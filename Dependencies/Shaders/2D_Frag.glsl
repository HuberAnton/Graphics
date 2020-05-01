#version 450


// Will eventually take in a color.
// Wait I'll just use worldspace for color lel.


in vec3 FragPos;
out vec4 final_color;

void main()
{	
	final_color = vec4(FragPos.x, FragPos.y, 1, 1);
}