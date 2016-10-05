//
//  LightTech.h
//  Lighting
//
//  Created by dai on 16/10/4.
//
//

#ifndef __Lighting__LightTech__
#define __Lighting__LightTech__

#include <stdio.h>
#include "Technique.h"
#include "BasicLight.h"
#include "MyHead.h"
#include "MyDefines.h"

class LightTech : public Technique{
    
public:
    LightTech();
    virtual bool init();
    
    // set uniforms
    void setTextureUnit(unsigned int textureUnit);
    void setDirLight(const DirectionalLight& dirLight);
    void setSpecularInfo(float specularIntensity,float power);
    void setEyeWorldPos(const Vec3& pos);
    void setMVPMatrix(const Mat& mvp);
    void setWorldMatrix(const Mat& world);
    
    // 设置点光源
    void setPointLights(unsigned int numLight,const PointLight* lights);
    
    // 设置聚光灯
    void setSpotLights(unsigned int numLight,const SpotLight* lights);
    
public:
    
//    GLint getPositionLocation(){
//        return mPositionLocation;
//    }
//    GLint getTexCoordLocation(){
//        return mTexCoordLocation;
//    }
//    GLint getNormalLocation(){
//        return mNormalLocation;
//    }
    
    
private:
    
    
    // 先试试方向光
    GLint mMVPMatrixLocation = -1;
    GLint mWorldMatrixLocation = -1;
    GLint mSamplerLocation = -1;
    GLint mEyeWorldPosLocation = -1;
    GLint mSpecularIntensityLocation = -1;
    GLint mSpecularPowerLocation = -1;
    
//    GLint mPositionLocation = -1;
//    GLint mTexCoordLocation = -1;
//    GLint mNormalLocation = -1;
    
    DirLightLocation dirLightLocation;
    
    PointLightLocation pointLightLocations[MAX_POINT_LIGHT];
    GLint mNumPointLightLocation = -1;
    
    SpotLightLocation spotLightLocations[MAX_SPOT_LIGHT];
    GLint mNumSpotLightLocation = -1;
    
};



#endif /* defined(__Lighting__LightTech__) */
