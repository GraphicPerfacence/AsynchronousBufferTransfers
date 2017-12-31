    //
    //  Subdivision.cpp
    //  openGLTest
    //
    //  Created by xt on 17/12/9.
    //  Copyright © 2017年 xt. All rights reserved.
    //

#include "util/Subdivision.hpp"
#include "math/helpF.h"
#include "math/const.h"

#include <math.h>
using namespace Util;

short Subdivision::numberOfSlicePartitions = 32;
short Subdivision::numberOfStackPartitions = 24;

struct TriangleIndicesUnsignedInt
{

    TriangleIndicesUnsignedInt(unsigned int i0,unsigned int i1,
                               unsigned int i2):indic0(i0),indic1(i1),indic2(i2){}

    unsigned int indic0;
    unsigned int indic1;
    unsigned int indic2;
};

static void Subdivide(Ellipsoid<float> *ellipsoid, std::vector<V3f>&positoin,std::vector<unsigned int>&indices,std::vector<V3f>*normalsPtr,
                      std::vector<V2f>*texCoordPtr,
                      TriangleIndicesUnsignedInt triangleIndices, short level)
{
    if(level > 0)
        {
        V3f p0 =  math::normalize((positoin[triangleIndices.indic0] + positoin[triangleIndices.indic1]) * 0.5f) ;
        V3f p1 =  math::normalize((positoin[triangleIndices.indic1] + positoin[triangleIndices.indic2]) * 0.5f) ;
        V3f p2 =  math::normalize((positoin[triangleIndices.indic2] + positoin[triangleIndices.indic0]) * 0.5f) ;
        if(ellipsoid != NULL)
            {
            p0 = ellipsoid->radius() * p0;
            p1 = ellipsoid->radius() * p1;
            p2 = ellipsoid->radius() * p2;
            }

        positoin.push_back(p0);
        positoin.push_back(p1);
        positoin.push_back(p2);

        if((normalsPtr != NULL || texCoordPtr != NULL) && (ellipsoid != NULL))
            {
            p0 = math::normalize(ellipsoid->geodeticSurfaceNormal(p0));
            p1 = math::normalize(ellipsoid->geodeticSurfaceNormal(p1));
            p2 = math::normalize(ellipsoid->geodeticSurfaceNormal(p2));
            }

        if(normalsPtr != NULL)
            {
            std::vector<V3f>&normals = *normalsPtr;
            normals.push_back(p0);
            normals.push_back(p1);
            normals.push_back(p2);

            }

        if(texCoordPtr != NULL)
            {
            std::vector<V2f>&texCoords = *texCoordPtr;
            texCoords.push_back(Subdivision::computeTextureCoordinate(p0));
            texCoords.push_back(Subdivision::computeTextureCoordinate(p1));
            texCoords.push_back(Subdivision::computeTextureCoordinate(p2));

            }
        unsigned int i01 = positoin.size() - 3;
        unsigned int i12 = positoin.size() - 2;
        unsigned int i20 = positoin.size() - 1;

        --level;
        Subdivide(ellipsoid,positoin,indices,normalsPtr,texCoordPtr,TriangleIndicesUnsignedInt(triangleIndices.indic0, i01, i20),level);
        Subdivide(ellipsoid,positoin,indices,normalsPtr,texCoordPtr,TriangleIndicesUnsignedInt(i01, triangleIndices.indic1, i12),level);
        Subdivide(ellipsoid,positoin,indices,normalsPtr,texCoordPtr,TriangleIndicesUnsignedInt(i01, i12, i20),level);
        Subdivide(ellipsoid,positoin,indices,normalsPtr,texCoordPtr,TriangleIndicesUnsignedInt(i20, i12, triangleIndices.indic2),level);

        }
    else
        {
        indices.push_back(triangleIndices.indic0);
        indices.push_back(triangleIndices.indic1);
        indices.push_back(triangleIndices.indic2);
        }
}

