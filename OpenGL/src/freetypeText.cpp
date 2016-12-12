#include "../include/text.h"

#include <ft2build.h>
#include FT_FREETYPE_H
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <gl/glew.h>

#include "../include/shader.hpp"
#include "../include/sys.h"
#include "../include/log.h"

#include <string>

struct Character
{
	GLuint		textureID;
	glm::ivec2	size;
	glm::ivec2	bearing;
	GLuint		advance;
};


std::map<unsigned char, Character*> rOGLText::_characters;

const char* getFreetypeErrorMessage(FT_Error err)
{
#undef __FTERRORS_H__
#define FT_ERRORDEF( e, v, s )  case e: return s;
#define FT_ERROR_START_LIST     switch (err) {
#define FT_ERROR_END_LIST       }
#include FT_ERRORS_H
	return "(Unknown error)";
}

bool rOGLText::initTextLib(void)
{	
	FT_Error error;

	FT_Library    library;

	error = FT_Init_FreeType(&library);
	if (error != 0)
	{
		return false;
	}

	const char * fontPath;
#if defined X_OS_WIN32 || defined X_OS_WIN64 
	fontPath = "e:/calibri.ttf";
#elif  __APPLE__
	fontPath = "/System/Library/Fonts/Keyboard.ttf";
#endif

	FT_Face       face;
	 
	error = FT_New_Face(library, fontPath, 0, &face);
	if(error == FT_Err_Unknown_File_Format)
	{
		Log::Instance()->printMessage("\
				the font file could be opened and read, but it appears,\
				that its font format is unsupported");
		return false;
	}
	else if (error)
	{
		const char* message = getFreetypeErrorMessage(error);

		Log::Instance()->printMessage(message);
		return false;
	}
	//set font's width and height 
	error =  FT_Set_Pixel_Sizes(face,0,48);
	if (error)
	{
		return false;
	}

	glPixelStorei(GL_UNPACK_ALIGNMENT,1);

	for(GLubyte c = 0;c < 128;c++)
	{
		if(FT_Load_Char(face,c,FT_LOAD_RENDER))
		{
			continue;
		}

		GLuint texture;
		glGenTextures(1,&texture);
		glBindTexture(GL_TEXTURE_2D, texture);
		glTexImage2D(
			GL_TEXTURE_2D,
			0,
			GL_RED,
			face->glyph->bitmap.width,
			face->glyph->bitmap.rows,
			0,
			GL_RED,
			GL_UNSIGNED_BYTE,
			face->glyph->bitmap.buffer
			);
		// Set texture options
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		Character * cr = new Character;
		cr->textureID =  texture;
		cr->size = glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows);
		cr->bearing =  glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top);
		cr->advance = face->glyph->advance.x;

		_characters.insert(std::pair<unsigned char, Character*>(c,cr));
	}

	FT_Done_Face(face);
	FT_Done_FreeType(library);

	glPixelStorei(GL_UNPACK_ALIGNMENT,4);
	
	return true;
}

void rOGLText::initShader(void)
{
	_shader = new Shader;

	//_shader->LoadShaderSouce(textVertexString.c_str(),textFragString.c_str(),NULL);
	_shader->LoadShaders("D:/projects/opengl/Perfance/Asy/OpenGL/shader/text.vert", "D:/projects/opengl/Perfance/Asy/OpenGL/shader/text.frag", NULL);

	_shader->TurnOn();

	GLuint loc =  _shader->GetVariable("textSample");
	_shader->SetInt(loc, 0);
	_shader->TurnOff();
}


void rOGLText::drawText(const std::string& text, GLfloat x, GLfloat y, GLfloat scale, glm::vec3 color)
{
	GLboolean blendEnabled;
	glGetBooleanv(GL_BLEND, &blendEnabled);

	// save off current state of src / dst blend functions
	GLint blendSrc;
	GLint blendDst;
	glGetIntegerv(GL_BLEND_SRC_ALPHA, &blendSrc);
	glGetIntegerv(GL_BLEND_DST_ALPHA, &blendDst);

	_shader->TurnOn();

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	GLuint projL =  glGetUniformLocation(_shader->getShaderId(), "projection");
	
	glm::mat4 projection = glm::ortho(0.0f, 800.0f, 0.0f, 600.0f);

	glUniformMatrix4fv(projL, 1, GL_FALSE, glm::value_ptr(projection));

	glUniform3f(glGetUniformLocation(_shader->getShaderId(), "textColor"), color.x, color.y, color.z);
	glActiveTexture(GL_TEXTURE0);
	glBindVertexArray(_vao);

	// Iterate through all characters
	std::string::const_iterator c;
	for (c = text.begin(); c != text.end(); c++)
	{
		Character* ch = _characters[*c];

		GLfloat xpos = x + ch->bearing.x * scale;
		GLfloat ypos = y - (ch->size.y - ch->bearing.y) * scale;

		GLfloat w = ch->size.x * scale;
		GLfloat h = ch->size.y * scale;
		// Update VBO for each character
		GLfloat vertices[6][4] = {
			{ xpos,     ypos + h,   0.0, 0.0 },            
			{ xpos,     ypos,       0.0, 1.0 },
			{ xpos + w, ypos,       1.0, 1.0 },

			{ xpos,     ypos + h,   0.0, 0.0 },
			{ xpos + w, ypos,       1.0, 1.0 },
			{ xpos + w, ypos + h,   1.0, 0.0 }           
		};
		// Render glyph texture over quad
		glBindTexture(GL_TEXTURE_2D, ch->textureID);
		// Update content of VBO memory
		glBindBuffer(GL_ARRAY_BUFFER, _vbo);
		glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices); 
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		// Render quad
		glDrawArrays(GL_TRIANGLES, 0, 6);
		// Now advance cursors for next glyph (note that advance is number of 1/64 pixels)
		x += (ch->advance >> 6) * scale; // Bitshift by 6 to get value in pixels (2^6 = 64)
	}
	glBindVertexArray(0);
	glBindTexture(GL_TEXTURE_2D, 0);

	_shader->TurnOff();

	if (blendEnabled) {
		glEnable(GL_BLEND);
	}
	else {
		glDisable(GL_BLEND);
	}

	glBlendFunc(blendSrc, blendDst);
}
