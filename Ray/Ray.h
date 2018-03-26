#ifndef _RAY_H_
#define _RAY_H_

#include <glm/glm.hpp>

#include "../Scene/Scene.h"

class Ray
{
public:
    Vertex origin;
    glm::vec3 direction;
    float t;

public:
    Ray() = default;
    Ray( Vertex v, glm::vec3 dir );

    void normalize();
};

#endif
