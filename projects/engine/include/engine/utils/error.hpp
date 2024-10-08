#pragma once 
#include "engine/types/number.hpp"
#include "engine/types/string.hpp"

namespace bubble
{
string_view GLErrorString( i32 errorCode );
void GLClearError();
void PrintOpenGLErrors( string_view function, string_view file, i32 line );
}

#define BUBBLE_ASSERT( x, str ) assert( x && str );

#ifdef _DEBUG
#define glcall(x) { GLClearError(); x; bubble::PrintOpenGLErrors(#x, __FILE__, __LINE__); }
#define glclear() GLClearError()
#define glcheck(s) bubble::PrintOpenGLErrors(s, __FILE__, __LINE__)
#else
#define glcall(x) (x)
#endif
