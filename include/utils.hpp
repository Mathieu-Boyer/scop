#pragma once
#include <numbers>

float degToRad(float degrees);


#ifdef __linux__
#include <GL/glx.h>
typedef void (*PFNGLGENERATEMIPMAPPROC)(GLenum);
PFNGLGENERATEMIPMAPPROC glGenerateMipmapFunc = (PFNGLGENERATEMIPMAPPROC)glXGetProcAddress((const GLubyte*)"glGenerateMipmap");

#endif