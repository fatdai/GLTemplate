//
//  TestOnlyVBO.h
//  ShadowMap
//
//  Created by dai on 16/10/6.
//
//

#ifndef __ShadowMap__TestOnlyVBO__
#define __ShadowMap__TestOnlyVBO__

#include <stdio.h>
#include "BaseApp.h"
#include "LightTech.h"
#include "Camera.h"
#include "Texture.h"
#include "BasicTech.h"
#include "Mesh.h"
#include "MyHead.h"
#include <vector>

// vao vbo 的基本使用情况
class TestOnlyVBO : public BaseApp{
    
public:
    
    TestOnlyVBO(const char* title);
    ~TestOnlyVBO();
    virtual bool init();
    virtual void update();
    virtual void render();
    
    virtual void keyEvents(int key,int action);
    
private:
    void createBuffers();
    
    // vao 的方式绑定数据
//    void bindIndices(unsigned int* indices,unsigned int indicesSize);
//    void bindAttribute(GLint attrLocation,int coordSize,float* data,unsigned int dataSize);
private:
    
    BasicTech* mEffect = nullptr;
    Texture* mTexture = nullptr;
    Camera* mCamera = nullptr;
    
    Mat mWorldMatrix;
    Mat mProjMatrix;
    
    float mRotY = 0;
    
    GLuint mVBO = 0;
    GLuint mIBO = 0;
    
    int mIndicesCount = 0;
};

#endif /* defined(__ShadowMap__TestOnlyVBO__) */
