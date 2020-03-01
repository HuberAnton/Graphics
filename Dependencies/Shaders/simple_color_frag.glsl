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

uniform vec3[numberOfLights]

float specularStrength = 0.5;

in vec3 FragPos;
in vec3 normal;
in vec2 final_texture_coodinates;
out vec4 final_color;


#define numberOfLights = 2;

vec3 CalculateDiffuse(vec3 a_norm, vec3 a_lightPosition, vec3 a_FragPos, vec3 a_lightColor)
{
	
	vec3 lightDir = normalize(lightPosition - FragPos);
	
	float diff = max(dot(norm, lightDir) ,0.0);

	return diff * lightColor;
	
}





void main()
{
    vec4 texturecolor = texture(diffuse_texture, final_texture_coodinates);
	
	// Ambient. Should eaxch light add to this?
	vec3 ambient = ambientStrength * ambientColor;
	
	vec3 norm = normalize(normal);
	
	// Diffuse calls function above.
	for(int i = 0; i < numberOfLights; i++)
	{
		vec3 diffuse += CalculateDiffuse(norm, lightPosition, FragPos, lightColor);
	}
	
	
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