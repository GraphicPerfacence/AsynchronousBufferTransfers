//
//  texture.h
//  OpenGL
//
//  Created by xt on 15/8/20.
//  Copyright (c) 2015年 xt. All rights reserved.
//

#ifndef __OpenGL__texture__
#define __OpenGL__texture__

class Texture
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

	Texture();

	Texture(int num);

	~Texture();

	void init(unsigned int interalFormat, unsigned int format, const char *imageFile,unsigned int flag = TEXTURE_LOAD_AUTO);
	void init(int n, unsigned int interalFormat, unsigned int format, unsigned int w, unsigned int h, const void* data);

	void initRGBFile(const char* imgFile);

	unsigned int getTexture(unsigned int index = 0)const;

	void bind(void);
	void unBind(void);

protected:
	unsigned int* texture;
private:
	unsigned int  _textureNum;
};

#endif /* defined(__OpenGL__texture__) */
