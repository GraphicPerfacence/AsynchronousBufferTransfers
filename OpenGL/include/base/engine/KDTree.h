//
//  KDTree.h
//  openGLTest
//
//  Created by xt on 17/8/30.
//  Copyright © 2017年 xt. All rights reserved.
//

#ifndef OPENGL_KDTree_H
#define OPENGL_KDTree_H

#include "../Persisten.h"

template <class LEAFDATA,class NODEDATA> struct KDTreeLeafNode;
template <class LEAFDATA,class NODEDATA> class KDTreeNodeBetween;

template <class LEAFDATA,class NODEDATA>
struct KDTreeNode: public Persisten
{
    typedef KDTreeNode <LEAFDATA,NODEDATA> Node;

protected:
    Node*           parent;

public:
    typedef KDTreeLeafNode<LEAFDATA, NODEDATA> Leaf;
    typedef KDTreeNodeBetween<LEAFDATA, NODEDATA> Between;

};
#endif /* KDTree_h */
