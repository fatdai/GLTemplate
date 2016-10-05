//
//  BaseApp.cpp
//  MyLighting
//
//  Created by dai on 16/9/26.
//
//

#include "BaseApp.h"
#include <unistd.h>
#include <sys/time.h>
#include <iostream>
#include "Utils.h"
#include "MyHead.h"
using namespace std;

const static int sOnceRenderTime = 1000/60;


static void ErrorCallback(int error,const char* desc){
    fprintf(stderr,"Error:%s\n",desc);
};

static void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods){
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
         glfwSetWindowShouldClose(window, 1);
    }
    
    // 处理键盘事件
    BaseApp::getInstance()->keyEvents(key,action);
    
}

BaseApp* BaseApp::App = nullptr;

BaseApp::BaseApp(const char* title,int width,int height){
    mTitle = title;
    mWidth = width;
    mHeight = height;
    mFrameCount = 0;
    mFPS = 0;
    mRunning = false;
    mLastTime = 0;
    mDeltaTime = 0;
    mWindow = nullptr;
    App = this;
    initContext();
}

BaseApp::~BaseApp(){
    
}

float BaseApp::getRatio(){
    return (float)mWidth/(float)mHeight;
}

bool BaseApp::initContext(){
    
    // set error callback
    glfwSetErrorCallback(ErrorCallback);
    
    /* Initialize the library */
    if (!glfwInit())
        return -1;
    
    // 设置 opengl 环境和版本
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    
    /* Create a windowed mode window and its OpenGL context */
    mWindow = glfwCreateWindow(mWidth,mHeight,mTitle.c_str(), NULL, NULL);
    if (!mWindow)
    {
        glfwTerminate();
        return false;
    }

    // set key event callback
    glfwSetKeyCallback(mWindow, KeyCallback);
    
    /* Make the window's context current */
    glfwMakeContextCurrent(mWindow);
    
    //---------------------------------------
    // 参考这里:https://www.opengl.org/wiki/OpenGL_Loading_Library
    // init gl3w
    if (gl3wInit()) {
        fprintf(stderr, "failed to initialize OpenGL\n");
        return -1;
    }
    
    if (!gl3wIsSupported(3, 3)) {
        fprintf(stderr, "OpenGL 3.3 not supported\n");
        return -1;
    }
    //---------------------------------------
    
    CHECK_GL_ERROR();
    
    // 打印硬件信息
    cout << "硬件信息为:" << endl;
    cout << "OpenGL Vendor:" << glGetString(GL_VENDOR) << endl;
    cout << "OpenGL Renderer: " << glGetString(GL_RENDERER) << endl;
    cout << "OpenGL Version: " << glGetString(GL_VERSION) << endl;
    cout << "GLSL Version:" << glGetString(GL_SHADING_LANGUAGE_VERSION) << endl;
    cout << "------------------------------------------------------" << endl;
    
    return true;
}

float BaseApp::getDeltaTime(){
    return mDeltaTime;
}


void BaseApp::runGame(){
    
    CHECK_GL_ERROR();
    if (!init()) {
        printf("init error!\n");
        return;
    }
    
    mLastTime = GetCurrentTime();
    
    long frameStartTime = 0;  // 每一帧开始的时间
    long frameOverTime = GetCurrentTime();   // 每一帧结束的时间
    
    while (!glfwWindowShouldClose(mWindow)) {
        
        frameStartTime = GetCurrentTime();
        
        mDeltaTime = (GetCurrentTime() - frameOverTime)/1000.0f;

        //logic
        update();
        
        //render
        render();
        
        //fps
        calculateFPS();
        
        renderFPS();
        
        frameOverTime = GetCurrentTime();
        if (frameOverTime - frameStartTime < sOnceRenderTime) {
            //delay(sOnceRenderTime - (frameOverTime - frameStartTime));
        }

        /* Swap front and back buffers */
        glfwSwapBuffers(mWindow);
        
        /* Poll for and process events */
        glfwPollEvents();
    }
    
    release();
    glfwDestroyWindow(mWindow);
    glfwTerminate();
}


// 计算 fps
void BaseApp::calculateFPS(){
    ++mFrameCount;
    long curTime = GetCurrentTime();
    if (curTime - mLastTime > 1000) {
        mLastTime = curTime;
        mFPS = mFrameCount;
        mFrameCount = 0;
    }
}

int BaseApp::getWindowWidth(){
    return mWidth;
}

int BaseApp::getWindowHeight(){
    return mHeight;
}

void BaseApp::renderFPS(){
    // TODO 等待实现
//    static char text[128];
//    sprintf(text,"FPS:%d",mFPS);
//    printf("%s\n",text);
}