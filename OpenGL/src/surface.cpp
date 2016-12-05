
#include "../include/surface.h"

#include <gl/glew.h>

void drawCube(void)
{
	float size = 1.0f;
	float scale = 0.2f;
	float delta = 0.1f;

	float A[3] = { size,  size,  size * scale + delta };
	float B[3] = { size,  size, -size * scale + delta };
	float C[3] = { size, -size, -size * scale };
	float D[3] = { size, -size,  size * scale };
	float E[3] = { -size,  size,  size * scale + delta };
	float F[3] = { -size,  size, -size * scale + delta };
	float G[3] = { -size, -size, -size * scale };
	float H[3] = { -size, -size,  size * scale };

	float I[3] = { 1.0f,  0.0f,  0.0f };
	float K[3] = { -1.0f,  0.0f,  0.0f };
	float L[3] = { 0.0f,  0.0f, 1.0f };
	float M[3] = { 0.0f,  0.0f,  -1.0f };
	float N[3] = { 0.0f,  1.0f,  0.0f };
	float O[3] = { 0.0f, -1.0f,  0.0f };


	glBegin(GL_QUADS);

	glNormal3fv(I);

	glTexCoord2f(1, 1);
	glVertex3fv(D);
	glTexCoord2f(0, 1);
	glVertex3fv(C);
	glTexCoord2f(0, 0);
	glVertex3fv(B);
	glTexCoord2f(1, 0);
	glVertex3fv(A);

	glNormal3fv(K);

	glTexCoord2f(1, 1);
	glVertex3fv(G);
	glTexCoord2f(0, 1);
	glVertex3fv(H);
	glTexCoord2f(0, 0);
	glVertex3fv(E);
	glTexCoord2f(1, 0);
	glVertex3fv(F);

	glNormal3fv(L);

	glTexCoord2f(1, 1);
	glVertex3fv(C);
	glTexCoord2f(0, 1);
	glVertex3fv(G);
	glTexCoord2f(0, 0);
	glVertex3fv(F);
	glTexCoord2f(1, 0);
	glVertex3fv(B);

	glNormal3fv(M);

	glTexCoord2f(1, 1);
	glVertex3fv(H);
	glTexCoord2f(0, 1);
	glVertex3fv(D);
	glTexCoord2f(0, 0);
	glVertex3fv(A);
	glTexCoord2f(1, 0);
	glVertex3fv(E);

	glNormal3fv(N);

	glTexCoord2f(1, 1);
	glVertex3fv(E);
	glTexCoord2f(0, 1);
	glVertex3fv(A);
	glTexCoord2f(0, 0);
	glVertex3fv(B);
	glTexCoord2f(1, 0);
	glVertex3fv(F);

	glNormal3fv(O);

	glTexCoord2f(1, 1);
	glVertex3fv(G);
	glTexCoord2f(0, 1);
	glVertex3fv(C);
	glTexCoord2f(0, 0);
	glVertex3fv(D);
	glTexCoord2f(1, 0);
	glVertex3fv(H);

	glEnd();
}