//
//  BaseApp.h
//  MyLighting
//
//  Created by dai on 16/9/26.
//
//

#ifndef __MyLighting__BaseApp__
#define __MyLighting__BaseApp__

#include <stdio.h>
#include <string>
using namespace std;

// 程序大体框架
class GLFWwindow;
class BaseApp{
private:
    
    static BaseApp* App;
    
public:
    
    
    
    BaseApp(const char* title,int width = 640,int height = 480);
    virtual ~BaseApp();
    static BaseApp* getInstance(){
        return App;
    }
    
    void renderFPS();
    
    
    virtual bool init() = 0;
    virtual void render() = 0;
    
    // 在这里面更新
    virtual void update(){};
    
    // 在这里面释放资源
    virtual void release(){};
    
    // 处理键盘事件
    virtual void keyEvents(int key,int action) = 0;
    
    
    void runGame();
    
    float getDeltaTime();
    int getWindowWidth();
    float getRatio();
    int getWindowHeight();
    GLFWwindow* getWindow(){
        return mWindow;
    }
    
private:
    
    bool initContext();
    
protected:
    
    void calculateFPS();
    
protected:
    
    int mFrameCount;  // 记录1秒累计渲染多少帧
    int mFPS;

    long mLastTime; // 记录时间
    
    int mWidth;
    int mHeight;
    
    bool mRunning;
    
    float mDeltaTime;
    
    GLFWwindow* mWindow;
    string mTitle;
};

#endif /* defined(__MyLighting__BaseApp__) */
