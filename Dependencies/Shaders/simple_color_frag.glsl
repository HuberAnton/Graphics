#version 450

uniform vec4 color = vec4(1,1,1,1);


out vec4 final_color;

in vec3 outnormal


void main()
{
	final_color = vec3(outnormal, 1);
}