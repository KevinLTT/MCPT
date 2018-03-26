#ifndef _INTERSECTION_H_
#define _INTERSECTION_H_

#include <memory>

#include "../Scene/Scene.h"
//#include "../Accelerate/Object.h"
//#include "../Accelerate/Primitive.h"
//class Primitive;
class Object;

class Intersection
{
public:
    Vertex point;
    Material material;
    std::shared_ptr<Object> obj;

public:
    Intersection() = default;
};

#endif
