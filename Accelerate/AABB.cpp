#include <algorithm>

#include "AABB.h"


bool AABB::intersect() 
{ 
    std::cout << "AABB" << std::endl; 
    innerObjectList[0]->intersect();
    return true; 
}
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
