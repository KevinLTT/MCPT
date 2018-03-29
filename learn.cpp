#include <cmath>
#include <stdlib.h>
#include <stdio.h>

void radiance( const Ray &r, int depth, unsigned short *Xi )
{
    double t; //distance to intersection
    int id = 0; //id of intersected object

    if( !intersect( r, t, id ) )
        return black;

    const Object 
}
