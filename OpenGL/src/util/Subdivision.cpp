    //
    //  Subdivision.cpp
    //  openGLTest
    //
    //  Created by xt on 17/12/9.
    //  Copyright © 2017年 xt. All rights reserved.
    //

#include "util/Subdivision.hpp"
#include "math/helpF.h"
#include <math.h>
using namespace Util;


struct TriangleIndicesUnsignedInt
{

    TriangleIndicesUnsignedInt(unsigned int i0,unsigned int i1,
                               unsigned int i2):indic0(i0),indic1(i1),indic2(i2){}

    unsigned int indic0;
    unsigned int indic1;
    unsigned int indic2;
};

static void Subdivide(std::vector<V3f>&positoin,std::vector<unsigned int>&indices,
                      TriangleIndicesUnsignedInt triangleIndices,short level)
{
    if(level > 0)
        {
        positoin.push_back( math::normal((positoin[triangleIndices.indic0] + positoin[triangleIndices.indic1]) * 0.5f) );
        positoin.push_back( math::normal((positoin[triangleIndices.indic1] + positoin[triangleIndices.indic2]) * 0.5f) );
        positoin.push_back( math::normal((positoin[triangleIndices.indic2] + positoin[triangleIndices.indic0]) * 0.5f) );

        unsigned int i01 = positoin.size() - 3;
        unsigned int i12 = positoin.size() - 2;
        unsigned int i20 = positoin.size() - 1;

        --level;
        Subdivide(positoin,indices,TriangleIndicesUnsignedInt(triangleIndices.indic0, i01, i20),level);
        Subdivide(positoin,indices,TriangleIndicesUnsignedInt(i01, triangleIndices.indic1, i12),level);
        Subdivide(positoin,indices,TriangleIndicesUnsignedInt(i01, i12, i20),level);
        Subdivide(positoin,indices,TriangleIndicesUnsignedInt(i20, i12, triangleIndices.indic2),level);

        }
    else
        {
        indices.push_back(triangleIndices.indic0);
        indices.push_back(triangleIndices.indic1);
        indices.push_back(triangleIndices.indic2);
        }
}

void Subdivision::subdivisionSphere(std::vector<V3f>&positions,std::vector<unsigned int> &indices,
                                    std::vector<V3f>&normals,short level)
{

    unsigned int triangleNum = 0;

    for(short i = 0;i < level;i++)
        {
        triangleNum += pow(4,i);
        }

    triangleNum *= 4;

    //(triangleNum * 3,0);

    double negativeRootTwoOverThree = -sqrt(2.0) / 3.0;
    const double negativeOneThird = -1.0 / 3.0;
    double rootSixOverThree = sqrt(6.0) / 3.0;


    positions.push_back(V3f(0.0,0.0,1.0));
    positions.push_back(V3f(0, (2.0 * sqrt(2.0)) / 3.0, negativeOneThird));
    positions.push_back(V3f(-rootSixOverThree, negativeRootTwoOverThree, negativeOneThird));
    positions.push_back(V3f(rootSixOverThree, negativeRootTwoOverThree, negativeOneThird));


    Subdivide(positions, indices,  TriangleIndicesUnsignedInt(0, 1, 2), level);
    Subdivide(positions, indices,  TriangleIndicesUnsignedInt(0, 2, 3), level);
    Subdivide(positions, indices,  TriangleIndicesUnsignedInt(0, 3, 1), level);
    Subdivide(positions, indices,  TriangleIndicesUnsignedInt(1, 3, 2), level);
}

