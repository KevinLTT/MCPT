#ifndef _VERTEX_H_
#define _VERTEX_H_

#include <glm/glm.hpp>
#include <math.h>
#include "Material.h"
#include "Normal.h"

#define X_AXIS 0
#define Y_AXIS 1
#define Z_AXIS 2

class Vertex
{
public:
    glm::vec3 position;
    //glm::vec3 normal;
    Normal normal;
    //Material material;

public:
    Vertex( glm::vec3 Position, glm::vec3 Normal ): 
        position( Position ), normal( Normal )  {  }
    Vertex( glm::vec3 Position ):
        position( Position ), normal( glm::vec3( 0, 0, 0 ) ) {  }
    Vertex() = default;

    glm::vec3 getPosition() { return position; };
    float getPosition( int axis )
    {
        switch( axis )
        {
            case X_AXIS:
                return position.x;
            case Y_AXIS:
                return position.y;
            case Z_AXIS:
            default:
                return position.z;
        } 
    }
    
    glm::vec3 getNormal() { return normal.getNormal(); }

    float getNormal( int axis )
    {
        return normal.getNormal( axis );
    }

    void setPosition( glm::vec3 p )
    {
        position = p;
    }
    void setNormal( glm::vec3 n )
    {
        normal = Normal( n );
    }
};

#endif
