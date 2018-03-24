#ifndef _MESH_H_
#define _MESH_H_

#include <vector>
#include <string>

#include "Vertex.h"
#include "Material.h"

class Mesh
{
public:
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;
    Material material;
    
public:
    Mesh( std::vector<Vertex> Vertices, std::vector<unsigned int> Indices, Material material1 ) :
        vertices( Vertices ), indices( Indices ), material( material1 ) {}

    //std::vector<Vertex> getVertices();
    //std::vector<unsigned int> getIndicies();
    //Material getMaterial();
};

#endif
