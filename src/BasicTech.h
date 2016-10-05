//
//  BasicTech.h
//  GLFW_DrawTriangle
//
//  Created by dai on 16/10/3.
//
//

#ifndef __GLFW_DrawTriangle__BasicTech__
#define __GLFW_DrawTriangle__BasicTech__

#include <stdio.h>
#include "Technique.h"
#include "MyHead.h"

// 作为测试使用,渲染下纹理试试
class BasicTech : public Technique{
public:
    
    BasicTech();
    virtual bool init();
    
    // 传递数据给 着色器
    void setMVPMatrix(const Mat& mvp);
    void setTextureUnit(unsigned int textureUnit);
    
private:
    
    GLint mMVPMatrixLocation = -1;
    GLint mSamplerLocation;
    
};

#endif /* defined(__GLFW_DrawTriangle__BasicTech__) */
