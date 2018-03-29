#include <string>
#include <vector>
#include <iostream>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "Loader.h"
#include "Mesh.h"
#include "Vertex.h"
#include "Material.h"

void Loader::loadModel( const std::string path, std::vector<Mesh>& meshes )
{
    // read file via ASSIMP
    Assimp::Importer importer;
    const aiScene* scene = importer.ReadFile( path, aiProcess_Triangulate );
    // const aiScene* scene = importer.ReadFile(path, aiProcess_FlipUVs | aiProcess_CalcTangentSpace);
    // check for errors
    if( !scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode ) // if is Not Zero
    {
        std::cout << "ERROR::ASSIMP:: " << importer.GetErrorString() << std::endl;
        return;
    }

    // process ASSIMP's root node recursively
    processNode( scene->mRootNode, scene, meshes );
}

void Loader::processNode( aiNode *node, const aiScene* scene, std::vector<Mesh>& meshes )
{
    // process each mesh located at the current node
    for(unsigned int i = 0; i < node->mNumMeshes; i++)
    {
        // the node object only contains indices to index the actual objects in the scene. 
        // the scene contains all the data, node is just to keep stuff organized (like relations between nodes).
        aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
        meshes.push_back(processMesh(mesh, scene));

    }
    // after we've processed all of the meshes (if any) we then recursively process each of the children nodes
    for(unsigned int i = 0; i < node->mNumChildren; i++)
    {
        processNode(node->mChildren[i], scene, meshes);
    }
}

Mesh Loader::processMesh( aiMesh *mesh, const aiScene* scene )
{
    // data to fill
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;
    
    // Walk through each of the mesh's vertices
    for( unsigned int i = 0; i < mesh->mNumVertices; i++ )
    {
        // position
        glm::vec3 position;
        position.x = mesh->mVertices[i].x;
        position.y = mesh->mVertices[i].y;
        position.z = mesh->mVertices[i].z;

        // normal
        glm::vec3 normal;
        normal.x = -1 * mesh->mNormals[i].x;
        normal.y = -1 * mesh->mNormals[i].y;
        normal.z = -1 * mesh->mNormals[i].z;

        vertices.push_back( Vertex( position, normal ) );
    }

    // walk through each of the mesh's faces and retrieve the corresponding vertex indices
    for( unsigned int i = 0; i < mesh->mNumFaces; i++ )
    {
        aiFace face = mesh->mFaces[i];
        // retrieve all indices of the face and store them in the indices vector
        for( unsigned int j = 0; j < face.mNumIndices; j++ )
            indices.push_back( face.mIndices[j] );
    }

    //process materials
    aiMaterial* aMaterial = scene->mMaterials[mesh->mMaterialIndex];
    Material material( aMaterial );

    return Mesh( vertices, indices, material );
}
