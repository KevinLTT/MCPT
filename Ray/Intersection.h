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
    float t;
    std::shared_ptr<Material> material;
    std::shared_ptr<Object> obj;

public:
    Intersection() = default;
};

#endif
