#include <iostream>
#include <vector>

#include "Scene/Scene.h"

using namespace std;

int main()
{
    Scene scene( "../Obj/scene01.obj" );

    std::vector<Mesh> meshes = scene.getMeshes();
    for( auto itr = meshes.begin(); itr != meshes.end(); itr++ )
    {
        itr->material.show();
        cout << "Vertex amount: " << itr->vertices.size() << endl;
        cout << "Index amount: " << itr->indices.size() << endl;
    }

    return 0;
}
