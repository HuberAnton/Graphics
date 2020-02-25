#version 450

layout(location = 0) in vec4 local_position;
layout(location = 1) in vec3 Anormal;
layout(location = 2) in vec2 texture_coordinates;



uniform mat4 projection_view_matrix;
uniform mat4 model_matrix;



out vec2 final_texture_coodinates;
out vec3 normal;
out vec3 FragPos;


void main()
{
    final_texture_coodinates = texture_coordinates;
	FragPos = vec3(model_matrix * local_position);
	normal = Anormal;
    gl_Position = (projection_view_matrix * model_matrix) * local_position;
}



