#ifndef _GEOMETRY_H_
#define _GEOMETRY_H_

#include "../Scene/Scene.h"

class Object
{
public:
    std::vector<Vertex> vertices;

public:
    Object(  ) {}
    Object( std::vector<Vertex> v ):
        vertices( v ) {}

};

#endif
