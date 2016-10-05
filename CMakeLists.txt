cmake_minimum_required (VERSION 2.8)

# command :  cmake -GXcode 生成Xcode工程

#设置版本信息
project(ShadowMap)
set(version_major "1")
set(version_minor "0")
set(version_patch "0")
set(version "${version_major}.${version_minor}.${version_patch}")
message("version code is:${version}")
message("binary tree path:${PROJECT_BINARY_DIR}")

#设置源代码
aux_source_directory(./src SRC_LIST)

# set env
#add_definitions(-DDEF_RET_1)
#include_directories(${PROJECT_SOURCE_DIR}/inc)
#link_directories(${PROJECT_SOURCE_DIR}/external/lib)
#message("binary tree path:${PROJECT_BINARY_DIR}")

#add subfolders
#add_subdirectory(libssrc)
#add_subdirectory(dlls)
#add_subdirectory(exes)

#----------------------------------------------------
# set depen libs
#----------------------------------------------------
# 添加依赖
if(APPLE)
find_library(CocoaLib Cocoa)
find_library(OpenGLLib OpenGL)
find_library(GLUTLib GLUT)
set(EXTRA_LIBS ${CocoaLib} ${OpenGLLib} ${GLUTLib})
endif(APPLE)

# 依赖 glfw
find_library(GLFW3Lib libglfw.dylib depens/glfw/libs)
if(GLFW3Lib)
message("found glfw3 lib")
include_directories(depens/glfw/include)
endif(GLFW3Lib)

# gl3w
find_library(GL3WLib libgl3w.a depens/gl3w/libs)
if(GL3WLib)
message("found gl3w lib")
include_directories(depens/gl3w/include)
endif(GL3WLib)

# free_image
find_library(FreeImageLib libfreeimage.a depens/freeimage/libs)
if(FreeImageLib)
message("found FreeImageLib lib")
include_directories(depens/freeimage/include)
endif(FreeImageLib)

# assimp
find_library(AssimpLib libassimp.dylib depens/assimp/libs)
if(AssimpLib)
message("found AssimpLib lib")
include_directories(depens/assimp/include)
endif(AssimpLib)
#----------------------------------------------------
#----------------------------------------------------

# gl3w
include_directories(depens/gl3w/include)

# 使用C++ 11
add_compile_options(-std=c++11)
add_executable(a ${SRC_LIST})

#链接需要的库
target_link_libraries(a ${EXTRA_LIBS} ${GLFW3Lib} ${GL3WLib} ${FreeImageLib} ${AssimpLib})
