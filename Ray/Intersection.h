#ifndef _INTERSECTION_H_
#define _INTERSECTION_H_

#include <memory>

#include "../Scene/Scene.h"
#include "../Config/config.h"
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
    bool valid;

public:
    Intersection() { valid = false; }
    void set( Vertex v, float t, std::shared_ptr<Material> m, std::shared_ptr<Object> o )
    {
        if( t < EPSILON )
            return;

        if( valid == false || t < this->t )
        {
            valid = true;
            point = v;
            this->t  = t;
            material = m;
            obj = o;
        }
    }
};

#endif
