#ifndef _KD_TREE_H_
#define _KD_TREE_H_

#include <memory>

#define xAxis 0
#define yAxis 1
#define zAxis 2

class KdNode
{
public:
    std::shared_ptr<KdNode> parent;
    std::shared_ptr<KdNode> left, right;
    int axis;
};

class KdTree
{

};

#endif
