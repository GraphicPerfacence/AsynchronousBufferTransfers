//
//  texture.cpp
//  OpenGL
//
//  Created by xt on 15/8/20.
//  Copyright (c) 2015年 xt. All rights reserved.
//

#include "../include/texture.h"
#include "../include/log.h"
#include "SOIL2/SOIL2.h"

#include <stdlib.h>
#include <stdio.h>


TextureObj::TextureObj(const char*imgFileName):
    _fileName(imgFileName),
    _minMapping(true),
    _targetType(GL_TEXTURE_2D)
{
    glGenTextures(1,&_texObject);
}

TextureObj::TextureObj(const GLenum vTargetType, const GLint vFormatExtern,
                                 const GLint vFormatIntern, const bool mipmap, const GLenum dataType_):
    _mDataType(dataType_),
    _minMapping(mipmap),
    _fileName(NULL)
    {

    glGenTextures(1,&_texObject);
    _targetType = vTargetType;
    _externFormat = vFormatExtern;
    _internFormat = vFormatIntern;
    _width = 0;
    _height = 0;
    _depth = 0;
}



TextureObj::~TextureObj()
{
    glDeleteTextures(1, &_texObject);
}


GLuint TextureObj::GetTexture(void)const
{
	return _texObject;
}

void  TextureObj::Bind(void)
{
    glBindTexture(Type(),_texObject);

}
void TextureObj::UnBind(void)
{
    glBindTexture(Type(),0);
}

GLuint  TextureObj::Width(void)const
{
    return  _width;
}
GLuint  TextureObj::Heigh(void)const
{
    return  _height;
}
GLuint  TextureObj::Depth(void)const
{
    return _depth;
}

GLenum  TextureObj::ExternFormat(void)const
{
    return _externFormat;
}
GLenum  TextureObj::InterFormat(void)const
{
    return  _internFormat;
}

GLenum TextureObj::Type()const
{
    return  _targetType;
}

bool   TextureObj::MapMapping(void)const
{
    return  _minMapping;
}

void         TextureObj::       ExternFormat(GLenum e)
{
    _externFormat = e;
}
void          TextureObj::      InterFormat(GLenum i)
{
    _internFormat = i;
}
void          TextureObj::      TargetType(GLenum t)
{
    _targetType = t;
}

void           TextureObj::DataType(GLenum d)
{
    _mDataType = d;
}

void TextureObj::ClampToEdge()
 {
    glTexParameteri(Type(),GL_TEXTURE_WRAP_S,GL_CLAMP_TO_EDGE);
    if(Heigh() != 0)
    {
        glTexParameteri(Type(),GL_TEXTURE_WRAP_T,GL_CLAMP_TO_EDGE);
        if(Depth() != 0)
        {
            glTexParameteri(Type(),GL_TEXTURE_WRAP_R,GL_CLAMP_TO_EDGE);
        }
    }
}

void TextureObj::MirrorRepeat()
{
    glTexParameteri(Type(),GL_TEXTURE_WRAP_S,GL_REPEAT);
    if(Heigh() != 0)
    {
        glTexParameteri(Type(),GL_TEXTURE_WRAP_T,GL_REPEAT);
        if(Depth() != 0)
        {
            glTexParameteri(Type(),GL_TEXTURE_WRAP_R,GL_REPEAT);
        }
    }
}

void TextureObj::FilterLinear()
 {
    if(_minMapping)
    {
        glTexParameteri(Type(),GL_TEXTURE_MIN_FILTER,GL_LINEAR_MIPMAP_LINEAR);
    }
    else
    {
        glTexParameteri(Type(),GL_TEXTURE_MIN_FILTER,GL_LINEAR);
    }
    glTexParameteri(Type(),GL_TEXTURE_MAG_FILTER,GL_LINEAR);
}

void TextureObj::FilterNearest()
{
    if(_minMapping)
    {
        glTexParameteri(Type(),GL_TEXTURE_MIN_FILTER,GL_NEAREST_MIPMAP_NEAREST);
    }
    else
    {
        glTexParameteri(Type(),GL_TEXTURE_MIN_FILTER,GL_NEAREST);
    }
    glTexParameteri(Type(),GL_TEXTURE_MAG_FILTER,GL_NEAREST);
}

bool TextureObj::Data()
{
    unsigned char* load =  Load();
    if(load != NULL)
    {
        Data(load,Width(),Heigh(),0);
        return  true;
    }

    return  false;
}
void TextureObj::Data(void* data, const unsigned vWidth, const unsigned vHeight, const unsigned vDepth )
{


    if(0 == vDepth)
     {
        if(0 == vHeight)
        {
            glTexImage1D(Type(),0,InterFormat(),vWidth,0,ExternFormat(),_mDataType,data);
        }
        else
        {
            glTexImage2D(Type(),0,InterFormat(),vWidth,vHeight,0,ExternFormat(),_mDataType,data);
        }
    }
    else
     {
        glTexImage3D(Type(),0,InterFormat(),vWidth,vHeight,vDepth,0,ExternFormat(),_mDataType,data);
     }

    if(_minMapping)
    {
        //glTexParameteri(Type(),GL_GENERATE_MIPMAP,GL_TRUE); for version 1.4
       glGenerateMipmap(Type());
    }
    SOIL_free_image_data((unsigned char*)data);

}

unsigned char* TextureObj::Load(void)
{
    if(_fileName != NULL)
    {
        int width, height, channels;
        unsigned char* ht_map = SOIL_load_image(_fileName,&width, &height, &channels,SOIL_LOAD_RGB);

        if(*ht_map == 0)
        {
            printf("load texture %s fail...,and the error is %s", _fileName, SOIL_last_result());
            return  NULL;
        }
        else
        {
            _width = width;
            _height = height;

            return  ht_map;
//            Data(ht_map, _width,_height,0);
        }
    }

    return  NULL;
}

