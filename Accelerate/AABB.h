#ifndef _AABB_H_
#define _AABB_H_

#include <iostream>

#include "Triangular.h"
#include "../Scene/Scene.h"
#include "BoundingBox.h"

#define AABB_MAX 10000000
#define AABB_MIN -10000000

#define AABB_MAX_INDEX 0
#define AABB_MIN_INDEX 1

class AABB : public BoundingBox
{
public:
    //AABB( Object inner ): BoundingBox( inner ) {}
    AABB( std::shared_ptr<Object> inner ): BoundingBox( inner ) {}
    //AABB( std::vector<Object> innerList ): BoundingBox( innerList ) {}
    AABB( std::vector< std::shared_ptr<Object> > innerList ): BoundingBox( innerList ) {}

    virtual bool intersect( Ray ray, Intersection& intersection );
    bool boxIntersect( Ray ray );
    //virtual bool intersect( );
    //void initialize();
    //void findMaxMin();
    //Vertex getMax() { return this->vertices[AABB_MAX_INDEX]; }
    //Vertex getMin() { return this->vertices[AABB_MAX_INDEX]; }
};

#endif
