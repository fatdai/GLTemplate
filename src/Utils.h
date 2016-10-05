//
//  Utils.h
//  ShadowMap
//
//  Created by dai on 16/10/5.
//
//

#ifndef __ShadowMap__Utils__
#define __ShadowMap__Utils__

#include <stdio.h>
#include "Mesh.h"

// 返回当前时间,毫秒为单位
long GetCurrentTime();

// 计算法线
void CalculateNormals(const unsigned int* pIndices,unsigned int pIndexCount,Vertex* pVertices,unsigned int pVertexCount);

#endif /* defined(__ShadowMap__Utils__) */
