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
    //std::cout << "KdTree" << std::endl; 
    if( !boxIntersect( ray ) )
        return false;

    if( isLeaf == true)
    {
        if( !innerObjectList.empty() )
            return innerObjectList[0]->intersect( ray, intersection );
        else
            return false;
    }

    if( fabs( ray.getDirection( this->axis )  ) <= EPSILON )
    {
        Intersection leftInter, rightInter;
        bool leftFind = left->intersect( ray, intersection );
        leftInter = intersection;
        bool rightFind = right->intersect( ray, intersection );
        rightInter = intersection;

        if( leftFind && rightFind )
        {
            intersection = ( leftInter.t < rightInter.t ) ? leftInter : rightInter;
            return true;
        }
        else
            return leftFind | rightFind;
    }

    if( ray.getDirection( this->axis ) >= 0 )
    {
        bool find = left->intersect( ray, intersection );    
        if( find == true )
        {
            auto leftIntersection = intersection;
            glm::vec3 interObjMax = leftIntersection.obj->getMax();
            glm::vec3 interObjMin = leftIntersection.obj->getMin();

            if( interObjMax.x > getMax( X_AXIS ) || interObjMax.y > getMax( Y_AXIS ) || interObjMax.z > getMax( Z_AXIS ) ||
                interObjMin.x < getMin( X_AXIS ) || interObjMin.y < getMin( Y_AXIS ) || interObjMin.z < getMin( Z_AXIS ) )
            {
                if( right->intersect( ray, intersection ) == true )
                {
                    auto rightInterObj = intersection;
                    intersection = ( leftIntersection.t < rightInterObj.t ) ? leftIntersection : rightInterObj;
                }
                else
                    intersection = leftIntersection;
            }
                
            return true;
        }
        else
            return right->intersect( ray, intersection );
    }
    else 
    {
        bool find = right->intersect( ray, intersection );
        if( find == true )
        {
            auto rightIntersection = intersection;
            glm::vec3 interObjMax = rightIntersection.obj->getMax();
            glm::vec3 interObjMin = rightIntersection.obj->getMin();

            if( interObjMax.x > getMax( X_AXIS ) || interObjMax.y > getMax( Y_AXIS ) || interObjMax.z > getMax( Z_AXIS ) ||
                interObjMin.x < getMin( X_AXIS ) || interObjMin.y < getMin( Y_AXIS ) || interObjMin.z < getMin( Z_AXIS ) )
            {
                if( left->intersect( ray, intersection ) == true )
                {
                    auto leftInterObj = intersection;
                    intersection = ( rightIntersection.t < leftInterObj.t ) ? rightIntersection : leftInterObj;
                }
                else
                    intersection = rightIntersection;
            }
                
            return true;
        }
        else
            return left->intersect( ray, intersection );
    }
    
    return true; 
}

bool KdTree::boxIntersect( Ray ray )
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

std::shared_ptr<KdTree> KdTree::buildTree( Mesh mesh )
{
    std::shared_ptr<Material> m = std::make_shared<Material>( mesh.material );
    std::vector<std::shared_ptr<Object>> prims;
    std::vector<std::shared_ptr<Object>> boxes;
    for( unsigned int i = 0; i < mesh.indices.size()-2; i += 3 )
    {
        std::vector<Vertex> vs = { mesh.vertices[mesh.indices[i]], mesh.vertices[mesh.indices[i+1]], mesh.vertices[mesh.indices[i+2]] };
        std::shared_ptr<Object> prim = std::make_shared<Triangular>( vs, m );
        std::cout << "prim: " << std::endl;
        prim->showMaxMin();
        std::shared_ptr<Object> box = std::make_shared<AABB>( prim );
        std::cout << "box: " << std::endl;
        box->showMaxMin();

        prims.push_back( prim );
        boxes.push_back( box );
    }

    return std::make_shared<KdTree>( boxes );
}

std::shared_ptr<KdTree> KdTree::buildTree( std::vector<Mesh> meshes )
{
    std::vector<std::shared_ptr<Object>> trees;
    for( auto itr = meshes.begin(); itr != meshes.end(); itr++ )
    {
        std::shared_ptr<Object> tempTree = buildTree( *itr );
        std::cout << "temp tree: " << std::endl;
        tempTree->showMaxMin();
        trees.push_back( tempTree );
    }

    return std::make_shared<KdTree>( trees );
}
