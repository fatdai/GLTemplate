//
//  BasicLight.h
//  Lighting
//
//  Created by dai on 16/10/4.
//
//

#ifndef Lighting_BasicLight_h
#define Lighting_BasicLight_h

#include "MyHead.h"

// 基本光源信息
struct BaseLight{
    
    Vec3 color;
    float ambientIntensity;
    float diffuseIntensity;
    
    BaseLight(){
        color = Vec3(0, 0, 0);
        ambientIntensity = 0;
        diffuseIntensity = 0;
    }
};


// 方向光
struct DirectionalLight : public BaseLight{
    Vec3 direction;
    DirectionalLight(){
        direction = Vec3(0, 0, 0);
    }
};


// 对应的 location
struct DirLightLocation{
    GLint color;
    GLint ambientIntensity;
    GLint diffuseIntensity;
    GLint direction;
    DirLightLocation(){
        color = ambientIntensity = diffuseIntensity = direction = 0;
    }
};

// 点光源
struct PointLight : public BaseLight{
    Vec3 position;
    struct{
        float constant;
        float linear;
        float exp;
    }attenuation;
    
    PointLight(){
        position = Vec3(0, 0, 0);
        attenuation.constant = 1;
        attenuation.linear = 0;
        attenuation.exp = 0;
    }
};

struct PointLightLocation{
    GLint position;
    GLint color;
    GLint ambientIntensity;
    GLint diffuseIntensity;
    
    struct{
        GLint constant;
        GLint linear;
        GLint exp;
    }attenuation;
    
    PointLightLocation(){
        color = ambientIntensity = diffuseIntensity = position = 0;
        attenuation.constant = attenuation.linear = attenuation.exp = 0;
    }
};


// 聚光灯
struct SpotLight : public PointLight{
    Vec3 direction;
    float cutOff = 0;  // 直接写角度,最好控制在[10-30]
};

struct SpotLightLocation{
    GLint position = -1;
    GLint color = -1;
    GLint ambientIntensity = -1;
    GLint diffuseIntensity = -1;
    GLint direction = -1;
    GLint cutOff = -1;
    
    struct{
        GLint constant;
        GLint linear;
        GLint exp;
    }attenuation;
    
    SpotLightLocation(){
        attenuation.constant = attenuation.linear = attenuation.exp = -1;
    }
};


#endif
