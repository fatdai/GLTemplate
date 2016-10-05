//
//  DrawTriangle.h
//  GLFW_DrawTriangle
//
//  Created by dai on 16/10/3.
//
//

#ifndef __GLFW_DrawTriangle__DrawTriangle__
#define __GLFW_DrawTriangle__DrawTriangle__

#include <stdio.h>
#include "BaseApp.h"
#include "LightTech.h"
#include "Camera.h"
#include "Texture.h"
#include "BasicLight.h"
#include "Mesh.h"
#include "MyHead.h"


class DrawTriangle : public BaseApp{
    
public:
    
    DrawTriangle(const char* title);
    ~DrawTriangle();
    virtual bool init();
    virtual void update();
    virtual void render();
    
    virtual void keyEvents(int key,int action);
    
private:
    LightTech* mEffect = nullptr;
    Camera* mCamera = nullptr;
    
    DirectionalLight mDirLight;
    PointLight mPointLights[2];
    SpotLight mSpotLights[1];

    
    Mat mWorldMatrix;
    Mat mProjMatrix;
    
    float mRotY = 0;
    
    Mesh* mMesh = nullptr;
};

#endif /* defined(__GLFW_DrawTriangle__DrawTriangle__) */
