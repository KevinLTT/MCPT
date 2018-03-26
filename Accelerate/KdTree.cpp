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
    if( innerObjectList.size() == 18 )
        int a = 10;

    axis = splitAxis;

    if( this->innerObjectList.size() <= LEAF_OBJ_NUM )
    {
        isLeaf = true;
        return;
    }
    else
        isLeaf = false;

    std::vector< std::shared_ptr<Object> > leftList, rightList;
    partitionInnerObjectList( leftList, rightList );

    //std::vector<std::shared_ptr<Object>>().swap( innerObjectList ); //todo
    left = std::make_shared<KdTree>( leftList );
    right = std::make_shared<KdTree>( rightList );
}

void KdTree::partitionInnerObjectList( std::vector< std::shared_ptr<Object> >& leftList, std::vector< std::shared_ptr<Object> >& rightList )
{
    int minDifference = innerObjectList.size() + 1;
    //unsigned int minTotalObjNumber = innerObjectList.size() * 2 + 1;

    for( int splitAxis = X_AXIS; splitAxis <= Z_AXIS; splitAxis++ )
    {
        std::vector< std::shared_ptr<Object> > left, right;
        //sortObjList( splitAxis, innerObjectList );
        float pivot = findPivot( splitAxis );
        for( auto obj = innerObjectList.begin(); obj != innerObjectList.end(); obj++ )
        {
            float center = ( (*obj)->getMax( splitAxis ) + (*obj)->getMin( splitAxis ) ) / 2;
            //float objMin = (*obj)->getMin( splitAxis );
            //float objMax = (*obj)->getMax( splitAxis );
            if( center <= pivot + EPSILON )
                left.push_back( *obj );
            else //if( objMin > pivot - EPSILON )
                right.push_back( *obj );
            /*else
            {
                left.push_back( *obj );
                right.push_back( *obj );
            }*/
        }

        //unsigned int totalObjNumber = left.size() + right.size();
        int difference = ( left.size() > right.size() ) ? left.size() - right.size() : right.size() - left.size() ;
        //if( totalObjNumber < minTotalObjNumber || ( totalObjNumber == minTotalObjNumber && difference < minDifference ) )
        if( difference < minDifference )
        {
            leftList = left;
            rightList = right;
            minDifference = difference;
            //minTotalObjNumber = totalObjNumber;
            this->axis = splitAxis;
        }
    }

    //in case that one of the tweo lists are empty, put the object nearest to the pivot to right list
    if( leftList.size() >= 2 && rightList.size() == 0 )
    {
        //sortObjList( this->axis, leftList );
        int maxIndex = findMax( this->axis, leftList );
        rightList.push_back( leftList[maxIndex] );
        leftList.erase( leftList.begin()+maxIndex );
    }


    if( rightList.size() >= 2 && leftList.size() == 0 )
    {
        //sortObjList( this->axis, rightList );
        int minIndex = findMin( this->axis, rightList );
        leftList.push_back( rightList[minIndex] );
        rightList.erase( rightList.begin()+minIndex );
    }
}

float KdTree::findPivot( int splitAxis )
{
    float sum = 0;
    for( auto itr = innerObjectList.begin(); itr != innerObjectList.end(); itr++ )
    {
        sum += (*itr)->getMax( splitAxis ) + (*itr)->getMin( splitAxis );
    }

    return sum / ( 2 * innerObjectList.size() );
}

int KdTree::findMax( int splitAxis, std::vector< std::shared_ptr<Object> > list )
{
    if( list.empty() )
        return -1;

    int maxIndex = 0;
    auto maxValue = list[0]->getMax( splitAxis );

    for( unsigned int i = 1; i < list.size(); i++ )
    {
        if( list[i]->getMax(splitAxis) > maxValue )
        {
            maxIndex = i;
            maxValue = list[i]->getMax( splitAxis );
        }
    }

    return maxIndex;
}

int KdTree::findMin( int splitAxis, std::vector< std::shared_ptr<Object> > list )
{
    if( list.empty() )
        return -1;

    int minIndex = 0;
    auto minValue = list[0]->getMin( splitAxis );

    for( unsigned int i = 1; i < list.size(); i++ )
    {
        if( list[i]->getMin(splitAxis) < minValue )
        {
            minIndex = i;
            minValue = list[i]->getMin( splitAxis );
        }
    }

    return minIndex;
}


bool KdTree::intersect( Ray ray, Intersection& intersection )  
{ 
    std::cout << "KdTree" << std::endl; 
    if( !innerObjectList.empty() )
        innerObjectList[0]->intersect( ray, intersection );
    return true; 
}

/*bool KdTree::intersect( )
{ 
    std::cout << "KdTree" << std::endl; 
    if( !innerObjectList.empty() )
        innerObjectList[0]->intersect();
    return true; 
}*/

void KdTree::sortObjList( int axis, std::vector< std::shared_ptr<Object> >& list )
{
    switch( axis )
    {
    case X_AXIS:
        std::sort( list.begin(), list.end(), cmpObjX );
        break;
    case Y_AXIS:
        std::sort( list.begin(), list.end(), cmpObjY );
        break;
    case Z_AXIS:
    default:
        std::sort( list.begin(), list.end(), cmpObjZ );
        break;
    }
}

bool KdTree::cmpObjX( const std::shared_ptr<Object>& obj1, const std::shared_ptr<Object>& obj2 )
{
    return obj1->getMax(X_AXIS) <= obj2->getMax(X_AXIS);
}

bool KdTree::cmpObjY( const std::shared_ptr<Object>& obj1, const std::shared_ptr<Object>& obj2 )
{
    return obj1->getMax(Y_AXIS) <= obj2->getMax(Y_AXIS);
}

bool KdTree::cmpObjZ( const std::shared_ptr<Object>& obj1, const std::shared_ptr<Object>& obj2 )
{
    return obj1->getMax(Z_AXIS) <= obj2->getMax(Z_AXIS);
}
