#include <iostream>
#include <opencv2/opencv.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Scene/Scene.h"
#include "Accelerate/Accelerate.h"
#include "Camera/Camera.h"
#include "PathTracing/PathTracing.h"
#include "Ray/Ray.h"

using namespace std;
using namespace cv;

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 800
#define FOV 70

#define MOVE_SPEED 1

#define LEFT 97
#define UP 119
#define RIGHT 100
#define DOWN 115
#define QUIT 113
#define TURN_LEFT 106
#define TURN_RIGHT 107
#define ZOOM_IN 105
#define ZOOM_OUT 111

#define LOOK_DOWN 102
#define LOOK_UP 114

int main()
{
    /*
    vector<Vertex> vs;
    vs.push_back( Vertex(glm::vec3( 5.76, 0, 5 ) ) );
    vs.push_back( Vertex(glm::vec3( 5.76, 0, -5 ) ) );
    vs.push_back( Vertex(glm::vec3( 5.76, 10, -5 ) ) );
    vs.push_back( Vertex(glm::vec3( 5.76, 10, 5 ) ) );
    vector<unsigned int> indices;
    indices.push_back( 0 );
    indices.push_back( 1 );
    indices.push_back( 2 );
    indices.push_back( 0 );
    indices.push_back( 2 );
    indices.push_back( 3 );
    Mesh me( vs, indices, ma );

    vector<Vertex>
    shared_ptr<Object> o1 = make_shared<Triangular>( )
    */

    /*auto ma = make_shared<Material>();
    ma->diffuse = glm::vec3( 0, 0, 1 );

    auto v1 = Vertex(glm::vec3( 5.76, 0, 5 ) ) ;
    auto v2 = Vertex(glm::vec3( 5.76, 0, -5 ) ) ;
    auto v3 = Vertex(glm::vec3( 5.76, 10, -5 ) );
    auto v4 = Vertex(glm::vec3( 5.76, 10, 5 ) );

    vector<Vertex> vs1 = { v1, v2, v3 };
    vector<Vertex> vs2 = { v1, v3, v4 };
    shared_ptr<Object> tri1 = make_shared<Triangular>( vs1, ma );
    shared_ptr<Object> tri2 = make_shared<Triangular>( vs2, ma );
    //tri1->showMaxMin();
    //tri2->showMaxMin();

    vector<shared_ptr<Object>> objs;
    objs.push_back( tri1 );
    objs.push_back( tri2 );
    std::shared_ptr<Object> triTree = make_shared<KdTree>( objs );
    //triTree->showMaxMin();
    KdTree tttt = KdTree( objs );
*/
    Scene scene( "../Obj/scene01.obj" );
    vector<Mesh> meshes;
    auto wall = scene.getMeshes().at(0);
    auto light = scene.getMeshes().at(4);
    auto wallBox = KdTree::buildTree( wall );
    auto ligthBox  = KdTree::buildTree( light );
    auto b1 = *wallBox;
    auto b2 = *ligthBox;
    Material temp = wall.material;
    wall.material = light.material;
    light.material = temp;
    meshes.push_back( scene.getMeshes().at(0)); //中墙
    //meshes.push_back( scene.getMeshes().at(1)); //右边蓝墙
    //meshes.push_back( scene.getMeshes().at(2)); //左边红墙
    //meshes.push_back( scene.getMeshes().at(3)); //左边球
    meshes.push_back( scene.getMeshes().at(4)); //顶灯
    //meshes.push_back( scene.getMeshes().at(5)); //右边球
    scene.getMeshes().at(0).material.show();
    scene.getMeshes().at(1).material.show();
    scene.getMeshes().at(2).material.show();
    scene.getMeshes().at(3).material.show();
    scene.getMeshes().at(4).material.show();
    scene.getMeshes().at(5).material.show();
    //std::shared_ptr<Object> tree = KdTree::buildTree( meshes );
    std::shared_ptr<Object> tree = KdTree::buildTree( scene.getMeshes() );
    auto t1 = KdTree::buildTree( meshes );
    KdTree t2 = *t1;

    Camera camera( SCREEN_WIDTH, SCREEN_HEIGHT, FOV );
    PathTracing tracer;

    /*
    glm::mat4x4 t;
    t = glm::translate( t, glm::vec3( -0.0f, 0.3f, 1.3f) );
    t = glm::rotate( t, glm::radians( -0.0f ), glm::vec3(0.0f, 0.0f, 1.0f) );
    camera.transform( t );
    auto img = tracer.render( tree, camera );
    imshow( "test", img );
    waitKey( 0 );
     */

    Normal n( glm::vec3( -1, 1, 0) );
    auto sample = tracer.uniformSampleHemisphere( n );
    cout << sample.x << " " << sample.y << " " << sample.z << endl;

    glm::vec3 g1( 1, 1, 1 );
    glm::vec3 g2( 0.1, 0.2, 0.3 );
    auto g3 = g1*g2;

    float angle = -0;
    float tx = 0;
    float ty = 4.6;
    float tz = 13.5;

    bool end = false;
    while( !end )
    {
        glm::mat4x4 t;
        t = glm::translate( t, glm::vec3( tx, ty, tz) );
        t = glm::rotate( t, glm::radians( angle), glm::vec3( 1.0f, 0.0f, 0.0f ) );
        //t = glm::rotate( t, glm::radians( angle1 ), glm::vec3( 1.0f, 0, 0 ) );
        camera.transform( t );
        camera.showPosition();

        auto img = tracer.render( tree, camera );
        cv::imwrite( "out.jpg", img );

        imshow( "test", img );
        int key = waitKey( 0 );
        switch( key )
        {
            case UP:
                ty += MOVE_SPEED;
                break;
            case DOWN:
                ty -= MOVE_SPEED;
                break;
            case LEFT:
                tx -= MOVE_SPEED;
                break;
            case RIGHT:
                tx += MOVE_SPEED;
                break;
            case ZOOM_IN:
                tz -= MOVE_SPEED;
                break;
            case ZOOM_OUT:
                tz += MOVE_SPEED;
                break;
            case QUIT:
                end = true;
                break;
            case TURN_LEFT:
                angle--;
                break;
            case TURN_RIGHT:
                angle++;
                break;
            default:
                break;
        }
    }



    return 0;
}
