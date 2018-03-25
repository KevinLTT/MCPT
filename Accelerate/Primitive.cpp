#include <algorithm>
#include <iostream>

#include "Primitive.h"

Primitive::Primitive( std::vector<Vertex> Vertices, std::shared_ptr<Material> m ):
    vertices( Vertices ), material( m ) 
{
    findMaxMin();
}

bool Primitive::intersect()
{
    std::cout << "Primitive" << std::endl;
    return true;
}

void Primitive::findMaxMin()
{
    for( auto v = vertices.begin(); v != vertices.end(); v++ )
    {
        max.x = fmax( max.x, v->position.x );
        max.y = fmax( max.y, v->position.y );
        max.z = fmax( max.z, v->position.z );

        min.x = fmin( min.x, v->position.x );
        min.y = fmin( min.y, v->position.y );
        min.z = fmin( min.z, v->position.z );
    }
}
