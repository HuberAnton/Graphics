#pragma once
#include "glm.hpp"
#include "gl_core_4_5.h"
#include "glfw3.h"
#include "ext.hpp"

class Camera
{
public:

	Camera();

	void UpdateCamera();

	void SetPosition(glm::vec3 a_newPositoin);

	void SetTarget(glm::vec3 a_newTarget);

	glm::mat4 GetView();
	// Note that this is the view that is  
	// multiplied by the perspective then 
	// passed into the shaders.

	// This contains the Right, Up and Direction(which
	// is the reverse of the direction that is displayed.
	// Glm has a lookat function which takes in these 3
	// and places them correctly on the matrix.


	// Actaully I'll wrtite it out just to remeber the process.
	// Camera Pos is jus the postion of the camera.
	glm::vec3 m_cameraPostion; //*** Needs to be accesible.

	// Camera diercion is worked out by getting the camera Target first
	// So where ever the camera should be looking at in xyz postion which 
	// should be the center(?) of the screen.
	glm::vec3 m_cameraTarget; //*** Needs to be accesible.

	// We then minus the camera position by the camera target.
	// Eg: (cam) x1, y2 , z6 - (target) x-2, y2, z 3 = camdireciotn x3 y0 z3
	// We then get the normalized value of that result and bam we have a 
	// direction to point at of 1,0,1. Well after we invert it of course -1, 0, -1 

	//glm::vec3 m_cameraDirection;

	// We then get the Right by firstly getting the up vector in the world.
	// Which is x0, y1, z0. Is it right to think of this as normailized in this case?
	// Sure why not.

	glm::vec3 m_up; //***Might need to be accesible. 

	// Then to get the Right we get the cross product of the up and camera direcion.
	// Note that camera direction and up gives the reverse.
	// We then normalize the value resulting in the cameras Right.

	glm::vec3 m_cameraRight;

	// We then need to get the up position of the camera. Note that this is the 
	// relative 'up' not the world 'up'.
	// We get the cross product of the cameraDirection and cameraRight
	// and the resultis the cameraUp

	glm::vec3 m_cameraUp;

	// With all these peices we now have what we need to define what we are able to see.
	// It's kind of a strange concept if you think about it. A 'Camera' is really only the
	// viewable screen. So we define all this data so that we can then pass it into shader
	// programs which then decide if the mesh(?) is in a viewable space. Kinda nifty.
	// Anyway Glm has a function which will correctly place these peice of data into
	// a matrix for us. Note that we still need a vector3 seperate with the inverse of
	// the positions which we store seperatly.


	// So in short we need:
	// A postion of the camera
	// A target postion
	// A World up.

	// The rest will be worked out GLM but it is worth knowing.

	glm::mat4 m_viewMatrix;




	// Note that I feel the inclusion of perspective matrix here should be A~okay
	// due to it not being modified elsewhere. Even if it is modified I don't feel
	// it is out of place. The quesiton is should I default the projection matrix
	// construciton or should I allow for passing it in?

	void SetPerspeciveMatrix();

	glm::mat4 m_projectionMatrix;


	//Combined projection view matrix to be passed into the 

	glm::mat4 m_projectionViewMatrix;

};

