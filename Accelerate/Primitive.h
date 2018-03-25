#ifndef _PRIMITIVE_H_
#define _PRIMITIVE_H_

#include <vector>
#include <memory>

#include "Object.h"
#include "../Scene/Vertex.h"
#include "../Scene/Material.h"

class Primitive : public Object
{
public:
    std::vector<Vertex> vertices;
    std::shared_ptr<Material> material;

public:
    Primitive( std::vector<Vertex> Vertices, std::shared_ptr<Material> m );

    virtual bool intersect();

    void findMaxMin();

};

#endif
