#version 450

layout(location = 0) in vec4 local_position;
layout(location = 1) in vec4 Anormal;
layout(location = 2) in vec2 texture_coordinates;
layout(location = 3) in vec4 Tangent;


uniform mat4 projection_view_matrix;
uniform mat4 model_matrix;
uniform mat3 NormalMatrix;

out vec3 FragPos;
out vec3 vNormal;
out vec2 final_texture_coodinates;
out vec3 vTangent;
out vec3 vBiTangent;


void main()
{
    final_texture_coodinates = texture_coordinates;
	FragPos = vec3(model_matrix * local_position);

	// SHOULD BE DONE CPU SIDE
	vTangent = inverse(transpose(mat3(model_matrix))) * Tangent.xyz;
	
	vBiTangent = cross(vec3(Anormal), vec3(Tangent)) * Tangent.w;
	
	// SHOULD BE DONE CPU SIDE
	vNormal = inverse(transpose(mat3(model_matrix))) * vec3(Anormal);
    gl_Position = (projection_view_matrix * model_matrix) * local_position;
}



