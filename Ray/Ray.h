#ifndef _RAY_H_
#define _RAY_H_

#include <glm/glm.hpp>
#include <memory>

#include "../Scene/Scene.h"
#include "../Scene/Normal.h"

class Ray
{
public:
    //std::shared_ptr<Vertex> origin;
    Vertex origin;
    //glm::vec3 direction;
    Normal direction;
    float t;

public:
    Ray() = default;
    Ray( Vertex v, glm::vec3 dir );
    Ray( Vertex v, Normal d ): origin(v), direction(d) {}
    //Ray( std::shared_ptr<Vertex> vptr, glm::vec3 dir );

    //std::shared_ptr<Vertex> getOrigin();
    Vertex getOrigin();
    float getOrigin( int axis );
    Normal& getDirection();
    float getDirection( int axis );
    glm::vec3 reflectDirection( Normal N );
    bool able2refract( glm::vec3 normal, float nit, glm::vec3& refractDirection );

    void normalize();
};

#endif
