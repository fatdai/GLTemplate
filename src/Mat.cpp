//
//  Mat.cpp
//  GLFW_DrawTriangle
//
//  Created by dai on 16/10/3.
//
//

#include "Mat.h"
#include <memory>
#include <cmath>
#include <cassert>
#include "MyDefines.h"


Mat::Mat(){
    memset(m,0,sizeof(float) * 16);
}

Mat::Mat(float* array){
    memcpy(m,array,sizeof(float) * 16);
}

Mat::Mat(const Mat& other){
    if (&other != this) {
        memcpy(m,other.m,sizeof(float) * 16);
    }
}

Mat Mat::operator*(const Mat& other){
    Mat ret;
    ret.m[0] = m[0] * other.m[0] + m[4] * other.m[1] + m[8] * other.m[2] + m[12] * other.m[3];
    ret.m[1] = m[1] * other.m[0] + m[5] * other.m[1] + m[9] * other.m[2] + m[13] * other.m[3];
    ret.m[2] = m[2] * other.m[0] + m[6] * other.m[1] + m[10] * other.m[2] + m[14] * other.m[3];
    ret.m[3] = m[3] * other.m[0] + m[7] * other.m[1] + m[11] * other.m[2] + m[15] * other.m[3];
    
    ret.m[4] = m[0] * other.m[4] + m[4] * other.m[5] + m[8] * other.m[6] + m[12] * other.m[7];
    ret.m[5] = m[1] * other.m[4] + m[5] * other.m[5] + m[9] * other.m[6] + m[13] * other.m[7];
    ret.m[6] = m[2] * other.m[4] + m[6] * other.m[5] + m[10] * other.m[6] + m[14] * other.m[7];
    ret.m[7] = m[3] * other.m[4] + m[7] * other.m[5] + m[11] * other.m[6] + m[15] * other.m[7];
    
    ret.m[8] = m[0] * other.m[8] + m[4] * other.m[9] + m[8] * other.m[10] + m[12] * other.m[11];
    ret.m[9] = m[1] * other.m[8] + m[5] * other.m[9] + m[9] * other.m[10] + m[13] * other.m[11];
    ret.m[10] = m[2] * other.m[8] + m[6] * other.m[9] + m[10] * other.m[10] + m[14] * other.m[11];
    ret.m[11] = m[3] * other.m[8] + m[7] * other.m[9] + m[11] * other.m[10] + m[15] * other.m[11];
    
    ret.m[12] = m[0] * other.m[12] + m[4] * other.m[13] + m[8] * other.m[14] + m[12] * other.m[15];
    ret.m[13] = m[1] * other.m[12] + m[5] * other.m[13] + m[9] * other.m[14] + m[13] * other.m[15];
    ret.m[14] = m[2] * other.m[12] + m[6] * other.m[13] + m[10] * other.m[14] + m[14] * other.m[15];
    ret.m[15] = m[3] * other.m[12] + m[7] * other.m[13] + m[11] * other.m[14] + m[15] * other.m[15];
    return ret;
}

Vec3 Mat::transformPoint(const Vec3& point){
    Vec3 ret;
    ret.x = m[0] * point.x + m[4] * point.y + m[8] * point.z + m[12];
    ret.y = m[1] * point.x + m[5] * point.y + m[9] * point.z + m[13];
    ret.z = m[2] * point.x + m[6] * point.y + m[10] * point.z + m[14];
    return ret;
}

Vec3 Mat::transformVector(const Vec3& vec){
    Vec3 ret;
    ret.x = m[0] * vec.x + m[4] * vec.y + m[8] * vec.z;
    ret.y = m[1] * vec.x + m[5] * vec.y + m[9] * vec.z;
    ret.z = m[2] * vec.x + m[6] * vec.y + m[10] * vec.z;
    return ret;
}

void Mat::identity(){
    memset(m,0,sizeof(float) * 16);
    m[0] = m[5] = m[10] = m[15] = 1;
}


Mat& Mat::translate(const Vec3& v){
    return translate(v.x, v.y, v.z);
}
Mat& Mat::translate(float x,float y,float z){
    Mat t = Mat::createTranslateMatrix(x,y,z);
    *this = *this * t;
    return *this;
}
Mat& Mat::rotate(float degress,const Vec3& axis){
    Mat t = Mat::createRotateMatrix(degress, axis);
    *this = *this * t;
    return *this;
}
Mat& Mat::rotateX(float degress){
    Mat t = Mat::createRotateX(degress);
    *this = *this * t;
    return *this;
}
Mat& Mat::rotateY(float degress){
    Mat t = Mat::createRotateY(degress);
    *this = *this * t;
    return *this;
}
Mat& Mat::rotateZ(float degress){
    Mat t = Mat::createRotateZ(degress);
    *this = *this * t;
    return *this;
}
Mat& Mat::scale(const Vec3& s){
    return scale(s.x, s.y, s.z);
}
Mat& Mat::scale(float x,float y,float z){
    Mat t = Mat::createScaleMatrix(x, y, z);
    *this = *this * t;
    return *this;
}

Mat& Mat::scale(float t){
    return scale(t, t, t);
}




void Mat::print(){
    printf("---------------------------------\n");
    printf("%.3f,%.3f,%.3f,%.3f\n",m[0],m[4],m[8],m[12]);
    printf("%.3f,%.3f,%.3f,%.3f\n",m[1],m[5],m[9],m[13]);
    printf("%.3f,%.3f,%.3f,%.3f\n",m[2],m[6],m[10],m[14]);
    printf("%.3f,%.3f,%.3f,%.3f\n",m[3],m[7],m[11],m[15]);
}

