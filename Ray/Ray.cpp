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

Normal& Ray::getDirection()
{
    return direction;
}

float Ray::getDirection( int axis )
{
    return direction.getNormal( axis );
}

glm::vec3 Ray::reflectDirection( Normal N) {
    Normal reflect(direction.getNormal() - 2.0f * glm::dot( N.getNormal(), direction.getNormal() ) * N.getNormal());
    return reflect.getNormal();
}

bool Ray::able2refract( glm::vec3 normal, float nit, glm::vec3& refractDirection )
{
    float ndoti = glm::dot( normal, direction.getNormal()  );
    float k = 1.0f - nit*nit*( 1.0f - ndoti * ndoti );
    if( k >= 0.0f )
    {
        refractDirection = nit*direction.getNormal() - normal * ( nit*ndoti + sqrtf(k) );
        Normal temp( refractDirection );
        refractDirection = temp.getNormal();
        return true;
    }
    else
        return false;
}
