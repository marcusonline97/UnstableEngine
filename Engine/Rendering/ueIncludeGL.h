#pragma once

#ifndef UE_INCLUDE_GL

#ifdef __EMSCRIPTEN__
#include <GLES3/gl3.h>
#include <GLES2/gl2ext.h>
#include <emscripten.h>
#include <GLFW/glfw3.h>


#define GL_GLEXT_PROTOTYPES
#define EGL_EGLEXT_PROTOTYPES
#else

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#endif // __EMSCRIPTEN__

#endif // !UE_INCLUDE_GL
