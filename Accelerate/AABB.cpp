#include <algorithm>

#include "AABB.h"


bool AABB::intersect( Ray ray, Intersection& intersection ) 
{ 
    //std::cout << "AABB" << std::endl; 
    if( boxIntersect( ray ) == false )
        return false;

    if( !innerObjectList.empty() && innerObjectList[0]->intersect( ray, intersection ) )
    {
        intersection.obj = innerObjectList[0];
        return true;
    }
    else
        return false;

}

bool AABB::boxIntersect( Ray ray )
{
    for( int axis = X_AXIS; axis <= Z_AXIS; axis++ )
    {
        if( fabs( ray.getDirection( axis ) ) <= EPSILON )
            if( ray.getOrigin( axis ) < getMin( axis ) || ray.getOrigin( axis ) > getMax( axis ) )
                return false;
    }

    float tNear = OBJECT_MIN;
    float tFar = OBJECT_MAX;
    for( int axis = X_AXIS; axis <= Z_AXIS; axis++ )
    {
        float t1 = ( getMin(axis) - ray.getOrigin( axis ) ) / ray.getDirection( axis );
        float t2 = ( getMax(axis) - ray.getOrigin( axis ) ) / ray.getDirection( axis );
        if( t1 > t2 )
        {
            float temp = t1;
            t1 = t2;
            t2 = temp;
        }

        if( t1 > tNear )
            tNear = t1;
        if( t2 < tFar )
            tFar = t2;
    }

    if( tNear > tFar || tFar <= EPSILON )
        return false;
    else 
        return true;
}
/*bool AABB::intersect()
{ 
    std::cout << "AABB" << std::endl; 
    innerObjectList[0]->intersect(  );
    return true; 
}*/
//AABB::AABB ( Object inner ):
    //BoundingBox( inner  )
//{}

/*
void AABB::initialize()
{
    this->vertices.clear();
    glm::vec3 max, min;

    max.x = max.y = max.z = AABB_MIN;
    min.x = min.y = min.z = AABB_MAX;
    this->vertices.push_back( Vertex(max) );
    this->vertices.push_back( Vertex(min) );
}

void AABB::findMaxMin ()
{
    for( auto obj = innerObjectList.begin(); obj != innerObjectList.end(); obj++ )
    {
        for( auto itr = innerObject.vertices.begin(); itr != innerObject.vertices.end(); itr++ )
        {
            this->vertices[AABB_MAX_INDEX].position.x = fmax( this->vertices[AABB_MAX_INDEX].position.x, itr->position.x );
            this->vertices[AABB_MAX_INDEX].position.y = fmax( this->vertices[AABB_MAX_INDEX].position.y, itr->position.y );
            this->vertices[AABB_MAX_INDEX].position.z = fmax( this->vertices[AABB_MAX_INDEX].position.z, itr->position.z );
            this->vertices[AABB_MIN_INDEX].position.x = fmin( this->vertices[AABB_MIN_INDEX].position.x, itr->position.x );
            this->vertices[AABB_MIN_INDEX].position.y = fmin( this->vertices[AABB_MIN_INDEX].position.y, itr->position.y );
            this->vertices[AABB_MIN_INDEX].position.z = fmin( this->vertices[AABB_MIN_INDEX].position.z, itr->position.z );

        }
    }
}
*/
