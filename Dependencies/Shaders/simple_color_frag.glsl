#version 450

uniform sampler2D diffuse_texture;
uniform sampler2D normal_texture;
uniform sampler2D specular_texture;


uniform vec3 cameraPostion;
uniform int numberOfLights;


in vec3 FragPos;
in vec3 vNormal;
in vec2 final_texture_coodinates;
in vec3 vTangent;
in vec3 vBiTangent;


out vec4 final_color;

#define MAXLIGHTS 10

uniform struct Light{
	vec3 m_position;
	vec3 m_ambient;
	vec3 m_diffuse;
	vec3 m_specular;
	float m_shininess;
	
	float m_constant;
    float m_linear;
    float m_quadratic;
	
} lights[MAXLIGHTS];
// Note that this is a declaration of a variable.


vec3 DoLights(vec3 a_norm, Light a_light, vec3 a_FragPos, vec3 a_cameraPostion)
{
	vec3 lightDir = normalize(a_light.m_position - a_FragPos);
	
	// Ambient
	
	 vec3 ambient  = a_light.m_ambient  * vec3(texture(diffuse_texture, final_texture_coodinates));
	
	
	// Diffuse
		
	float diffscale = max(dot(a_norm, lightDir) ,0.0);

	vec3 diffuse = diffscale * a_light.m_diffuse * vec3(texture(diffuse_texture, final_texture_coodinates));
	
	// Diffuse end
	
	// Specular
	
	vec3 viewDir = normalize(a_cameraPostion - a_FragPos);
	
	// note that these are created above.
	vec3 reflrectDir = reflect(-lightDir, a_norm);
	
	float spec = pow(max(dot(viewDir, reflrectDir), 0.0), a_light.m_shininess);
	
	vec3 specular = a_light.m_specular * spec *  vec3(texture(diffuse_texture, final_texture_coodinates));
	
	// Some kind of attenuation otherwise they are just directional lights?
	
	float distance = length(a_light.m_position - a_FragPos);
	
	float attenuation = 1.0 / (a_light.m_constant + a_light.m_linear * distance + a_light.m_quadratic * (distance * distance));    
	
	diffuse *= attenuation;
	specular *= attenuation;
	ambient *= attenuation;
	
	

	return (diffuse + specular + ambient);

}







void main()
{
    //vec4 textureColor = texture(diffuse_texture, final_texture_coodinates);
	//vec4 specularMap = texture(specular_texture, final_texture_coodinates);
	vec4 normalMap = texture(normal_texture, final_texture_coodinates);
	
	
	vec3 N = normalize(vNormal);
	vec3 T = normalize(vTangent);
	vec3 B = normalize(vBiTangent);	
	
	mat3 TBN = mat3(T,B,N);
	
	
	N = TBN * (vec3(normalMap) * 2 - 1);
	
	vec3 lightResult = vec3(0);
	
	
	
	
	

	for(int i = 0; i < numberOfLights; i++)
	{
		lightResult += DoLights(N, lights[i], FragPos, cameraPostion);
	}
	vec3 result = lightResult;// * vec3(textureColor);
	//vec3 result = lightResult * vec3(0,1,0);
	//vec3 result = vec3(0,1,0);
	
	//final_color = vec4(textureColor,1);
	final_color = vec4(result, 1);

}