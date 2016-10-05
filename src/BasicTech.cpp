//
//  BasicTech.cpp
//  GLFW_DrawTriangle
//
//  Created by dai on 16/10/3.
//
//

#include "BasicTech.h"
#include "MyDefines.h"

BasicTech::BasicTech(){

}

bool BasicTech::init(){
    if (!Technique::init()) {
        return false;
    }
    
    if (!addShader(GL_VERTEX_SHADER,"assets/vertex.vs")) {
        printf("init shader %s error!\n","assets/vertex.vs");
        return false;
    }
    
    if (!addShader(GL_FRAGMENT_SHADER,"assets/fragment.frag")) {
        printf("init shader %s error!\n","assets/fragment.frag");
        return false;
    }
    
    if (!linkAndValidate()) {
        printf("link program error!\n");
        return false;
    }
    
    mMVPMatrixLocation = getUniformLocation("gMVPMatrix");
    mSamplerLocation = getUniformLocation("gSampler");
    
    if (mMVPMatrixLocation == INVALID_VALUE ||
        mSamplerLocation == INVALID_VALUE) {
        printf("get uniform or attribute location error!\n");
        return false;
    }
    
    CHECK_GL_ERROR();
    
    return true;
}

void BasicTech::setMVPMatrix(const Mat& mvp){
    glUniformMatrix4fv(mMVPMatrixLocation,1,GL_FALSE,mvp.m);
}


void BasicTech::setTextureUnit(unsigned int textureUnit){
    glUniform1i(mSamplerLocation,textureUnit);
}




