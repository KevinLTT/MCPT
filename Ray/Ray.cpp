#include <math.h>

#include "Ray.h"

Ray::Ray( Vertex v, glm::vec3 dir ):
    origin( v ), direction( dir )
{
    normalize();
}

void Ray::normalize()
{
    
    double normalize = sqrt( direction.x*direction.x + direction.y*direction.y + direction.z*direction.z  ) ;
    direction.x = direction.x / normalize;
    direction.y = direction.y / normalize;
    direction.z = direction.z / normalize;
}
