//
//  Camera.cpp
//  BasicMove
//
//  Created by dai on 16/10/4.
//
//

#include "Camera.h"

const static float kMoveSpeed = 1.0f;
const static float kRotateSpeed = 5;


const static int sPosDirty = 0x0001;
const static int sRotateDirty = 0x0010;
const static int sAllDirty = (sPosDirty | sRotateDirty);


Camera::Camera(){
    mPos = Vec3(0, 0, 0);
    mHead = Vec3(0, 0, -1);
    mUp = Vec3(0, 1, 0);
    mDirty = sAllDirty;
}

Camera::Camera(const Vec3& pos,const Vec3& head,const Vec3& up){
    mPos = pos;
    mHead = head;
    mUp = up;
    mHead.normalize();
    mDirty = sAllDirty;
}

void Camera::update(){
    
    // 更新相机旋转相关
    if (mDirty & sRotateDirty) {
        // 先计算相机的 left
        mLeft = Vec3::YAxis.cross(mHead);
        mLeft.normalize();
        
        // 计算 up
        mUp = mHead.cross(mLeft);
        mUp.normalize();
    }
    
    // 更新 viewMatrix
    if (mDirty & sAllDirty) {
        mViewMatrix = Mat::createViewMatrix(mPos,mHead,mUp);
        mDirty = 0;
    }
}

void Camera::forward(){
    Vec3 tmp(mHead.x,0,mHead.z);
    mPos += (tmp * kMoveSpeed);
    mDirty |= sPosDirty;
}

void Camera::back(){
    Vec3 tmp(mHead.x,0,mHead.z);
    mPos -= tmp * kMoveSpeed;
    mDirty |= sPosDirty;
}
void Camera::left(){
    // 其实就是旋转 mHead
    mHead.rotate(kRotateSpeed,Vec3::YAxis);
    mHead.normalize();
    mDirty |= sRotateDirty;
}

void Camera::right(){
    mHead.rotate(-kRotateSpeed,Vec3::YAxis);
    mHead.normalize();
    mDirty |= sRotateDirty;
}

void Camera::lookUp(){
    mHead.rotate(-kRotateSpeed,Vec3::XAxis);
    mHead.normalize();
    mDirty |= sRotateDirty;
}
void Camera::lookDown(){
    mHead.rotate(kRotateSpeed,Vec3::XAxis);
    mHead.normalize();
    mDirty |= sRotateDirty;
}