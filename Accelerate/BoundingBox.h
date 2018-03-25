#ifndef _BOUNDING_BOX_H
#define _BOUNDING_BOX_H

#include "Primitive.h"
#include "Geometry.h"

class BoundingBox : public Object
{
public:
    Object innerObject;

public:
    BoundingBox( Object inner ):
        innerObject( inner ) {}
};

#endif
