
#include "ImfArray.h"
#include "ImfRgbaFile.h"            // OpenEXR headers
#include "ImathBox.h"

#include "GL/glew.h"

bool LoadOpenEXRImage(char *fileName, unsigned int textureName, unsigned int &texWidth, unsigned int &texHeight)
{
	try
	{
		Imf::Array2D<Imf::Rgba> pixels;
		Imf::RgbaInputFile file(fileName);
		Imath::Box2i dw = file.dataWindow();

		texWidth = dw.max.x - dw.min.x + 1;
		texHeight = dw.max.y - dw.min.y + 1;

		pixels.resizeErase(texHeight, texWidth);

		file.setFrameBuffer(&pixels[0][0] - dw.min.x - dw.min.y * texWidth, 1, texWidth);
		file.readPixels(dw.min.y, dw.max.y);

		GLfloat* texels = (GLfloat*)malloc(texWidth * texHeight * 3 * sizeof(GLfloat));
		GLfloat* pTex = texels;

		// Copy OpenEXR into local buffer for loading into a texture
		for (unsigned int v = 0; v < texHeight; v++)
		{
			for (unsigned int u = 0; u < texWidth; u++)
			{
				Imf::Rgba texel = pixels[texHeight - v - 1][u];
				pTex[0] = texel.r;
				pTex[1] = texel.g;
				pTex[2] = texel.b;

				pTex += 3;
			}
		}

		// Bind texture, load image, set tex state
		glBindTexture(GL_TEXTURE_2D, textureName);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB16F, texWidth, texHeight, 0, GL_RGB, GL_FLOAT, texels);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

		free(texels);
	}
	catch (Iex::BaseExc & e)
	{
		std::cerr << e.what() << std::endl;
		//
		// Handle exception.
		//
	}

	return true;
}
