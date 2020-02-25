#version 450

// This is goign to be very similar to the other
// frag shader but with the names changed to 
// how they appear in the formula.
// Note as well that I'll need to pass ALL the lights
// in the scene and then get the information. I'm not sure
// how that is expected to work but hey lets go.

in vec2 final_texture_coodinates
in vec3 normal;
in vec3 FragPos;


uniform vec3 Ia; // Ambient color

uniform vec3 Id; // Diffuse color
uniform vec3 Is; // Specular color
uniform vec3 LightDirection;

out vec4 final_color;


// I Really don't want to do this but since I don't
// Know what the shorthand stands for I have to basically redo
// the simple_color_frag.



void main()
{
	


	final_color = vec4(result, 1);
}