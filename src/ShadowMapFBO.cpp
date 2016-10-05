//
//  ShadowMapFBO.cpp
//  ShadowMap
//
//  Created by dai on 16/10/5.
//
//

#include "ShadowMapFBO.h"


ShadowMapFBO::ShadowMapFBO(){
    mFBO = 0;
    mShadowMap = 0;
}

ShadowMapFBO::~ShadowMapFBO(){
    if (mFBO != 0) {
        
    }
}

bool ShadowMapFBO::init(unsigned int WindowWidth, unsigned int WindowHeight){
    //glGenFramebuffers(1,&mFBO);
}
void ShadowMapFBO::bindForWriting(){

}
void ShadowMapFBO::bindForReading(GLenum TextureUnit){

}