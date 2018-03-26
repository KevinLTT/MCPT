#include <math.h>
#include "Ray.h"

Ray::Ray( Vertex v, glm::vec3 dir ):
    origin( v ), direction( dir )
{
    normalize();
}

/*Ray::Ray( Vertex v, glm::vec3 dir )
{
    std::shared_ptr<Vertex> vptr = std::make_shared<Vertex>( v );
    origin = vptr;
}*/

void Ray::normalize()
{
    
    double normalize = sqrt( direction.x*direction.x + direction.y*direction.y + direction.z*direction.z  ) ;
    direction.x = direction.x / normalize;
    direction.y = direction.y / normalize;
    direction.z = direction.z / normalize;
}

//std::shared_ptr<Vertex> Ray::getOrigin()
Vertex Ray::getOrigin()
{
    return origin;
}

float Ray::getOrigin( int axis )
{
    return origin.getPosition( axis );
}

glm::vec3 Ray::getDirection()
{
    return direction;
}

float Ray::getDirection( int axis )
{
    switch( axis )
    {
    case X_AXIS: return direction.x;
    case Y_AXIS: return direction.y;
    case Z_AXIS: 
    default: return direction.z;
    }
}
