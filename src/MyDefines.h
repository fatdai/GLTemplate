//
//  MyDefines.h
//  GLFW_DrawTriangle
//
//  Created by dai on 16/10/3.
//
//

#ifndef GLFW_DrawTriangle_MyDefines_h
#define GLFW_DrawTriangle_MyDefines_h

//#define glGenVertexArrays glGenVertexArraysAPPLE
//#define glBindVertexArray glBindVertexArrayAPPLE
//#define glDeleteVertexArrays glDeleteVertexArraysAPPLE

//  定义最大的点光源为 8 个
#define MAX_POINT_LIGHT 8
#define MAX_SPOT_LIGHT 4

// 角度  弧度间的转换
#define MATH_DEG_TO_RAD(x) ((x)*0.0174532925f)
#define MATH_RAD_TO_DEG(x) ((x)*57.29577951f)

#define INVALID_VALUE -1

//---------------------------------------------
// 检测opengl 错误
#define CHECK_GL_ERROR() \
do { \
GLenum __error = glGetError(); \
if(__error) { \
printf("OpenGL error 0x%04X in %s %s %d\n", __error, __FILE__, __FUNCTION__, __LINE__); \
} \
} while (false)
//---------------------------------------------

#endif
