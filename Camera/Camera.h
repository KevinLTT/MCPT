#ifndef _CAMERA_H_
#define _CAMERA_H_

#include <cmath>
#include <iostream>
#include <glm/glm.hpp>
#include "../Scene/Normal.h"
#include "../Ray/Ray.h"

//a simple camera whose initial position is ( 0, 0, 0 ) and face direction is ( 0, 0, -1 )
class Camera
{
private:
    glm::vec4 position;
    int width, height;
    float fov;
    float aspectRatio;

    glm::mat4x4 camera2world;

public:
    Camera( int Width = 800, int Height = 600, float Fov = 75 );
    Ray generateRay( int Px, int Py );
    float deg2rad( const float& deg ) { return deg * M_PI / 180; }
    void transform( glm::mat4x4 t );
    int getWidth() { return width; }
    int getHeight() { return height; };
    void showPosition() { std::cout << "x: " << position.x << " y: " << position.y << " z: " << position.z << std::endl; }
};

#endif
