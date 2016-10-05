//
//  LightTech.cpp
//  Lighting
//
//  Created by dai on 16/10/4.
//
//

#include "LightTech.h"
#include <cassert>
#include <cmath>


LightTech::LightTech(){
}

bool LightTech::init(){
    if (!Technique::init()) {
        return false;
    }
    
    // load and link shaders
    if (!addShader(GL_VERTEX_SHADER,"assets/lighting.vs")) {
        return false;
    }
    
    if (!addShader(GL_FRAGMENT_SHADER,"assets/lighting.fs")) {
        return false;
    }
    
    if (!linkAndValidate()) {
        return false;
    }
    
    // get locations
//    mPositionLocation = getAttribLocation("Position");
//    mTexCoordLocation = getAttribLocation("TexCoord");
//    mNormalLocation = getAttribLocation("Normal");
    
    mMVPMatrixLocation = getUniformLocation("gMVPMatrix");
    mWorldMatrixLocation = getUniformLocation("gWorldMatrix");
    mSamplerLocation = getUniformLocation("gSampler");
    
    dirLightLocation.color = getUniformLocation("gDirectionalLight.base.color");
    dirLightLocation.ambientIntensity = getUniformLocation("gDirectionalLight.base.ambientIntensity");
    dirLightLocation.diffuseIntensity = getUniformLocation("gDirectionalLight.base.diffuseIntensity");
    dirLightLocation.direction = getUniformLocation("gDirectionalLight.direction");
    
    mEyeWorldPosLocation = getUniformLocation("gEyeWorldPos");
    mSpecularIntensityLocation = getUniformLocation("gSpecularIntensity");
    mSpecularPowerLocation = getUniformLocation("gSpecularPower");
    
    if (
//        mPositionLocation == INVALID_VALUE ||
//        mTexCoordLocation == INVALID_VALUE ||
//        mNormalLocation == INVALID_VALUE ||
        mMVPMatrixLocation == INVALID_VALUE ||
        mWorldMatrixLocation == INVALID_VALUE ||
        mSamplerLocation == INVALID_VALUE ||
        dirLightLocation.color == INVALID_VALUE ||
        dirLightLocation.ambientIntensity == INVALID_VALUE ||
        dirLightLocation.diffuseIntensity == INVALID_VALUE ||
        dirLightLocation.direction == INVALID_VALUE ||
        mEyeWorldPosLocation == INVALID_VALUE ||
        mSpecularIntensityLocation == INVALID_VALUE ||
        mSpecularPowerLocation == INVALID_VALUE
        ) {
        printf("get attribute or uniform location error!\n");
        assert(false);
        return false;
    }
    
    
    // 点光源相关
    mNumPointLightLocation = getUniformLocation("gNumPointLights");
    if (mNumPointLightLocation == INVALID_VALUE) {
        assert(false);
        printf("in shader,getuniformlocation error!\n");
        return false;
    }
    
    char tempName[128] = {0};
    for (int i = 0; i < MAX_POINT_LIGHT; ++i) {
        sprintf(tempName,"gPointLights[%d].base.color",i);
        pointLightLocations[i].color = getUniformLocation(tempName);
        
        sprintf(tempName,"gPointLights[%d].base.ambientIntensity",i);
        pointLightLocations[i].ambientIntensity = getUniformLocation(tempName);
        
        sprintf(tempName,"gPointLights[%d].base.diffuseIntensity",i);
        pointLightLocations[i].diffuseIntensity = getUniformLocation(tempName);
        
        sprintf(tempName,"gPointLights[%d].position",i);
        pointLightLocations[i].position = getUniformLocation(tempName);
        
        sprintf(tempName,"gPointLights[%d].atten.constant",i);
        pointLightLocations[i].attenuation.constant = getUniformLocation(tempName);
        
        sprintf(tempName,"gPointLights[%d].atten.linear",i);
        pointLightLocations[i].attenuation.linear = getUniformLocation(tempName);
        
        sprintf(tempName,"gPointLights[%d].atten.expo",i);
        pointLightLocations[i].attenuation.exp = getUniformLocation(tempName);
        
        if (pointLightLocations[i].color == INVALID_VALUE ||
            pointLightLocations[i].ambientIntensity == INVALID_VALUE ||
            pointLightLocations[i].diffuseIntensity == INVALID_VALUE ||
            pointLightLocations[i].position == INVALID_VALUE ||
            pointLightLocations[i].attenuation.constant == INVALID_VALUE ||
            pointLightLocations[i].attenuation.linear == INVALID_VALUE ||
            pointLightLocations[i].attenuation.exp == INVALID_VALUE
            ) {
            printf("in shader,getuniformlocation error!\n");
            assert(false);
            return false;
        }
    }

    
    // 聚光灯相关
    mNumSpotLightLocation = getUniformLocation("gNumSpotLights");
    if (mNumSpotLightLocation == INVALID_VALUE) {
        assert(false);
        printf("in shader,getuniformlocation error!\n");
        return false;
    }
    for (int i = 0; i < MAX_SPOT_LIGHT; ++i) {
        sprintf(tempName,"gSpotLights[%d].base.base.color",i);
        spotLightLocations[i].color = getUniformLocation(tempName);
        
        sprintf(tempName,"gSpotLights[%d].base.base.ambientIntensity",i);
        spotLightLocations[i].ambientIntensity = getUniformLocation(tempName);
        
        sprintf(tempName,"gSpotLights[%d].base.base.diffuseIntensity",i);
        spotLightLocations[i].diffuseIntensity = getUniformLocation(tempName);
        
        sprintf(tempName,"gSpotLights[%d].base.position",i);
        spotLightLocations[i].position = getUniformLocation(tempName);
        
        sprintf(tempName,"gSpotLights[%d].base.atten.constant",i);
        spotLightLocations[i].attenuation.constant = getUniformLocation(tempName);
        
        sprintf(tempName,"gSpotLights[%d].base.atten.linear",i);
        spotLightLocations[i].attenuation.linear = getUniformLocation(tempName);
        
        sprintf(tempName,"gSpotLights[%d].base.atten.expo",i);
        spotLightLocations[i].attenuation.exp = getUniformLocation(tempName);
        
        sprintf(tempName,"gSpotLights[%d].direction",i);
        spotLightLocations[i].direction = getUniformLocation(tempName);
        
        sprintf(tempName,"gSpotLights[%d].cutOff",i);
        spotLightLocations[i].cutOff = getUniformLocation(tempName);
        
        if (spotLightLocations[i].color == INVALID_VALUE ||
            spotLightLocations[i].ambientIntensity == INVALID_VALUE ||
            spotLightLocations[i].diffuseIntensity == INVALID_VALUE ||
            spotLightLocations[i].position == INVALID_VALUE ||
            spotLightLocations[i].attenuation.constant == INVALID_VALUE ||
            spotLightLocations[i].attenuation.linear == INVALID_VALUE ||
            spotLightLocations[i].attenuation.exp == INVALID_VALUE ||
            spotLightLocations[i].direction == INVALID_VALUE ||
            spotLightLocations[i].cutOff == INVALID_VALUE
            ) {
            printf("in shader,getuniformlocation error!\n");
            assert(false);
            return false;
        }
    }
    
    return true;
}

