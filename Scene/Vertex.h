#ifndef _VERTEX_H_
#define _VERTEX_H_

#include <glm/glm.hpp>
#include "Material.h"

class Vertex
{
private:
    glm::vec3 position;
    glm::vec3 normal;
    //Material material;

public:
    Vertex( glm::vec3 Position, glm::vec3 Normal ): 
        position( Position ), normal( Normal )  {}

    glm::vec3 getPosition();
    glm::vec3 getNormal();
    Material& getMaterial();

    void setPosition( glm::vec3 );
    void setNormal( glm::vec3 );
    void setMaterial( Material );
};

#endif
