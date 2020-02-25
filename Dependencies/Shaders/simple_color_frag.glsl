#version 450

uniform sampler2D diffuse_texture;
uniform float ambientStrength;
uniform vec3 ambientColor;
uniform vec3 lightPosition;
uniform vec3 cameraPostion;

uniform vec3 modelColor = vec3(1,1,1);
uniform vec3 diffuseColor;

uniform float specularStrength;


uniform vec4 color;

in vec3 FragPos;
in vec3 Normal;
in vec2 final_texture_coodinates;
out vec4 final_color;


uniform float shininess = 0.5;

struct PointLight
{
	vec3 Sposition;
	vec3 Sdiffuse;
	vec3 Sspecular;

	
	// constant
	float constant;
	float linear;
	float quadratic;
	
};
#define nmbOfPointLights 2
uniform PointLight pointLights[nmbOfPointLights];

vec3 CalcPointLight(PointLight light, vec3 Normal, vec3 FragPos, vec3 viewDir)
{

	// Light direction of other calcs.
	// Obviously on a per light basis	
	vec3 lightDir = normalize(light.Sposition - FragPos);
	
	// diffuse shadeing happening
	float diff = max(dot(norm, lightDir) ,0.0);
	// Spec shading
	vec3 reflrectDir = reflect(-lightDir, norm);
	float spec = pow(max(dot(viewDir, reflrectDir),0.0), shininess);
	
	// attenuation
	float distance = length(light.Sposition - fragPos);
	float attenuation = 1.0 / (light.co
	
	
	vec3 diffuse = diff * diffuseColor;
}




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
	vec3 norm = normalize(Normal);	
	// For saving the data.
	vec3 result;
	
	for(int i = 0; i < nmbOfPointLights; i++)
	{
		result += CalcPointLight(pointLights[i], norm, FragPos, viewDir);
	}	
	final_color = vec4(result,1);
}