#include <iostream>
#include <sstream>
#include <opencv2/opencv.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Scene/Scene.h"
#include "Accelerate/Accelerate.h"
#include "Camera/Camera.h"
#include "PathTracing/PathTracing.h"

using namespace std;
using namespace cv;

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 800
#define FOV 70

int main( int argc, char** argv )
{
    int ssp = 10;
    if( argc >= 3 )
        ssp = std::atoi( argv[2] );

    Scene scene( argv[1] );
    std::shared_ptr<Object> tree = KdTree::buildTree( scene.getMeshes() );
    Camera camera( SCREEN_WIDTH, SCREEN_HEIGHT, FOV );
    PathTracing tracer;
    // ball
    
    float tx = 0;
    float ty = 4.6;
    float tz = 13.5;
    

    // wall
    
    //float tx = 1.5;
    //float ty = 5.464;
    //float tz = 16;

    //cornell
    //float tx = -0.01;
    //float ty = 0.79495;
    //float tz = 2.5;
    
    

    glm::mat4x4 t;
      t = glm::translate( t, glm::vec3( tx, ty, tz) );
      camera.transform( t );
      //camera.showPosition();
    //camera.setPosition( tree );
    //camera.showPosition();

    auto img = tracer.render( tree, camera, ssp );

    //imshow( "Result", img );
    //waitKey( 0 );

    stringstream ss;
    ss << argv[1] << "_" << ssp << ".jpg";
    cout << ss.str() << endl;
    imwrite( ss.str(), img );

    return 0;
}
