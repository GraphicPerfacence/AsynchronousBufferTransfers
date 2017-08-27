//
//  texture.h
//  OpenGL
//
//  Created by xt on 15/8/20.
//  Copyright (c) 2015年 xt. All rights reserved.
//

#ifndef __OpenGL__texture__
#define __OpenGL__texture__

#include <GL/glew.h>

class TextureObj
{
public:

    enum
    {
        TEXTURE_LOAD_AUTO = 0,
        TEXTURE_LOAD_L = 1,
        TEXTURE_LOAD_LA = 2,
        TEXTURE_LOAD_RGB = 3,
        TEXTURE_LOAD_RGBA = 4
    };

    TextureObj(const char*imgFileName);

    TextureObj(const GLenum vTargetType = GL_TEXTURE_2D,
               const GLint vFormatExtern = GL_RGBA, const GLint vFormatIntern = GL_RGBA,
               const bool mipmap = false, const GLenum dataType_ = GL_UNSIGNED_BYTE);

	~TextureObj();

    void                Data(void* data, const unsigned vWidth, const unsigned vHeight = 0, const unsigned vDepth = 0);

    bool                Data();
    
    unsigned char*      Load(void);
    
    GLuint              GetTexture(void)const;
    
    

    void                MirrorRepeat();
    void                ClampToEdge();

    void                FilterLinear();
    void                FilterNearest();
    
	void                Bind(void);
	void                UnBind(void);

    GLenum              Type(void)const;
    GLuint              Width(void)const;
    GLuint              Heigh(void)const;
    GLuint              Depth(void)const;

    GLenum              ExternFormat(void)const;
    GLenum              InterFormat(void)const;

    void                ExternFormat(GLenum);
    void                InterFormat(GLenum);
    void                TargetType(GLenum);
    void                DataType(GLenum);

    bool                MapMapping(void)const;
private:

    const char*         _fileName;

    GLenum              _targetType;
    GLenum              _mDataType;
    GLenum              _externFormat;
    GLenum              _internFormat;
    GLuint              _width;
    GLuint              _height;
    GLuint              _depth;
    bool                _minMapping;

    GLuint              _texObject;

};

#endif /* defined(__OpenGL__texture__) */
