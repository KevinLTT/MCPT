#ifndef _NORMAL_H_
#define _NORMAL_H_

#include <glm/glm.hpp>
#include <math.h>
#include "../Config/config.h"

class Normal
{
private:
    glm::vec3 normal;

public:
    Normal( glm::vec3 n ):
        normal(n)
    {
        normalize();
    }

    Normal(): normal( glm::vec3( 0.0f, 0.0f, 0.0f ) ) {}

    glm::vec3 getNormal() { return normal; }

    float getNormal( int axis )
    {
        switch( axis )
        {
        case X_AXIS:    return normal.x;
        case Y_AXIS:    return normal.y;
        case Z_AXIS:    
        default:        return normal.z;
        }
    }

    bool check()
    {
        if( fabs(normal.x) + fabs(normal.y) + fabs(normal.z) > EPSILON  )
            return true;
        else
            return false;
    }

    void normalize()
    {
        if( check() == true )
        {
            float squareSum = sqrt(normal.x*normal.x + normal.y*normal.y + normal.z*normal.z );
            normal.x = normal.x / squareSum;
            normal.y = normal.y / squareSum;
            normal.z = normal.z / squareSum;
        }
    }

    void setNormal( glm::vec3 n )
    {
        normal = n;
        normalize();
    }
};

#endif
