#pragma once
#include <sol/sol.hpp>
#include "engine/window/input.hpp"
#include "engine/types/pointer.hpp"
#include "engine/types/map.hpp"
#include "engine/scripting/script.hpp"

namespace bubble
{
class Scene;
struct Loader;

class ScriptingEngine
{
public:
    ScriptingEngine( WindowInput& input, Loader& loader, Scene& scene );
    ScriptingEngine( const ScriptingEngine& ) = default;
    ScriptingEngine( ScriptingEngine&& ) = default;
    ScriptingEngine& operator=( const ScriptingEngine& ) = default;
    ScriptingEngine& operator=( ScriptingEngine&& ) = default;
    ~ScriptingEngine();

    void OnUpdate( Ref<Script>& script );
    void RunScript( const Script& script );
    void RunScript( const Ref<Script>& script );

private:
    Scope<sol::state> mLua;

    struct FunctionCache
    {
        sol::function mOnUpdate;
    };
    str_hash_map<FunctionCache> mCache;
};

}