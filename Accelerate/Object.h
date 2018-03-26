#ifndef _GEOMETRY_H_
#define _GEOMETRY_H_

#include <iostream>

#include "../Scene/Scene.h"
#include "../Ray/Ray.h"
#include "../Ray/Intersection.h"

#define OBJECT_MAX 10000000
#define OBJECT_MIN -1000000

#define X_AXIS 0
#define Y_AXIS 1
#define Z_AXIS 2

#define EPSILON 0.00001

class Object
{
public:
    glm::vec3 max, min;

public:
    Object( ) 
    { 
        max.x = max.y = max.z = OBJECT_MIN;  
        min.x = min.y = min.z = OBJECT_MAX;
    }

    glm::vec3 getMax() { return max; }
    float getMax( int axis )
    {
        switch( axis )
        {
        case X_AXIS: 
            return max.x;
        case Y_AXIS:
            return max.y;
        case Z_AXIS:
        default:
            return max.z;
        }
    }
    glm::vec3 getMin() { return min; }
    float getMin( int axis )
    {
        switch( axis )
        {
        case X_AXIS: 
            return min.x;
        case Y_AXIS:
            return min.y;
        case Z_AXIS:
        default:
            return min.z;
        }
    }

    //virtual bool intersect() { std::cout << "Object" << std::endl; return true; }
    virtual bool intersect( Ray ray, Intersection& intersection ) = 0; //.{ std::cout << "Object" << std::endl; return false; };

};

#endif
