#include <hot_reloader_import.hpp>

namespace hr
{
HotReloader::HotReloader( fs::path path )
{
    if ( path.has_root_path() )
    {
        mLibraryName = path.filename().string();
        mLibraryPath = path.parent_path();
    }
    else
    {
        mLibraryName = path.string();
        mLibraryPath = fs::current_path();
    }
    auto fullpath = GetInputPath();
    if ( !fs::exists( fullpath ) )
        throw std::runtime_error( "Invalid library path " + fullpath.string() );

    auto cache_dir = GetCacheDir();
    if ( std::filesystem::exists( cache_dir ) )
        fs::remove_all( cache_dir );
    fs::create_directories( cache_dir );

    TryUpdate();
}

bool IsClose( fs::file_time_type start, fs::file_time_type end )
{
    return std::chrono::duration_cast<std::chrono::microseconds>( end - start ) < 1000ms;
}

bool HotReloader::TryUpdate()
{
    fs::file_time_type lib_update_time = mLastUpdateTime;
    lib_update_time = fs::last_write_time( GetInputPath() );

    if ( !IsClose( mLastUpdateTime, lib_update_time ) || mLibraryVersions.empty() )
    {
        for ( int i = 0; i < 10; i++ )
        {
            try
            {
                mLastUpdateTime = lib_update_time;
                fs::path input_path = GetInputPath();
                fs::path output_path = GetOutputPath();
                fs::copy( input_path, output_path, std::filesystem::copy_options::overwrite_existing );
                dynalo::library lib( output_path.string() );
                UpdateMeta( lib );
                mLibraryVersions.push_back( std::move( lib ) );
                mFunctionCache.clear();
                return true;
            }
            catch ( const std::exception& )
            {
                if ( i > 10 )
                    throw;
            }
            std::this_thread::sleep_for( RELOAD_DELAY );
        }
    }
    return false;
}

fs::path HotReloader::GetInputPath()
{
    return mLibraryPath / dynalo::to_native_name( mLibraryName );
}

fs::path HotReloader::GetOutputPath()
{
    auto version = std::to_string( GetLibraryVersion() );
    auto full_lib_name = mLibraryName + version;
    return GetCacheDir() / dynalo::to_native_name( full_lib_name );
}

fs::path HotReloader::GetCacheDir()
{
    return fs::current_path() / CACHE_DIR / mLibraryName;
}

int HotReloader::GetLibraryVersion()
{
    return static_cast<int>( mLibraryVersions.size() );
}

dynalo::library& HotReloader::GetActiveLibrary()
{
    return mLibraryVersions.back();
}

const LibraryMeta& HotReloader::ExtractLibraryMeta( dynalo::library& lib )
{
    auto func = lib.get_function<const LibraryMeta&()>( "HR_GetModuleInfo" );
    return func();
}

void HotReloader::UpdateMeta( dynalo::library& lib )
{
    auto new_meta = ExtractLibraryMeta( lib );
    for ( const auto& [name, func] : new_meta )
    {
        if ( mLibraryMeta.count( name ) )
        {
            auto old_sig = mLibraryMeta[name].ToString();
            auto new_sig = func.ToString();
            if ( old_sig != new_sig )
                throw std::runtime_error( "Loading failed: New signature is deferent "
                                          "to previous for function: " + name +
                                          "\nprevious: " + old_sig +
                                          "\nnew: " + new_sig );
        }
    }
    mLibraryMeta = new_meta;
}

}