#version 450

uniform vec4 color = vec4(0.0,0.0,0.0,1.0);

out vec4 final_color;

void main()
{
	final_color = color;
}