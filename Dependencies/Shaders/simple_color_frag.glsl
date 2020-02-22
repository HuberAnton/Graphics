#version 450

uniform sampler2D diffuse_texture;
uniform float ambientStrength;
uniform vec3 ambientColor;
uniform vec3 modelColor;

uniform vec4 color;
vec4 texturecolor;


in vec2 final_texture_coodinates;
out vec4 final_color;



void main()
{
	// Demo to see how to pass colors in as well as textures.
    // texturecolor = texture(diffuse_texture, final_texture_coodinates);
	// final_color = texturecolor * color;
	// final_color = color;

	
	vec3 ambient = ambientStrength * ambientColor;
	vec3 result = ambient * modelColor;
	
	final_color = vec4(result,1);
}