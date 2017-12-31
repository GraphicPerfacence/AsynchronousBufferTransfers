    //
    //  ElliposidGeometry.cpp
    //  openGLTest
    //
    //  Created by xt on 17/12/30.
    //  Copyright © 2017年 xt. All rights reserved.
    //

#include "ElliposidGeometry.h"
#include "Subdivision.hpp"

#include <gl/glew.h>

#include <vector>

using namespace Util;

ElliposidGeometry::ElliposidGeometry()
{

}



void ElliposidGeometry::create()
{
    std::vector<V3f> positions;
    std::vector<unsigned int > indices;
    std::vector<V3f> normals;
    std::vector<V2f> texCoords;
    Ellipsoid<float> ellipsoid(1.0,1.1,1.0);

    Util::Subdivision::TYPE type = (Util::Subdivision::TYPE)(_subType);
    Util::Subdivision::subdivisionElliposid(&ellipsoid,type, &positions,indices,&normals,&texCoords,5);

    _indicesNum = indices.size();

    if((positions.size() < 0) || (indices.size() < 0)) return;

    if(Util::Subdivision::TETRAHEDRON)
        {

        glGenVertexArrays(1,&_vertex_buffer); //vao
        glBindVertexArray(_vertex_buffer);

        GLuint VBO[3];
        glGenBuffers(3,VBO);

        glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
        glBufferData(GL_ARRAY_BUFFER, sizeof(V3f) * positions.size(), &positions[0], GL_STATIC_DRAW);


        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, VBO[2]);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);

        glEnableVertexAttribArray(0);
        glVertexAttribPointer(
                              0,                  // attribute. No particular reason for 0, but must match the layout in the shader.
                              3,                  // size
                              GL_FLOAT,           // type
                              GL_FALSE,           // normalized?
                              0,                  // stride
                              (void*)0            // array buffer offset
                              );

        glBindBuffer(GL_ARRAY_BUFFER,VBO[1]);
        glBufferData(GL_ARRAY_BUFFER,sizeof(V2f) * texCoords.size(),&texCoords[0],GL_STATIC_DRAW);


        glEnableVertexAttribArray(1);
        glVertexAttribPointer(
                              1,                  // attribute. No particular reason for 0, but must match the layout in the shader.
                              2,                  // size
                              GL_FLOAT,           // type
                              GL_FALSE,           // normalized?
                              0,                  // stride
                              (void*)0            // array buffer offset
                              );
        glBindVertexArray(0);

        }
    else if ( Util::Subdivision::GEOGRAPHICGRID == type)
        {
        short slip = Util::Subdivision::numberOfSlicePartitions;
        short stack = Util::Subdivision::numberOfStackPartitions;


        glGenVertexArrays(1,&_vertex_buffer); //vao
        glBindVertexArray(_vertex_buffer);

        GLuint VBO[3];
        glGenBuffers(3,VBO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
        glBufferData(GL_ARRAY_BUFFER, sizeof(V3f) * positions.size(), &positions[0], GL_STATIC_DRAW); //position

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, VBO[2]); //top fan
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);

        glEnableVertexAttribArray(0);
        glVertexAttribPointer(
                              0,                  // attribute. No particular reason for 0, but must match the layout in the shader.
                              3,                  // size
                              GL_FLOAT,           // type
                              GL_FALSE,           // normalized?
                              0,                  // stride
                              (void*)0            // array buffer offset
                              );

        glBindBuffer(GL_ARRAY_BUFFER,VBO[1]); //texCoord
        glBufferData(GL_ARRAY_BUFFER,sizeof(V2f) * texCoords.size(),&texCoords[0],GL_STATIC_DRAW);


        glEnableVertexAttribArray(1);
        glVertexAttribPointer(
                              1,                  // attribute. No particular reason for 0, but must match the layout in the shader.
                              2,                  // size
                              GL_FLOAT,           // type
                              GL_FALSE,           // normalized?
                              0,                  // stride
                              (void*)0            // array buffer offset
                              );
        glBindVertexArray(0);


        }
}

void ElliposidGeometry::DrawElliposid()
{
    glBindVertexArray(_vertex_buffer);
    if(_subType == Util::Subdivision::TETRAHEDRON)
        {

        }
    else if(_subType == Util::Subdivision::GEOGRAPHICGRID)
        {
        glActiveTexture(GL_TEXTURE0);
            // glBindTexture(GL_TEXTURE_2D, _texturesObj[0]->GetTexture());
            //glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

        glDrawElements(GL_TRIANGLES, _indicesNum , GL_UNSIGNED_INT, (void*)0);

        }
    
    glBindVertexArray(0);
}