#ifndef _SCENE_H_
#define _SCENE_H_

#include <vector>
#include <string>

#include "Mesh.h"

class Scene
{
private:
    std::vector<Mesh> meshes;

public:
    Scene( std::string path );
    std::vector<Mesh> getMeshes();
};

#endif
