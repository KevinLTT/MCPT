#include <math.h>
#include "Ray.h"

Ray::Ray( Vertex v, glm::vec3 dir ):
    origin( v ), direction( dir )
{}

/*Ray::Ray( Vertex v, glm::vec3 dir )
{
    std::shared_ptr<Vertex> vptr = std::make_shared<Vertex>( v );
    origin = vptr;
}*/

//std::shared_ptr<Vertex> Ray::getOrigin()
Vertex Ray::getOrigin()
{
    return origin;
}

float Ray::getOrigin( int axis )
{
    return origin.getPosition( axis );
}

Normal Ray::getDirection()
{
    return direction;
}

float Ray::getDirection( int axis )
{
    return direction.getNormal( axis );
}
