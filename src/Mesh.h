//
//  Mesh.h
//  Lighting
//
//  Created by dai on 16/10/4.
//
//

#ifndef __Lighting__Mesh__
#define __Lighting__Mesh__

#include <stdio.h>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <string>
#include "MyHead.h"
#include "Texture.h"
#include <vector>
using namespace std;

struct Vertex{
    
    Vec3 position;
    Vec2 texCoord;
    Vec3 normal;
    
    Vertex(const Vec3& pos,const Vec2& tex){
        position = pos;
        texCoord = tex;
    }
    
    Vertex(const Vec3& pos,const Vec2& tex,const Vec3& nor){
        position = pos;
        texCoord = tex;
        normal = nor;
    }
};

//-----------------------------------

class Mesh{
    
public:
    
    Mesh();
    ~Mesh();
    
    bool LoadMesh(const std::string& Filename);
    
    void Render();
    
private:
    
    bool InitFromScene(const aiScene* pScene, const std::string& Filename);
    void InitMesh(unsigned int Index, const aiMesh* paiMesh);
    bool InitMaterials(const aiScene* pScene, const std::string& Filename);
    void Clear();
    
#define INVALID_MATERIAL 0xFFFFFFFF
    
    struct MeshEntry {
        MeshEntry();
        ~MeshEntry();
        void Init(const std::vector<Vertex>& Vertices,
                  const std::vector<unsigned int>& Indices);
        GLuint VAO;
        GLuint VB;
        GLuint IB;
        unsigned int NumIndices;
        unsigned int MaterialIndex;
    };
    
    std::vector<MeshEntry> m_Entries;
    std::vector<Texture*> m_Textures;
};







#endif /* defined(__Lighting__Mesh__) */
