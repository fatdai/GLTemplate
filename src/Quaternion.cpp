//
//  Quaternion.cpp
//  GLFW_DrawTriangle
//
//  Created by dai on 16/10/3.
//
//

#include "Quaternion.h"
#include "Vec3.h"
#include <cmath>


Quaternion::Quaternion(){
    x = y = z = 0;
    w = 1;
}

Quaternion::Quaternion(float px,float py,float pz,float pw){
    x = px;
    y = py;
    z = pz;
    w = pw;
}

Quaternion Quaternion::conjugate(){
    return Quaternion(-x,-y,-z,w);
}

Quaternion Quaternion::operator*(const Quaternion& other){
    Vec3 pv(x,y,z);
    Vec3 qv(other.x,other.y,other.z);
    Quaternion ret;
    ret.w = w * other.w - pv * qv;
    Vec3 v = w * qv + other.w * pv + pv.cross(qv);
    ret.x = v.x;
    ret.y = v.y;
    ret.z = v.z;
    return ret;
}

float Quaternion::length(){
    return sqrtf(x * x + y * y + z * z + w * w);
}

void Quaternion::normalize(){
    float len = length();
    if (len > 0) {
        x /= len;
        y /= len;
        z /= len;
        w /= len;
    }
}