void Subdivision::subdivisionSphere(TYPE type,std::vector<V3f>*positoinPtr,
                                    std::vector<unsigned int>&indices,
                                    std::vector<V3f>*normalsPtr,
                                    std::vector<V2f>*texCoordPtr,short level)
{

    if(TETRAHEDRON == type)
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

        V3f p0 = V3f(0.0,0.0,1.0);
        V3f p1 = V3f(0.0, (2.0 * sqrt(2.0)) / 3.0, negativeOneThird);
        V3f p2 = V3f(-rootSixOverThree, negativeRootTwoOverThree, negativeOneThird);
        V3f p3 = V3f(rootSixOverThree, negativeRootTwoOverThree, negativeOneThird);


        std::vector<V3f>&positions = *positoinPtr;
        positions.push_back(p0);
        positions.push_back(p1);
        positions.push_back(p2);
        positions.push_back(p3);

        if(normalsPtr != NULL)
            {
            std::vector<V3f>&normals = *normalsPtr;
            normals.push_back(p0);
            normals.push_back(p1);
            normals.push_back(p2);
            normals.push_back(p3);
            }

        if(texCoordPtr != NULL)
            {
            std::vector<V2f>&texCoords = *texCoordPtr;
            texCoords.push_back(computeTextureCoordinate(p0));
            texCoords.push_back(computeTextureCoordinate(p1));
            texCoords.push_back(computeTextureCoordinate(p2));
            texCoords.push_back(computeTextureCoordinate(p3));
            }

        Subdivide(NULL,positions, indices, normalsPtr,texCoordPtr, TriangleIndicesUnsignedInt(0, 1, 2), level);
        Subdivide(NULL,positions, indices, normalsPtr,texCoordPtr, TriangleIndicesUnsignedInt(0, 2, 3), level);
        Subdivide(NULL,positions, indices, normalsPtr,texCoordPtr,TriangleIndicesUnsignedInt(0, 3, 1), level);
        Subdivide(NULL,positions, indices, normalsPtr,texCoordPtr, TriangleIndicesUnsignedInt(1, 3, 2), level);

        }

    else if(CUBMAP == type)
        {

        }
}

