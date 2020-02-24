#version 450

uniform sampler2D diffuse_texture;
uniform float ambientStrength;
uniform vec3 ambientColor;
uniform vec3 lightPosition;
uniform vec3 cameraPostion;

uniform vec3 modelColor = vec3(1,1,1);
uniform vec3 lightColor = vec3(1, 1, 1);

float specularStrength = 0.5;


uniform vec4 color;

in vec3 FragPos;
in vec3 normal;
in vec2 final_texture_coodinates;
out vec4 final_color;

void main()
{
	// Demo to see how to pass colors in as well as textures.
    vec4 texturecolor = texture(diffuse_texture, final_texture_coodinates);
	// final_color = texturecolor * color;
	// final_color = color;
	// final_color = texturecolor;
	
	// Ambient
	vec3 ambient = ambientStrength * ambientColor;
	
	
	// Diffuse
	// Ensure the value of the normal is within -1 to 1;
	vec3 norm = normalize(normal);
	
	// Get the direction of the light.
	// Simple vector math.
	// Since only need the direction it is normalized.
	vec3 lightDir = normalize(lightPosition - FragPos);
	
	
	float diff = max(dot(norm, lightDir) ,0.0);
	
	
	vec3 diffuse = diff * lightColor;
	
	// End Diffuse
	
	// Specular
	
	// Directional vector math.
	vec3 viewDir = normalize(cameraPostion - FragPos);
	
	// note that these are created above.
	vec3 reflrectDir = reflect(-lightDir, norm);
	
	float spec = pow(max(dot(viewDir, reflrectDir), 0.0), 32);
	
	
	vec3 specular = specularStrength * spec * lightColor;
	
	// End specular
	
	
	// Putting it all together.
	
	//vec3 result = (ambient + diffuse + specular) * modelColor;
	vec3 result = (ambient + diffuse + specular) * vec3(texturecolor);
	
	
	
	final_color = vec4(result,1);
}