// set uniforms
void LightTech::setTextureUnit(unsigned int textureUnit){
    glUniform1i(mSamplerLocation,textureUnit);
}

void LightTech::setDirLight(const DirectionalLight& dirLight){
    glUniform3f(dirLightLocation.color,dirLight.color.x, dirLight.color.y, dirLight.color.z);
    glUniform1f(dirLightLocation.ambientIntensity, dirLight.ambientIntensity);
    
    Vec3 dir = dirLight.direction;
    dir.normalize();
    glUniform3f(dirLightLocation.direction, dir.x, dir.y, dir.z);
    glUniform1f(dirLightLocation.diffuseIntensity, dirLight.diffuseIntensity);
}

void LightTech::setMVPMatrix(const Mat& mvp){
    glUniformMatrix4fv(mMVPMatrixLocation,1,GL_FALSE,mvp.m);
}

void LightTech::setWorldMatrix(const Mat& world){
    glUniformMatrix4fv(mWorldMatrixLocation,1,GL_FALSE,world.m);
}

void LightTech::setSpecularInfo(float specularIntensity,float power){
    glUniform1f(mSpecularIntensityLocation,specularIntensity);
    glUniform1f(mSpecularPowerLocation, power);
}

void LightTech::setEyeWorldPos(const Vec3& pos){
    glUniform3f(mEyeWorldPosLocation,pos.x, pos.y, pos.z);
}

void LightTech::setPointLights(unsigned int numLight,const PointLight* lights){
    assert(numLight <= MAX_POINT_LIGHT);
    glUniform1i(mNumPointLightLocation, numLight);
    for (int i = 0; i < numLight; ++i) {
        glUniform3f(pointLightLocations[i].color,lights[i].color.x,lights[i].color.y, lights[i].color.z);
        glUniform1f(pointLightLocations[i].ambientIntensity, lights[i].ambientIntensity);
        glUniform1f(pointLightLocations[i].diffuseIntensity, lights[i].diffuseIntensity);
        glUniform3f(pointLightLocations[i].position, lights[i].position.x, lights[i].position.y, lights[i].position.z);
        glUniform1f(pointLightLocations[i].attenuation.constant, lights[i].attenuation.constant);
        glUniform1f(pointLightLocations[i].attenuation.linear, lights[i].attenuation.linear);
        glUniform1f(pointLightLocations[i].attenuation.exp, lights[i].attenuation.exp);
    }
}

void LightTech::setSpotLights(unsigned int numLight,const SpotLight* lights){
    assert(numLight < MAX_SPOT_LIGHT);
    glUniform1i(mNumSpotLightLocation,numLight);
    for (int i = 0; i < numLight ; ++i) {
        glUniform3f(spotLightLocations[i].position, lights[i].position.x, lights[i].position.y, lights[i].position.z);
        glUniform3f(spotLightLocations[i].color, lights[i].color.x, lights[i].color.y, lights[i].color.z);
        glUniform1f(spotLightLocations[i].ambientIntensity,lights[i].ambientIntensity);
        glUniform1f(spotLightLocations[i].diffuseIntensity,lights[i].diffuseIntensity);
        
        Vec3 dir = lights[i].direction;
        dir.normalize();
        
        glUniform3f(spotLightLocations[i].direction,dir.x, dir.y, dir.z);
        glUniform1f(spotLightLocations[i].cutOff,cosf(MATH_DEG_TO_RAD(lights[i].cutOff)));
        glUniform1f(spotLightLocations[i].attenuation.constant,lights[i].attenuation.constant);
        glUniform1f(spotLightLocations[i].attenuation.linear,lights[i].attenuation.linear);
        glUniform1f(spotLightLocations[i].attenuation.exp,lights[i].attenuation.exp);
    }
}

