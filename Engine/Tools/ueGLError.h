

#ifndef UE_GLERROR
#define UE_GLERROR

#include "../Rendering/ueIncludeGL.h"

#include<string>
#include <plog/Log.h>

#ifndef NDEBUG
GLenum glCheckError_(const char* desc, const char* file, int line);
#define glCheckError(desc) glCheckError_(desc, __FILE__, __LINE__)
#else
#define glCheckError(desc)
#endif
#endif