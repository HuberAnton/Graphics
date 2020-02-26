#version 450

uniform sampler2D diffuse_texture;
uniform float ambientStrength;
uniform vec3 ambientColor;

uniform vec3 cameraPostion;

uniform vec3 modelColor = vec3(0.01,0.01,0.01);

uniform vec3 lightPosition1;
uniform vec3 lightPosition2;


uniform vec3 lightColor1 = vec3(1, 0, 1);
uniform vec3 lightColor2 = vec3(0, 1, 1);


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
	vec3 lightDir1 = normalize(lightPosition1 - FragPos);
	
	
	float diff = max(dot(norm, lightDir1) ,0.0);
	
	
	vec3 diffuse = diff * lightColor1;
	
	vec3 lightDir2 = normalize(lightPosition2 - FragPos);
	
	
	diff = max(dot(norm, lightDir2) ,0.0);
	
	
	
	
	
	diffuse += diff * lightColor2; 
	
	// End Diffuse
	
	// Specular
	
	// Directional vector math.
	vec3 viewDir = normalize(cameraPostion - FragPos);
	
	// note that these are created above.
	vec3 reflrectDir = reflect(-lightDir1, norm);
	
	float spec = pow(max(dot(viewDir, reflrectDir), 0.0), 32);
	
	
	vec3 specular = specularStrength * spec * lightColor1;
	
	
	reflrectDir = reflect(-lightDir2, norm);
	
	
	spec = pow(max(dot(viewDir, reflrectDir), 0.0), 32);
	
	
	specular += specularStrength * spec * lightColor2;
	
	
	
	// End specular
	
	
	// Putting it all together.
	
	vec3 result = (ambient + diffuse + specular) + modelColor;
	//vec3 result = (ambient + diffuse + specular) * vec3(texturecolor);
	
	
	
	final_color = vec4(result,1);
}