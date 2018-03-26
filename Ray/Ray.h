#ifndef _RAY_H_
#define _RAY_H_

#include <glm/glm.hpp>
#include <memory>

#include "../Scene/Scene.h"

class Ray
{
public:
    //std::shared_ptr<Vertex> origin;
    Vertex origin;
    glm::vec3 direction;
    float t;

public:
    Ray() = default;
    Ray( Vertex v, glm::vec3 dir );
    //Ray( std::shared_ptr<Vertex> vptr, glm::vec3 dir );

    //std::shared_ptr<Vertex> getOrigin();
    Vertex getOrigin();
    float getOrigin( int axis );
    glm::vec3 getDirection();
    float getDirection( int axis );

    void normalize();
};

#endif
