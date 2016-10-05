//
//  Mat.h
//  GLFW_DrawTriangle
//
//  Created by dai on 16/10/3.
//
//

#ifndef __GLFW_DrawTriangle__Mat__
#define __GLFW_DrawTriangle__Mat__

#include <stdio.h>
#include "Vec3.h"

class Mat{
    
public:
    
    float m[16];
    
    Mat();
    Mat(float* array);
    Mat(const Mat& other);
    
    // 矩阵乘法
    Mat operator*(const Mat& other);
    
    // 变换点和向量
    Vec3 transformPoint(const Vec3& point);
    Vec3 transformVector(const Vec3& vec);
    
    // transform
    Mat& translate(const Vec3& v);
    Mat& translate(float x,float y,float z);
    Mat& rotate(float degress,const Vec3& axis);
    Mat& rotateX(float degress);
    Mat& rotateY(float degress);
    Mat& rotateZ(float degress);
    Mat& scale(const Vec3& s);
    Mat& scale(float t);
    Mat& scale(float x,float y,float z);
    
    void identity();
    void print();
    
    // static
    static Mat createTranslateMatrix(const Vec3& tran);
    static Mat createTranslateMatrix(float x,float y,float z);
    
    // axis 要求已经 normalize
    static Mat createRotateMatrix(float degress,const Vec3& axis);
    
    static Mat createRotateX(float degress);
    static Mat createRotateY(float degress);
    static Mat createRotateZ(float degress);
    static Mat createScaleMatrix(const Vec3& scale);
    static Mat createScaleMatrix(float x,float y,float z);
    
    // head 表示注视的方向
    static Mat createViewMatrix(const Vec3& pos,const Vec3& head,const Vec3& up);
    static Mat createProjMatrix(float fov,float ratio,float near,float far);
    static Mat createOrthographic(float left, float right, float bottom,
                                  float top, float zNearPlane,
                                  float zFarPlane);
    
    
    
};

#endif /* defined(__GLFW_DrawTriangle__Mat__) */
