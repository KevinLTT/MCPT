#ifndef _BOUNDING_BOX_H
#define _BOUNDING_BOX_H

#include <memory>
#include <vector>

#include "Primitive.h"
#include "Object.h"

class BoundingBox : public Object
{
public:
    std::vector< std::shared_ptr<Object> > innerObjectList;

public:
    BoundingBox( std::shared_ptr<Object> inner );
    BoundingBox( std::vector< std::shared_ptr<Object> > objectList );

    virtual bool  intersect( Ray ray, Intersection& intersection ) = 0;
    //virtual bool  intersect();

    void findMaxMin();
};

#endif
