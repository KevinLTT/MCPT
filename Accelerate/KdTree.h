#ifndef _KD_TREE_H_
#define _KD_TREE_H_

#include <memory>
#include <iostream>

#include "Object.h"
#include "BoundingBox.h"

#define LEAF_OBJ_NUM 1

enum Axis
{
    x, y, z
};

class KdTree : public BoundingBox
{
public:
    std::shared_ptr<KdTree> left, right; //, parent;
    int axis;
    bool isLeaf;

public:
    //KdTree( Object inner ); //: BoundingBox( inner ) { build( Z_AXIS ); }
    KdTree( std::shared_ptr<Object> inner ); //: BoundingBox( inner ) { build( Z_AXIS ); }
    //KdTree( std::vector<Object> innerList ); //: BoundingBox( innerList ) { build( Z_AXIS ); }
    KdTree( std::vector< std::shared_ptr<Object> > innerList ); //: BoundingBox( innerList ) { build( Z_AXIS ); }
    
    virtual bool intersect( Ray ray, Intersection& intersection );
    //virtual bool intersect();

    void build( int splitAxis );
    //int findGoodAxis();
    void partitionInnerObjectList( std::vector< std::shared_ptr<Object> >& leftList, std::vector< std::shared_ptr<Object> >& rightList );
    float findPivot( int splitAxis );
    int findMax( int splitAxis, std::vector<std::shared_ptr<Object>> list );
    int findMin( int splitAxis, std::vector<std::shared_ptr<Object>> list );
    
    void sortObjList( int axis, std::vector< std::shared_ptr<Object> >& list );
    static bool cmpObjX( const std::shared_ptr<Object>& obj1, const std::shared_ptr<Object>& obj2 );
    static bool cmpObjY( const std::shared_ptr<Object>& obj1, const std::shared_ptr<Object>& obj2 );
    static bool cmpObjZ( const std::shared_ptr<Object>& obj1, const std::shared_ptr<Object>& obj2 );
};


#endif
