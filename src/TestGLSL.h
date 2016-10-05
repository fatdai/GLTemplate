//
//  TestGLSL.h
//  ShadowMap
//
//  Created by dai on 16/10/5.
//
//

#ifndef __ShadowMap__TestGLSL__
#define __ShadowMap__TestGLSL__

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
class TestGLSL : public BaseApp{
    
public:
    
    TestGLSL(const char* title);
    ~TestGLSL();
    virtual bool init();
    virtual void update();
    virtual void render();
    
    virtual void keyEvents(int key,int action);
    
private:
    void createBuffers();
    
    // vao 的方式绑定数据
    void bindIndices(unsigned int* indices,unsigned int indicesSize);
    void bindAttribute(GLint attrLocation,int coordSize,float* data,unsigned int dataSize);
private:

    BasicTech* mEffect = nullptr;
    Texture* mTexture = nullptr;
    Camera* mCamera = nullptr;
    
    Mat mWorldMatrix;
    Mat mProjMatrix;
    
    float mRotY = 0;
    
    GLuint mVAO = 0;
    vector<GLuint> mVBOs;
    
    int mIndicesCount = 0;
};


#endif /* defined(__ShadowMap__TestGLSL__) */