//-------------------------------------------
// static
Mat Mat::createTranslateMatrix(const Vec3& tran){
    return createTranslateMatrix(tran.x, tran.y, tran.z);
}
Mat Mat::createTranslateMatrix(float x,float y,float z){
    Mat ret;
    ret.identity();
    ret.m[12] = x;
    ret.m[13] = y;
    ret.m[14] = z;
    return ret;
}

Mat Mat::createRotateMatrix(float degress,const Vec3& axis){
    float rad = MATH_DEG_TO_RAD(degress);
    float sin = sinf(rad);
    float cos = cosf(rad);
    
    Mat ret;
    ret.m[0] = cos + (1 - cos) * axis.x * axis.x;
    ret.m[1] = (1 - cos) * axis.x * axis.y + sin * axis.z;
    ret.m[2] = (1 - cos) * axis.x * axis.z - sin * axis.y;
    ret.m[3] = 0;
    
    ret.m[4] = (1 - cos) * axis.y * axis.x - sin * axis.z;
    ret.m[5] = cos + (1 - cos) * axis.y * axis.y;
    ret.m[6] = (1 - cos) * axis.y * axis.z + sin * axis.x;
    ret.m[7] = 0;
    
    ret.m[8] = (1 - cos) * axis.z * axis.x + sin * axis.y;
    ret.m[9] = (1 - cos) * axis.z * axis.y - sin * axis.x;
    ret.m[10] = cos + (1 - cos) * axis.z * axis.z;
    ret.m[11] = 0;
    
    ret.m[12] = ret.m[13] = ret.m[14] = 0;
    ret.m[15] = 1;
    return ret;
}

Mat Mat::createRotateX(float degress){
    float rad = MATH_DEG_TO_RAD(degress);
    float sin = sinf(rad);
    float cos = cosf(rad);
    
    Mat ret;
    ret.m[0] = 1;
    ret.m[5] = cos;
    ret.m[6] = sin;
    ret.m[9] = -sin;
    ret.m[10] = cos;
    ret.m[15] = 1;
    return ret;
}

Mat Mat::createRotateY(float degress){
    float rad = MATH_DEG_TO_RAD(degress);
    float sin = sinf(rad);
    float cos = cosf(rad);
    
    Mat ret;
    ret.m[0] = cos;
    ret.m[2] = -sin;
    ret.m[5] = 1;
    ret.m[8] = sin;
    ret.m[10] = cos;
    ret.m[15] = 1;
    return ret;
}


Mat Mat::createRotateZ(float degress){
    float rad = MATH_DEG_TO_RAD(degress);
    float sin = sinf(rad);
    float cos = cosf(rad);
    
    Mat ret;
    ret.m[0] = cos;
    ret.m[1] = sin;
    ret.m[4] = -sin;
    ret.m[5] = cos;
    ret.m[10] = 1;
    ret.m[15] = 1;
    return ret;
}


Mat Mat::createScaleMatrix(const Vec3& scale){
    return createScaleMatrix(scale.x, scale.y, scale.z);
}

Mat Mat::createScaleMatrix(float x,float y,float z){
    Mat ret;
    ret.m[0] = x;
    ret.m[5] = y;
    ret.m[10] = z;
    ret.m[15] = 1;
    return ret;
}


Mat Mat::createViewMatrix(const Vec3& pos,const Vec3& head,const Vec3& up){

    // 计算 viewMatrix 时, 此时的+z轴的方向和head方向相反
    Vec3 zAxis = -head;
    zAxis.normalize();
    
    Vec3 xAxis = up.cross(zAxis);
    xAxis.normalize();
    
    Vec3 yAxis = zAxis.cross(xAxis);
    yAxis.normalize();
    
    Mat inverseR;
    inverseR.m[0] = xAxis.x;
    inverseR.m[4] = xAxis.y;
    inverseR.m[8] = xAxis.z;
    inverseR.m[12] = 0;
    
    inverseR.m[1] = yAxis.x;
    inverseR.m[5] = yAxis.y;
    inverseR.m[9] = yAxis.z;
    inverseR.m[13] = 0;
    
    inverseR.m[2] = zAxis.x;
    inverseR.m[6] = zAxis.y;
    inverseR.m[10] = zAxis.z;
    inverseR.m[14] = 0;
    
    inverseR.m[15] = 1;
    
    Mat inverseT = Mat::createTranslateMatrix(-pos.x,-pos.y,-pos.z);
    return inverseR * inverseT;
}

Mat Mat::createProjMatrix(float fov,float ratio,float near,float far){
    assert(far != near);
    assert(ratio);
    
    float f_n = 1.0f / (far - near);
    float theta = MATH_DEG_TO_RAD(fov) * 0.5f;
    
    float divisor = tan(theta);
    assert(divisor);
    float factor = 1.0f / divisor;
    
    Mat dst;
    dst.m[0] = (1.0f / ratio) * factor;
    dst.m[5] = factor;
    dst.m[10] = (-(far + near)) * f_n;
    dst.m[11] = -1.0f;
    dst.m[14] = -2.0f * far * near * f_n;
    return dst;
}


Mat Mat::createOrthographic(float left, float right, float bottom,
                       float top, float zNearPlane,
                            float zFarPlane){
    // 可能不对 todo
    Mat dst;
    dst.m[0] = 2 / (right - left);
    dst.m[5] = 2 / (top - bottom);
    dst.m[10] = 2 / (zNearPlane - zFarPlane);
    
    dst.m[12] = (left + right) / (left - right);
    dst.m[13] = (top + bottom) / (bottom - top);
    dst.m[14] = (zNearPlane + zFarPlane) / (zNearPlane - zFarPlane);
    dst.m[15] = 1;
    return dst;
}


