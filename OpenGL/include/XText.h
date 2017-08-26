    //
    //  text.h
    //  OpenGL
    //
    //  Created by xt on 8/12/16
    //  Copyright (c) 2016ƒÍ xt. All rights reserved.
    //

#include "Xtype.h"
#include <map>

struct Character;
class Shader ;

class XText
{
public:


	bool init(void);
	static bool initTextLib(void);
	XText();
	~XText();

	void drawText(const std::string& text, float x, float y, float scale, Vec3f color);

private:

	void initShader(void);

	static std::map<unsigned char, Character*> _characters;

	Shader * _shader;

	unsigned int _vao;

	unsigned int _vbo;

};