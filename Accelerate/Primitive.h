#ifndef _PRIMITIVE_H_
#define _PRIMITIVE_H_

#include <vector>
#include <memory>

#include "Geometry.h"
#include "../Scene/Vertex.h"
#include "../Scene/Material.h"

class Primitive : public Object
{
public:
    std::shared_ptr<Material> material;

public:
    Primitive( std::vector<Vertex> Vertices, std::shared_ptr<Material> m ):
        Object( Vertices ), material( m ) {}
    
};

#endif
