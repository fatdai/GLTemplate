//
//  Vec3.h
//  GLFW_DrawTriangle
//
//  Created by dai on 16/10/3.
//
//

#ifndef __GLFW_DrawTriangle__Vec3__
#define __GLFW_DrawTriangle__Vec3__

#include <stdio.h>
#include "Quaternion.h"

class Vec3{
    
public:
    
    float x = 0;
    float y = 0;
    float z = 0;
    
    Vec3();
    Vec3(float px,float py,float pz);
    Vec3(const Vec3& other);
    
    // r饶 axis 旋转 degress ,要求 axis 必须已经 归一化
    void rotate(float degress,const Vec3& axis);
    void normalize();
    float length();
    void print();
    
    Vec3 operator+(const Vec3& other) const;
    Vec3 operator-(const Vec3& other) const;
    float operator*(const Vec3& other) const;
    Vec3 operator*(float t) const;
    Vec3 operator/(float t) const;
    
    Vec3& operator+=(const Vec3& other);
    Vec3& operator-=(const Vec3& other);
    
    Vec3 cross(const Vec3& other) const;
    Vec3 cross(const Vec3& other);
    
    
    const static Vec3 XAxis;
    const static Vec3 YAxis;
    const static Vec3 ZAxis;
};


bool operator==(const Vec3& v1,const Vec3& v2);
Vec3 operator*(float t,const Vec3& v);
Vec3 operator/(float t,const Vec3& v);
Vec3 operator-(const Vec3& v);


#endif /* defined(__GLFW_DrawTriangle__Vec3__) */
