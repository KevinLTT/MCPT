#ifndef _LOADER_H_
#define _LOADER_H_

#include <string>
#include <iostream>
#include <vector>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "Mesh.h"
#include "Vertex.h"
#include "Material.h"

class Loader
{
public:
    void loadModel( const std::string path, std::vector<Mesh>& meshes );
    void processNode( aiNode *node, const aiScene* scene, std::vector<Mesh>& meshes );
    Mesh processMesh( aiMesh* mesh, const aiScene* scene );

};

#endif
