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

	Texture();

	Texture(int num);

	~Texture();

	void init(unsigned int flag, unsigned int interalFormat, unsigned int format, const char *imageFile);
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
