#include <iostream>

#include "BoundingBox.h"

BoundingBox::BoundingBox( std::shared_ptr<Object> inner )
{
    innerObjectList.push_back( inner );
    findMaxMin();
}

BoundingBox::BoundingBox( std::vector< std::shared_ptr<Object> > objectList ):
    innerObjectList( objectList ) 
{
    findMaxMin();
}

/*bool BoundingBox::intersect( Ray ray, Intersection& intersection )
{
    std::cout << "BoundingBox" << std::endl;
    return true;
}
*/
/*bool BoundingBox::intersect()
{
    std::cout << "BoundingBox" << std::endl;
    return true;
}*/

void BoundingBox::findMaxMin()
{
    for( auto obj = innerObjectList.begin(); obj != innerObjectList.end(); obj++ )
    {
        max.x = fmax( max.x, (*obj)->getMax().x );
        max.y = fmax( max.y, (*obj)->getMax().y );
        max.z = fmax( max.z, (*obj)->getMax().z );

        min.x = fmin( min.x, (*obj)->getMin().x );
        min.y = fmin( min.y, (*obj)->getMin().y );
        min.z = fmin( min.z, (*obj)->getMin().z );
    }
}
