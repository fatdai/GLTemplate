//
//  Vec3.cpp
//  GLFW_DrawTriangle
//
//  Created by dai on 16/10/3.
//
//

#include "Vec3.h"
#include <cmath>
#include "MyDefines.h"

const Vec3 Vec3::XAxis = Vec3(1,0,0);
const Vec3 Vec3::YAxis = Vec3(0,1,0);
const Vec3 Vec3::ZAxis = Vec3(0,0,1);

Vec3::Vec3(){
    
}
Vec3::Vec3(float px,float py,float pz){
    x = px;
    y = py;
    z = pz;
}

Vec3::Vec3(const Vec3& other){
    x = other.x;
    y = other.y;
    z = other.z;
}

void Vec3::rotate(float degress,const Vec3& axis){
    float rad = MATH_DEG_TO_RAD(degress);
    float sin = sinf(rad/2);
    float cos = cosf(rad/2);
    
    Quaternion p(x,y,z,0);
    Quaternion q(sin * axis.x,sin * axis.y,sin * axis.z,cos);
    Quaternion conjugate = q.conjugate();
    Quaternion ret = q * p * conjugate;
    x = ret.x;
    y = ret.y;
    z = ret.z;
}

void Vec3::normalize(){
    float len = length();
    if (len > 0) {
        x /= len;
        y /= len;
        z /= len;
    }
}
float Vec3::length(){
    return sqrtf(x * x + y * y + z * z);
}

Vec3 Vec3::operator+(const Vec3& other)const{
    return Vec3(x + other.x,y + other.y, z + other.z);
}

Vec3& Vec3::operator+=(const Vec3& other){
    x += other.x;
    y += other.y;
    z += other.z;
    return *this;
}

Vec3& Vec3::operator-=(const Vec3& other){
    x -= other.x;
    y -= other.y;
    z -= other.z;
    return *this;
}

Vec3 Vec3::operator-(const Vec3& other)const{
    return Vec3(x - other.x,y - other.y,z - other.z);
}
float Vec3::operator*(const Vec3& other)const{
    return (x * other.x + y * other.y + z * other.z);
}
Vec3 Vec3::cross(const Vec3& other) const{
    return Vec3(y * other.z - z * other.y,z * other.x - x * other.z,x * other.y - y * other.x);
}

Vec3 Vec3::cross(const Vec3& other){
    return Vec3(y * other.z - z * other.y,z * other.x - x * other.z,x * other.y - y * other.x);
}

Vec3 Vec3::operator*(float t)const{
    return Vec3(x * t , y * t, z * t);
}

Vec3 Vec3::operator/(float t)const{
    if (t == 0) {
        return Vec3();
    }
    return  Vec3(x/t,y/t,z/t);
}

void Vec3::print(){
    printf("-------------------------------\n");
    printf("%.3f,%.3f,%.3f\n",x,y,z);
}



//---------------------------------------
// Global
bool operator==(const Vec3& v1,const Vec3& v2){
    if (v1.x == v2.x && v1.y == v2.y && v1.z == v2.z) {
        return true;
    }
    return false;
}


Vec3 operator*(float t,const Vec3& v){
    return Vec3(t * v.x, t * v.y, t * v.z);
}


Vec3 operator/(float t,const Vec3& v){
    if (t == 0) {
        return Vec3();
    }
    return Vec3(v.x/t,v.y/t,v.z/t);
}

Vec3 operator-(const Vec3& v){
    return Vec3(-v.x, -v.y, -v.z);
}