void Subdivision::subdivisionElliposid(Ellipsoid<float>* ellipsoid,TYPE type,std::vector<V3f>*positoinPtr,
                                       std::vector<unsigned int>&indices,
                                       std::vector<V3f>*normalsPtr,
                                       std::vector<V2f>*texCoordPtr,short level)
{
    if(TETRAHEDRON == type)
        {

        double negativeRootTwoOverThree = -sqrt(2.0) / 3.0;
        const double negativeOneThird = -1.0 / 3.0;
        double rootSixOverThree = sqrt(6.0) / 3.0;

        V3f p0 = V3f(0.0,0.0,1.0);
        V3f p1 = V3f(0.0, (2.0 * sqrt(2.0)) / 3.0, negativeOneThird);
        V3f p2 = V3f(-rootSixOverThree, negativeRootTwoOverThree, negativeOneThird);
        V3f p3 = V3f(rootSixOverThree, negativeRootTwoOverThree, negativeOneThird);

        p0 = ellipsoid->radius() * p0;
        p1 = ellipsoid->radius() * p1;
        p2 = ellipsoid->radius() * p2;
        p3 = ellipsoid->radius() * p3;

        std::vector<V3f>&positions = *positoinPtr;
        positions.push_back(p0);
        positions.push_back(p1);
        positions.push_back(p2);
        positions.push_back(p3);

        if(normalsPtr != NULL || texCoordPtr != NULL)
            {

            V3f d0 = ellipsoid->geodeticSurfaceNormal(p0);
            V3f d1 = ellipsoid->geodeticSurfaceNormal(p1);
            V3f d2 = ellipsoid->geodeticSurfaceNormal(p2);
            V3f d3 = ellipsoid->geodeticSurfaceNormal(p3);

            if(normalsPtr != NULL)
                {
                std::vector<V3f>&normals = *normalsPtr;
                normals.push_back(d0);
                normals.push_back(d1);
                normals.push_back(d2);
                normals.push_back(d3);
                }
            if(texCoordPtr != NULL)
                {
                std::vector<V2f>&texCoords = *texCoordPtr;
                texCoords.push_back(computeTextureCoordinate(d0));
                texCoords.push_back(computeTextureCoordinate(d1));
                texCoords.push_back(computeTextureCoordinate(d2));
                texCoords.push_back(computeTextureCoordinate(d3));
                }
            }

        Subdivide(ellipsoid,positions, indices, normalsPtr,texCoordPtr, TriangleIndicesUnsignedInt(0, 1, 2), level);
        Subdivide(ellipsoid,positions, indices, normalsPtr,texCoordPtr, TriangleIndicesUnsignedInt(0, 2, 3), level);
        Subdivide(ellipsoid,positions, indices, normalsPtr,texCoordPtr,TriangleIndicesUnsignedInt(0, 3, 1), level);
        Subdivide(ellipsoid,positions, indices, normalsPtr,texCoordPtr, TriangleIndicesUnsignedInt(1, 3, 2), level);

        }
    else if(CUBMAP == type)
        {

        }
    else if(GEOGRAPHICGRID ==  type)
        {

            //unsigned int  vertexNum = 2 + (numberOfStackPartitions - 1) * numberOfSlicePartitions;

            // Create lookup table
            //
        float* cosTheta  = new float[numberOfSlicePartitions];
        float* sinTheta  = new float[numberOfSlicePartitions];

        for (int j = 0; j < numberOfSlicePartitions; ++j)
            {
            float theta = 2.0 *  math::Const<float>::pi()  * (((float)j) / numberOfSlicePartitions);
            cosTheta[j] = cos(theta);
            sinTheta[j] = sin(theta);
            }

        std::vector<V3f>& positions = *positoinPtr;

        positions.push_back(V3f(0.0,0.0,ellipsoid->radius().z));
        for (int i = 1; i < numberOfStackPartitions; ++i)
            {

            float phi = math::Const<float>::pi() * (((float)i) / numberOfStackPartitions);
            float sinPhi = sin(phi);

            float xSinPhi = ellipsoid->radius().x * sinPhi;
            float ySinPhi = ellipsoid->radius().y * sinPhi;
            float zCosPhi = ellipsoid->radius().z * cos(phi);

            for (int j = 0; j < numberOfSlicePartitions; ++j)
                {
                positions.push_back(V3f(cosTheta[j] * xSinPhi, sinTheta[j] * ySinPhi, zCosPhi));
                }
            }
        positions.push_back(V3f(0, 0, -ellipsoid->radius().z));

        delete [] cosTheta;
        delete [] sinTheta;

        if(normalsPtr != NULL || texCoordPtr != NULL)
            {
            for(unsigned int i = 0;i < positions.size();i++)
                {
                V3f deticSurfaceNormal = ellipsoid->geodeticSurfaceNormal(positions[i]);
                if(normalsPtr != NULL)
                    {
                    normalsPtr->push_back(deticSurfaceNormal);
                    }
                if(texCoordPtr != NULL)
                    {
                    texCoordPtr->push_back(computeTextureCoordinate(deticSurfaceNormal));
                    }
                }
            }

            //top triangles
        int lastPosition = 0;
        for (int j = 1; j < numberOfSlicePartitions; j++)
            {
            indices.push_back(lastPosition); indices.push_back(j); indices.push_back(j + 1);
            }
        indices.push_back(lastPosition); indices.push_back(numberOfSlicePartitions); indices.push_back(1);

            //middle triangles
        for (unsigned int i = 0; i <  numberOfStackPartitions - 2; ++i)
            {
            int topRowOffset = (i * numberOfSlicePartitions) + 1;
            int bottomRowOffset = ((i + 1) * numberOfSlicePartitions) + 1;


            for (int j = 0; j < numberOfSlicePartitions - 1; ++j)
                {
                indices.push_back(bottomRowOffset + j);
                indices.push_back(bottomRowOffset + j + 1);
                indices.push_back(topRowOffset + j + 1);

                indices.push_back(bottomRowOffset + j);
                indices.push_back(topRowOffset + j + 1);
                indices.push_back(topRowOffset + j);
                }

            int  topRowOffsetN    = topRowOffset + numberOfSlicePartitions - 1;
            int  bottomRowOffsetN = bottomRowOffset +  numberOfSlicePartitions - 1;

            indices.push_back(bottomRowOffsetN);
            indices.push_back(bottomRowOffset);
            indices.push_back(topRowOffset);

            indices.push_back(bottomRowOffsetN);
            indices.push_back(topRowOffset);
            indices.push_back(topRowOffsetN);

            }

            //buttom triangles
        lastPosition = positions.size() - 1;
        for (int j = lastPosition - 1; j > lastPosition - numberOfSlicePartitions; j--)
            {
            indices.push_back(lastPosition); indices.push_back(j); indices.push_back(j - 1);
            }

        indices.push_back(lastPosition); indices.push_back(lastPosition - numberOfSlicePartitions);
        indices.push_back(lastPosition -  1);
        
        }
    
}

V2f Subdivision::computeTextureCoordinate(const V3f&position)
{
    V2f texCoord;
    texCoord.x = (atan2(position.y, position.x) / math::Const<float>::pi()) + 0.5;
    texCoord.y = asin(position.z) / math::Const<float>::pi() + 0.5;
    
    return  texCoord;
}