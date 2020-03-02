#version 450

uniform sampler2D diffuse_texture;
uniform sampler2D specular_texture;
uniform sampler2D normal_texture;

uniform float ambientStrength;
uniform vec3 ambientColor;

uniform vec3 cameraPostion;
uniform int numberOfLights;



uniform vec3 modelColor = vec3(0.01,0.01,0.01);

uniform vec3 lightPosition1;
uniform vec3 lightPosition2;





in vec3 FragPos;
in vec3 normal;
in vec2 final_texture_coodinates;
in vec3 vTangent;
in vec3 vBiTangent;






out vec4 final_color;




#define MAXLIGHTS 10

uniform struct Light{
	vec3 position;
	vec3 color;
	float specularStrength;
} lights[MAXLIGHTS];



vec3 DoLights(vec3 a_norm, Light a_light, vec3 a_FragPos)
{
	vec3 lightDir = normalize(a_light.position - FragPos);
	
	// Diffuse
		
	float diff = max(dot(a_norm, lightDir) ,0.0);

	vec3 diffuse = diff * a_light.color;
	
	// Diffuse end
	
	// Specular
	
	vec3 viewDir = normalize(cameraPostion - FragPos);
	
	// note that these are created above.
	vec3 reflrectDir = reflect(-lightDir, a_norm);
	
	float spec = pow(max(dot(viewDir, reflrectDir), 0.0), 32);
	
	
	vec3 specular = a_light.specularStrength * spec * a_light.color;
	
	
	return specular + diffuse;
	
}


void main()
{
    vec4 textureColor = texture(diffuse_texture, final_texture_coodinates);
	vec4 specularMap = texture(specular_texture, final_texture_coodinates);
	vec4 normalMap = texture(normal_texture,final_texture_coodinates);
	
	
	
	
	// Ambient. Should each light add to this?
	vec3 ambient = ambientStrength * ambientColor;
	
	vec3 norm = normalize(normal);

	
	
	vec3 lightResult;
	
	lightResult += ambient;
	
	// Diffuse calls function above.
	for(int i = 0; i < numberOfLights; i++)
	{
		lightResult += DoLights(norm, lights[i], FragPos);
	}

	
	//vec3 result = lightResult + modelColor;
	//vec3 result = lightResult * vec3(textureColor);
	//vec3 result = vec3(specularMap);
	vec3 result = vec3(normalMap);
	
	final_color = vec4(result,1);
}