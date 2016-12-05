

#version 330

uniform TransformBlock //block
{
	float scale;
	vec3 translation;
	float rotation[3];
	mat4 projection_matrix;
} transform; //instance


