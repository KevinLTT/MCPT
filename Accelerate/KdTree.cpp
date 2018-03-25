#include <algorithm>
#include <math.h>

#include "KdTree.h"

#define MAX_COST 99999999

//KdTree::KdTree( Object inner ): BoundingBox( inner ) { build( Z_AXIS ); }
KdTree::KdTree( std::shared_ptr<Object> inner ): BoundingBox( inner ) { build( Z_AXIS ); }
//KdTree::KdTree( std::vector<Object> innerList ): BoundingBox( innerList ) { build( Z_AXIS ); }
KdTree::KdTree( std::vector< std::shared_ptr<Object> > innerList ): BoundingBox( innerList ) { build( Z_AXIS ); }

void KdTree::build( int splitAxis )
{
    axis = splitAxis;

    if( this->innerObjectList.size() <= 1 )
        return;

    std::vector< std::shared_ptr<Object> > leftList, rightList;
    partitionInnerObjectList( leftList, rightList );

    left = std::make_shared<KdTree>( leftList );
    right = std::make_shared<KdTree>( rightList );
}

void KdTree::partitionInnerObjectList( std::vector< std::shared_ptr<Object> >& leftList, std::vector< std::shared_ptr<Object> >& rightList )
{
    int minDifference = innerObjectList.size();

    for( int splitAxis = X_AXIS; splitAxis <= Z_AXIS; splitAxis++ )
    {
        std::vector< std::shared_ptr<Object> > left, right;
        float pivot = ( getMax( splitAxis ) + getMin( splitAxis ) ) / 2;

        for( auto obj = innerObjectList.begin(); obj != innerObjectList.end(); obj++ )
        {
            float center = ( (*obj)->getMax( splitAxis ) + (*obj)->getMin( splitAxis ) ) / 2;
            if( center < pivot )
                left.push_back( *obj );
            else
                right.push_back( *obj );
        }

        int difference = ( left.size() > right.size() ) ? left.size() - right.size() : right.size() - left.size() ;
        if( difference <= minDifference )
        {
            leftList = left;
            rightList = right;
            minDifference = difference;
            this->axis = splitAxis;
        }
    }

    //in case that one of the tweo lists are empty, put the object nearest to the pivot to right list
    if( leftList.size() >= 2 && rightList.size() == 0 )
    {
        sortObjList( this->axis, leftList );
        rightList.push_back( leftList[0] );
        leftList.erase( leftList.begin() );
    }


    if( rightList.size() >= 2 && leftList.size() == 0 )
    {
        sortObjList( this->axis, rightList );
        leftList.push_back( rightList[0] );
        rightList.erase( rightList.begin() );
    }
}

bool KdTree::intersect() 
{ 
    std::cout << "KdTree" << std::endl; 
    innerObjectList[0]->intersect();
    return true; 
}

void KdTree::sortObjList( int axis, std::vector< std::shared_ptr<Object> >& list )
{
    switch( axis )
    {
    case X_AXIS:
        std::sort( list.begin(), list.end(), cmpObjX );
    case Y_AXIS:
        std::sort( list.begin(), list.end(), cmpObjY );
    case Z_AXIS:
        std::sort( list.begin(), list.end(), cmpObjZ );
    }
}

bool KdTree::cmpObjX( const std::shared_ptr<Object>& obj1, const std::shared_ptr<Object>& obj2 )
{
    return obj1->getMax().x <= obj2->getMax().x;
}

bool KdTree::cmpObjY( const std::shared_ptr<Object>& obj1, const std::shared_ptr<Object>& obj2 )
{
    return obj1->getMax().y <= obj2->getMax().y;
}

bool KdTree::cmpObjZ( const std::shared_ptr<Object>& obj1, const std::shared_ptr<Object>& obj2 )
{
    return obj1->getMax().z <= obj2->getMax().z;
}
