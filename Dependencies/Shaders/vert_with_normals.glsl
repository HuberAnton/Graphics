#version 450

layout(location = 0) in vec4 local_position;
layout(location = 1) in vec3 Anormal;
layout(location = 2) in vec2 texture_coordinates;
layout(location = 3) in vec4 Tangent;


uniform mat4 projection_view_matrix;
uniform mat4 model_matrix;
uniform mat3 NormalMatrix;


out vec2 final_texture_coodinates;
out vec3 normal;
out vec3 vTangent;
out vec3 vBiTangent;
out vec3 FragPos;

void main()
{

    final_texture_coodinates = texture_coordinates;
	FragPos = vec3(model_matrix * local_position);
	
	
	// Not sure about these
	vTangent = NormalMatrix * Tangent.xyz;
	vBiTangent = 
	

	// Does not give the expected result...
	//normal =  NormalMatrix * Anormal;
	normal = Anormal;
    gl_Position = (projection_view_matrix * model_matrix) * local_position;
}