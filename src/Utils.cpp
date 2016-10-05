//
//  Utils.cpp
//  ShadowMap
//
//  Created by dai on 16/10/5.
//
//

#include "Utils.h"
#include <sys/time.h>


long GetCurrentTime(){
    timeval tv;
    gettimeofday(&tv,nullptr);
    return (tv.tv_sec * 1000000 + tv.tv_usec)/1000;
}

// 计算法线
void CalculateNormals(const unsigned int* pIndices,unsigned int pIndexCount,Vertex* pVertices,unsigned int pVertexCount){
    
    for (unsigned int i = 0 ; i < pIndexCount ; i += 3) {
        unsigned int Index0 = pIndices[i];
        unsigned int Index1 = pIndices[i + 1];
        unsigned int Index2 = pIndices[i + 2];
        Vec3 v1 = pVertices[Index1].position - pVertices[Index0].position;
        Vec3 v2 = pVertices[Index2].position - pVertices[Index0].position;
        Vec3 Normal = v1.cross(v2);
        Normal.normalize();
        
        pVertices[Index0].normal += Normal;
        pVertices[Index1].normal += Normal;
        pVertices[Index2].normal += Normal;
    }
    for (unsigned int i = 0 ; i < pVertexCount ; i++) {
        pVertices[i].normal.normalize();
    }
}