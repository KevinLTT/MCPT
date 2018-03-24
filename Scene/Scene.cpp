#include <string>
#include <vector>
#include <iostream>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "Scene.h"
#include "Mesh.h"
#include "Vertex.h"
#include "Material.h"
#include "Loader.h"

Scene::Scene ( std::string path )
{
    Loader loader;
    loader.loadModel( path, meshes );
}

std::vector<Mesh> Scene::getMeshes()
{
    return meshes;
}

