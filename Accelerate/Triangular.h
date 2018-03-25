#ifndef _TRIANGULAR_H_
#define _TRIANGULAR_H_

#include <memory>
#include <vector>
#include <iostream>

#include "../Scene/Scene.h"
#include "../Scene/Material.h"
#include "Primitive.h"

class Triangular : public Primitive
{
public:
    Triangular( std::vector<Vertex> v, std::shared_ptr<Material> m ) :
        Primitive( v, m ) {}

    virtual bool intersect();
};

#endif


