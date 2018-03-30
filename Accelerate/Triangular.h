#ifndef _TRIANGULAR_H_
#define _TRIANGULAR_H_

#include <memory>
#include <vector>
#include <iostream>

#include "../Scene/Scene.h"
#include "../Scene/Material.h"
#include "Primitive.h"
#include "../Config/config.h"

class Triangular : public Primitive
{
private:
    glm::vec3 A, B, C;
    glm::vec3 vectorAB, vectorAC;

public:
    Triangular( std::vector<Vertex> v, std::shared_ptr<Material> m );

    virtual bool intersect( Ray ray, Intersection& intersection );
    //virtual bool intersect();

    float determinant3x3( glm::vec3 column, glm::vec3 column2, glm::vec3 column3 );
};

#endif


