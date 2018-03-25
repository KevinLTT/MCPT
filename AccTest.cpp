#include <iostream>
#include <vector>
#include <memory>

#include "Scene/Scene.h"
#include "Accelerate/AABB.h"
#include "Accelerate/Triangular.h"
#include "Accelerate/Primitive.h"

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

        shared_ptr<Material> m = make_shared<Material>( itr->material );
        vector<Primitive> prims;
        vector<BoundingBox> boxes;
        for( unsigned int i = 0; i < itr->indices.size()-2; i += 3)
        {
            vector<Vertex> tris = { itr->vertices[i], itr->vertices[i+1], itr->vertices[i+2] };
            Primitive prim = Triangular( tris, m );
            BoundingBox box = AABB( prim );

            prims.push_back( prim );
            boxes.push_back( box );
        }

        cout << endl << "Primitive amount: " << prims.size() << endl;
        cout << endl << "Box amount: " << boxes.size() << endl;
    }



    return 0;
}
