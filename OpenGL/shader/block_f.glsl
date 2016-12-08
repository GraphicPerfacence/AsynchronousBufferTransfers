

#version 140
//#version 330
precision highp float;
precision highp int;

in vec3 color;

out vec4 _retval;

void main()
{
	_retval = vec4(color, 0);
}
