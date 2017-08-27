//
//  Header.h
//  openGLTest
//
//  Created by xt on 17/4/29.
//  Copyright © 2017年 xt. All rights reserved.
//

#ifndef X_MODEL_H
#define X_MODEL_H

#include <vector>
#include <Gl/glew.h>

#include <glm/glm.hpp>

typedef glm::vec3 Vec3f;
typedef glm::vec4 Vec4f;
typedef glm::mat4 Matrix;

class XModel
{
    enum PrimType {
        eptNone = 0x0,
        eptPoints = 0x1,
        eptEdges = 0x2,
        eptTriangles = 0x4,
        eptTrianglesWithAdjacency = 0x8,
        eptAll = 0xf
    };

    static const int NumPrimTypes = 4;

    static XModel* CreateModel();

    XModel();
    virtual ~XModel();


    bool loadModelFromFile( const char* file);
    void computeBoundingBox( Vec3f &minVal, Vec3f &maxVal);

    bool hasNormals() const;
    bool hasTexCoords() const;
    bool hasTangents() const;
    bool hasColors() const;

    int getPositionSize() const;
    int getNormalSize() const;
    int getTexCoordSize() const;
    int getTangentSize() const;
    int getColorSize() const;

protected:
    std::vector<float> _positions;
    std::vector<float> _normals;
    std::vector<float> _texCoords;
    std::vector<float> _sTangents;
    std::vector<float> _colors;
    int _posSize;
    int _tcSize;
    int _cSize;

    std::vector<GLuint> _pIndex;
    std::vector<GLuint> _nIndex;
    std::vector<GLuint> _tIndex;
    std::vector<GLuint> _tanIndex;
    std::vector<GLuint> _cIndex;

        //data structures optimized for rendering, compiled model
    std::vector<GLuint> _indices[NumPrimTypes];
    std::vector<float> _vertices;

   static bool loadObjFromFile( const char *file, XModel &m);
};

#endif /* Header_h */
