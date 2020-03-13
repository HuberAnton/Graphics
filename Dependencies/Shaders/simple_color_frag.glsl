#version 450

uniform sampler2D diffuse_texture;
uniform sampler2D normal_texture;
uniform sampler2D specular_texture;


uniform float ambientStrength;
uniform vec3 ambientColor;

uniform vec3 cameraPostion;
uniform int numberOfLights;



uniform vec3 modelColor = vec3(0.01,0.01,0.01);

uniform vec3 lightPosition1;
uniform vec3 lightPosition2;





in vec3 FragPos;
in vec3 vNormal;
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
// Note that this is a declaration of a variable.


vec3 DoLights(vec3 a_norm, Light a_light, vec3 a_FragPos, vec3 a_cameraPostion)
{
	vec3 lightDir = normalize(a_light.position - a_FragPos);
	
	// Diffuse
		
	float diffscale = max(dot(a_norm, lightDir) ,0.0);

	vec3 diffuse = diffscale * a_light.color;
	
	// Diffuse end
	
	// Specular
	
	vec3 viewDir = normalize(a_cameraPostion - a_FragPos);
	
	// note that these are created above.
	vec3 reflrectDir = reflect(-lightDir, a_norm);
	
	float spec = pow(max(dot(viewDir, reflrectDir), 0.0), 32);
	
	
	//vec3 specular = a_light.specularStrength * spec * a_light.color;
	vec3 specular = a_light.specularStrength * spec * vec3(1,1,1);
	//return diff; float 
	return diffuse + specular;
	//return specular;
	
}


void main()
{
    vec4 textureColor = texture(diffuse_texture, final_texture_coodinates);
	//vec4 specularMap = texture(specular_texture, final_texture_coodinates);
	vec4 normalMap = texture(normal_texture, final_texture_coodinates);
	
	
	vec3 debugVal;
	
	
	// Ambient. Should each light add to this?
	vec3 ambient = ambientStrength * ambientColor;
	
	vec3 N = normalize(vNormal);
	vec3 T = normalize(vTangent);
	vec3 B = normalize(vBiTangent);	
	
	mat3 TBN = mat3(T,B,N);
	
	
	N = TBN * (vec3(normalMap) * 2 - 1);
	
	vec3 lightResult = vec3(0);
	
	debugVal = normalMap.xyz;
	
	lightResult += ambient;
	float greyscale;
	// Diffuse calls function above.
	for(int i = 0; i < numberOfLights; i++)
	{
		lightResult += DoLights(N, lights[i], FragPos, cameraPostion);
	}
		

	vec3 result = lightResult * vec3(textureColor);
	//vec3 result = lightResult * vec3(0,1,0);
	//vec3 result = vec3(0,1,0);
	
	//final_color = vec4(textureColor,1);
	final_color = textureColor;
	//final_color = vec4(greyscale,greyscale,greyscale, 1);
	//final_color = vec4(debugVal.x, 0, debugVal.y, 1);
}