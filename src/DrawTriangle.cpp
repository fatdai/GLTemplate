//
//  DrawTriangle.cpp
//  GLFW_DrawTriangle
//
//  Created by dai on 16/10/3.
//
//

#include "DrawTriangle.h"
#include "MyHead.h"
#include "MyDefines.h"
#include "Utils.h"


//---------------------------

DrawTriangle::DrawTriangle(const char* title):BaseApp(title){
    mWorldMatrix.identity();
    mProjMatrix = Mat::createProjMatrix(70,getRatio(),0.1,100);
    
    // 方向光
    mDirLight.color = Vec3(1, 1, 1);
    mDirLight.direction = Vec3(-10,-10,0);
    mDirLight.ambientIntensity = 0.2f;
    mDirLight.diffuseIntensity = 0.6f;
    
    // 点光源
    mPointLights[0].color = Vec3(1, 0, 0);
    mPointLights[0].ambientIntensity = 0.4f;
    mPointLights[0].diffuseIntensity = 0.7f;
    mPointLights[0].position = Vec3(0, 1, 0);
    mPointLights[0].attenuation.constant = 1;
    mPointLights[0].attenuation.linear = 2;
    mPointLights[0].attenuation.exp = 2;
    
    mPointLights[1].color = Vec3(0, 1, 0);
    mPointLights[1].ambientIntensity = 0.4f;
    mPointLights[1].diffuseIntensity = 0.7f;
    mPointLights[1].position = Vec3(1, 1, 0);
    mPointLights[1].attenuation.constant = 1;
    mPointLights[1].attenuation.linear = 2;
    mPointLights[1].attenuation.exp = 2;
    
    // 聚光灯
    mSpotLights[0].color = Vec3(0, 0, 1);
    mSpotLights[0].ambientIntensity = 0.4f;
    mSpotLights[0].diffuseIntensity = 1.0f;
    mSpotLights[0].position = Vec3(-1, 1, 0);
    mSpotLights[0].attenuation.constant = 1;
    mSpotLights[0].attenuation.linear = 0;
    mSpotLights[0].attenuation.exp = 0;
    mSpotLights[0].direction = Vec3(0, -1, 0);
    mSpotLights[0].cutOff = 20;
};

DrawTriangle::~DrawTriangle(){
    delete mEffect;
    delete mCamera;
    delete mMesh;
}

bool DrawTriangle::init(){
    
    glClearColor(0, 0, 0, 0);
    glEnable(GL_DEPTH_TEST); // 开启深度测试
    glEnable(GL_CULL_FACE);
    
    // set viewport
    int width;
    int height;
    glfwGetFramebufferSize(getWindow(), &width, &height);
    glViewport(0, 0, width, height);
    
    mEffect = new LightTech;
    mEffect->init();
    
    Vec3 pos(0,1,5);
    Vec3 head(0,-1,-5);
    Vec3 up(0,1,0);
    mCamera = new Camera(pos,head,up);
    mMesh = new Mesh;
    // phoenix_ugv.md2   land.obj
    if (!mMesh->LoadMesh("assets/land.obj")) {
        printf("load mesh error!\n");
        return false;
    }

    
    return true;
}

void DrawTriangle::update(){
    mCamera->update();
}

void DrawTriangle::keyEvents(int key,int action){
    if (action == GLFW_PRESS) {
        if (key == GLFW_KEY_A) {
            mCamera->left();
        }else if (key == GLFW_KEY_D){
            mCamera->right();
        }else if (key == GLFW_KEY_W){
            mCamera->forward();
        }else if (key == GLFW_KEY_S){
            mCamera->back();
        }else if (key == GLFW_KEY_UP){
            mCamera->lookUp();
        }else if (key == GLFW_KEY_DOWN){
            mCamera->lookDown();
        }
    }
}



void DrawTriangle::render(){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    mEffect->enable();
    
    mRotY += 1.0f;
    if (mRotY > 360) {
        mRotY -= 360;
    }
    mWorldMatrix.identity();
    mWorldMatrix.translate(0, 0, -2);
//    mWorldMatrix.rotateY(mRotY);
    CHECK_GL_ERROR();
    mEffect->setMVPMatrix(mProjMatrix * mCamera->getViewMatrix() * mWorldMatrix);
    mEffect->setWorldMatrix(mWorldMatrix);
    mEffect->setDirLight(mDirLight);
    mEffect->setSpecularInfo(1.0f,20);
    mEffect->setEyeWorldPos(mCamera->getPos());
    CHECK_GL_ERROR();
    // 设置下点光源
    mEffect->setPointLights(2,mPointLights);
    
    // 设置聚光灯
    mEffect->setSpotLights(1,mSpotLights);
    CHECK_GL_ERROR();
    mMesh->Render();

    CHECK_GL_ERROR();
}



