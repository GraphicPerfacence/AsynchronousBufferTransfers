

//#version 330
#version 140
precision highp float;
precision highp int;

uniform float max_sides;
uniform samplerBuffer tb_blocks;
uniform int block_type;
uniform int start_index;
uniform mat4 mvp;

out vec3 color;

#define PI 3.14159265358979323846
#define TWO_PI 6.28318530717958647692
#define SQRT_2 1.414213562

void main()
{
	int index = ((gl_InstanceID >> (block_type >= 1 ? 1 : 0)) + start_index) << 2;

	mat4 tm = mvp * mat4(
		texelFetch(tb_blocks, index),
		texelFetch(tb_blocks, index + 1),
		texelFetch(tb_blocks, index + 2),
		texelFetch(tb_blocks, index + 3));

	// PILLAR / CYLINDER
	if(block_type == 0) 
	{
		float num_sides = max_sides; ///TODO lod
		float angle = (round(float(gl_VertexID >> 1) * (num_sides / max_sides)) / num_sides) * TWO_PI;
		gl_Position = tm * vec4(cos(angle), (gl_VertexID & 1) << 1, sin(angle), 1);
	}
	// BOX
	else if(block_type == 1) 
	{
		float angle = float(gl_VertexID >> 1) * 0.25 * TWO_PI - PI * 0.25;

		if((gl_InstanceID & 1) != 0) {
			angle += PI;
			gl_Position = tm * vec4(
				cos(angle) * SQRT_2,
				(gl_VertexID & 1) << 1,
				sin(angle) * SQRT_2,
				1);
		}
		else {
			gl_Position = tm * vec4(
				(1 - (gl_VertexID & 1)) * 2 - 1,
				cos(angle) * SQRT_2 + 1.0,
				sin(angle) * SQRT_2,
				1);
		}
	}
	// STAIRS
	else if(block_type == 2) 
	{
		int vtx_id=gl_VertexID + 2;

		if((gl_InstanceID & 1) != 0) {
			float step_size = 1.0/20.0;
			float step_pos = (vtx_id >> 2) * step_size * 2;
			gl_Position = tm * vec4(
				(1 - (vtx_id & 1)) * 2 - 1,
				step_pos,
				-1.0 + step_pos + ((vtx_id & 2) - 1) * step_size,
				1);
		}
		else {
			int vtx_id_clamped = clamp(vtx_id,0,2);
			float step_size = 1.0/20.0;
			float step_pos = (vtx_id >> 2) * step_size * 2;
			gl_Position = tm * vec4(
				-1,
				step_pos + ((vtx_id_clamped & 2) - 1) * step_size,
				-1.5 + step_pos + ((vtx_id_clamped & 1) * 2 - 1) * step_size,
				1);
		}
	}
	color=vec3(gl_VertexID/32.0);
}
