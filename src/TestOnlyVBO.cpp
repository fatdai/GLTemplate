//
//  TestOnlyVBO.cpp
//  ShadowMap
//
//  Created by dai on 16/10/6.
//
//

#include "TestOnlyVBO.h"
#include "MyDefines.h"


//---------------------------

TestOnlyVBO::TestOnlyVBO(const char* title):BaseApp(title){
    mWorldMatrix.identity();
    mProjMatrix = Mat::createProjMatrix(70,getRatio(),0.1,100);
};

TestOnlyVBO::~TestOnlyVBO(){
        
    delete mTexture;
    delete mEffect;
    delete mCamera;
}

bool TestOnlyVBO::init(){
    
    glClearColor(0, 0, 0, 0);
    glEnable(GL_DEPTH_TEST); // 开启深度测试
    //glEnable(GL_CULL_FACE);
    
    CHECK_GL_ERROR();
    // set viewport
    int width;
    int height;
    glfwGetFramebufferSize(getWindow(), &width, &height);
    glViewport(0, 0, width, height);
    
    CHECK_GL_ERROR();
    
    mEffect = new BasicTech;
    if (!mEffect->init()) {
        assert(false);
        return false;
    }
    
    mTexture = new Texture(GL_TEXTURE_2D,"assets/test.png");
    if (!mTexture->load()) {
        assert(false);
        return false;
    }
    
    Vec3 pos(0,1,5);
    Vec3 head(0,-1,-5);
    Vec3 up(0,1,0);
    mCamera = new Camera();
    
    createBuffers();
    
    return true;
}

void TestOnlyVBO::update(){
    mCamera->update();
}

void TestOnlyVBO::keyEvents(int key,int action){
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



void TestOnlyVBO::render(){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    mEffect->enable();
    
    mRotY += 1.0f;
    if (mRotY > 360) {
        mRotY -= 360;
    }
    mWorldMatrix.identity();
    mWorldMatrix.translate(0, 0, -2);
    //    mWorldMatrix.rotateY(mRotY);
    
    mEffect->setMVPMatrix(mProjMatrix * mCamera->getViewMatrix() * mWorldMatrix);
    CHECK_GL_ERROR();
    glBindBuffer(GL_ARRAY_BUFFER,mVBO);
    glEnableVertexAttribArray(0);
    CHECK_GL_ERROR();
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,sizeof(Vertex), 0);
    glVertexAttribPointer(1,2,GL_FLOAT,GL_FALSE,sizeof(Vertex),(void*)(3 * sizeof(float)));
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mIBO);
    mTexture->bind(GL_TEXTURE0);
    glDrawElements(GL_TRIANGLES,mIndicesCount,GL_UNSIGNED_INT,0);
    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    
    CHECK_GL_ERROR();
}


void TestOnlyVBO::createBuffers(){

    Vertex vertices[] = {
        Vertex(Vec3(-1, -1, -1),Vec2(0, 1)),
        Vertex(Vec3(1, -1, -1),Vec2(1, 1)),
        Vertex(Vec3(1, 1, -1),Vec2(1, 0)),
        Vertex(Vec3(-1, 1, -1),Vec2(0, 0)),
    };
    
    unsigned int indices[] = {
        0,1,2,0,2,3
    };
    
    mIndicesCount = sizeof(indices)/sizeof(indices[0]);
    
    glGenBuffers(1, &mVBO);
    glBindBuffer(GL_ARRAY_BUFFER, mVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    
    glGenBuffers(1, &mIBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mIBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
    
    glBindBuffer(GL_ARRAY_BUFFER,0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,0);

}

//void TestOnlyVBO::bindIndices(unsigned int* indices,unsigned int indicesSize){
//    printf("indicesSize : %d\n",indicesSize);
//    
//    GLuint vbo;
//    glGenBuffers(1, &vbo);
//    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,vbo);
//    glBufferData(GL_ELEMENT_ARRAY_BUFFER,indicesSize, indices, GL_STATIC_DRAW);
//    mVBOs.push_back(vbo);
//}
//
//void TestOnlyVBO::bindAttribute(GLint attrLocation,int coordSize,float* data,unsigned int dataSize){
//    GLuint vbo;
//    glGenBuffers(1, &vbo);
//    glBindBuffer(GL_ARRAY_BUFFER, vbo);
//    glBufferData(GL_ARRAY_BUFFER,dataSize,data,GL_STATIC_DRAW);
//    glVertexAttribPointer(attrLocation, coordSize, GL_FLOAT, GL_FALSE, 0, 0);
//    glEnableVertexAttribArray(attrLocation);
//    mVBOs.push_back(vbo);
//}
