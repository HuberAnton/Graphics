#pragma once

#include "glm.hpp"

// Note that this information is stored in a mtl file not 
// in the obj.


class Material
{
	// I'm going to define what the variables are in long form as well.
	// I'll probably use the obj loader version but for my own reference
	// I feel it's better to write the terms a few more times.


	// This is using the Phong lighting method.

	// Diffuse					or					albedo
	// Color when the object is illuminated			Color before illumination
	// Rgb
	glm::vec3 Kd;
	// Specular
	// The reflective color of the surface
	// RGB in this case but can be greyscale * Diffuse
	glm::vec3 Ks;
	// Specular power
	// Controls the sharpness of the specular reflection.
	// Intesity? Maybe?
	// Float
	float specularPower;
	// Ambient
	// The color of the object regardless of light.
	// Rgb
	glm::vec3 Ka;

};

