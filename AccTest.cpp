#include <iostream>
#include <vector>
#include <memory>

#include "Scene/Scene.h"
#include "Accelerate/AABB.h"
#include "Accelerate/Triangular.h"
#include "Accelerate/Primitive.h"
#include "Accelerate/KdTree.h"

using namespace std;

int main()
{
    Scene scene( "../Obj/scene01.obj" );

    std::vector<Mesh> meshes = scene.getMeshes();
    std::vector<shared_ptr<Object>> trees;
    Ray ray;
    Intersection intersection;
    for( auto itr = meshes.begin()+0; itr != meshes.end()-0; itr++ )
    {
        itr->material.show();
        cout << "Vertex amount: " << itr->vertices.size() << endl;
        cout << "Index amount: " << itr->indices.size() << endl;

        shared_ptr<Material> m = make_shared<Material>( itr->material );
        vector<shared_ptr<Object>> prims;
        vector<shared_ptr<Object>> boxes;
        for( unsigned int i = 0; i < itr->indices.size()-2; i += 3)
        {
            vector<Vertex> tris = { itr->vertices[i], itr->vertices[i+1], itr->vertices[i+2] };
            shared_ptr<Object> prim = make_shared<Triangular>( tris, m );
            shared_ptr<Object> box = make_shared<AABB>( prim );
            //box->intersect( ray, intersection );

            prims.push_back( prim );
            boxes.push_back( box );

            Intersection inter;
        }
        //boxes[0]->intersect();

        //KdTree t( boxes );
        shared_ptr<Object> t = make_shared<KdTree>( boxes );
        t->intersect( ray, intersection );
        //t->intersect();
        //t.innerObjectList[0]->intersect();
        trees.push_back( t );
        //std::shared_ptr<Object> ptr = std::make_shared<Object>( boxes[0]);
        //auto ptr1 = ptr;

        cout << endl << "Primitive amount: " << prims.size() << endl;
        cout << endl << "Box amount: " << boxes.size() << endl;
    }

    KdTree tree( trees );
    cout << "root: " << tree.innerObjectList.size() << endl;
    cout << "left" << tree.left->innerObjectList.size() << endl;
    cout << "right" << tree.right->innerObjectList.size() << endl;

    //tree.intersect( );
    tree.intersect( ray, intersection );

    return 0;
}
