#include <iostream>
#include <vector>
#include <memory>

#include "Scene/Scene.h"
#include "Accelerate/AABB.h"
#include "Accelerate/Triangular.h"
#include "Accelerate/Primitive.h"
#include "Accelerate/KdTree.h"
#include "Camera/Camera.h"
#include <glm/gtc/matrix_transform.hpp>
#include "PathTracing/PathTracing.h"

#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

int main()
{
    //bool hello = true;
    bool hello = false;
    if( hello )
    {
        Vertex A( glm::vec3( 0.0f, 1.0f, 0.0f), glm::vec3( 0.0f, 5.0f, 0.0f ) );
        Vertex B( glm::vec3( -1.0f, 0.0f, 0.0f ), glm::vec3( -0.5f, 0.0f, 0.0f ) );
        Vertex C( glm::vec3( 1.0f, 0.0f, 0.0f ), glm::vec3( 0.5f, 0.0f, 0.0f ) );
        auto m = make_shared<Material>();
        vector<Vertex> tris = { A, B, C};

        Triangular tri( tris, m );

        Vertex origin( glm::vec3( 0.0f, 0.5f, 1.0f ) );
        glm::vec3 direction( 0.3f,  0.00f, -1.0f);
        Ray ray( origin, direction );
        Intersection inter;

        if( tri.intersect( ray, inter ) )
            cout << "hit" << endl;
        else
            cout << "miss" << endl;

        return 0;
    }


    Scene scene( "../Obj/scene01.obj" );

    std::vector<Mesh> meshes = scene.getMeshes();
    std::vector<shared_ptr<Object>> trees;
    Vertex origin( glm::vec3( 2.0f, 2.0f, 6.5f) );
    glm::vec3 direction( 0.0f, 0.00f, -0.5f );
    Ray ray( origin, direction);
    Intersection intersection;
    for( auto itr = meshes.begin()+2; itr != meshes.end()-3; itr++ )
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
        KdTree tt( boxes );
        if( t->intersect( ray, intersection ) == true )
            cout << "hit" << endl;
        else
            cout << "miss" << endl;

        //t.innerObjectList[0]->intersect();
        trees.push_back( t );
        //std::shared_ptr<Object> ptr = std::make_shared<Object>( boxes[0]);
        //auto ptr1 = ptr;

        cout << endl << "Primitive amount: " << prims.size() << endl;
        cout << endl << "Box amount: " << boxes.size() << endl;
    }


    KdTree tree( trees );
    cout << "root: " << tree.innerObjectList.size() << endl;
    //cout << "left" << tree.left->innerObjectList.size() << endl;
    //cout << "right" << tree.right->innerObjectList.size() << endl;


    //tree.intersect( );
    if (tree.intersect( ray, intersection ) )
        cout << "hit" << endl;
    else
        cout << "miss" << endl;

    Camera c;
    Ray r = c.generateRay( 400, 300 );

    /*
    glm::mat4x4 model;
    //model = glm::translate( model, glm::vec3( 0.0f, 0.0f, -5.0f) );
    model = glm::rotate( model, glm::radians( -90.0f), glm::vec3( 1.0f, 0.0f, 0.0f) );
    c.transform( model );

    Ray r1 = c.generateRay( 400, 300 );
    */
    glm::mat4x4 t;
    t = glm::rotate( t, glm::radians( -90.0f ), glm::vec3(0.0f, 0.0f, 1.0f) );
    t = glm::translate( t, glm::vec3( -0.0f, 0.1f, 1.3f) );
    c.transform( t );

    cv::Mat img( 600, 800, CV_8UC1, cv::Scalar(255) );

    int hitNum = 0;
    Intersection inter;
    for( int i = 0; i < c.getHeight(); i++ )
        for( int j = 0; j < c.getWidth(); j++ )
        {
            Ray ray = c.generateRay( j, i );
            if( tree.intersect( ray, inter))
            {
                hitNum++;
                img.at<uchar>( i, j ) = 0;
            }

        }

    cout << "total hit: " << hitNum << endl;

    //cv::imshow( "test", img );
    //cv::waitKey( 0 );

    PathTracing pt;
    shared_ptr<Object> Tree = make_shared<KdTree>( trees );
    cout << Tree->getMax(0) << " " << Tree->getMax(1) << " " << Tree->getMax(2) << endl;
    cout << Tree->getMin(0) << " " << Tree->getMin(1) << " " << Tree->getMin(2) << endl;
    Mat image = pt.render( Tree, c );
    imshow( "test", image );
    waitKey( 0 );

    return 0;
}
