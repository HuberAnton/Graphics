#include "Mesh.h"



// Handles all cleanup.
// Since this is handled by open gl we call the funcitons to deal with it.

Mesh::~Mesh()
{
	glDeleteVertexArrays(1, &m_vao);
	glDeleteBuffers(1, &m_vbo);
	glDeleteBuffers(1, &m_ibo);
}


void Mesh::Draw()
{
	// So we switch to the state we want to use for the draw which is handily contained
	// within the class.
	glBindVertexArray(m_vao);
	// We check if there is an Ibo associated.
	//if (m_ibo != 0)
		// If there isn't we must pass in more information.
	//	glDrawElements(GL_TRIANGLES, 3 * m_triCount, GL_UNSIGNED_INT, 0);
	//else
		// If there is we can pass less.
	//	glDrawArrays(GL_TRIANGLES, 0, 3 * m_triCount);

	// As a side note I'm not sure if having a shader in the class as well would be useful or good.
	// I might need to make a mesh a variable of another class.
}





// VAO == Vertex array object. Both the VertexBufferObject/VBO(or data) 
// and IndexBufferObject/IBO(optional. Stores a list of what order to draw the
// vertexes in.)

// These Vao stores both of them.
void Mesh::InitialiseQuad()
{
	// Checks if the mesh has been initalised already.
	// Since glGenVertexArray, whcih needs to be called assaigns
	// a number to this buffer it will == 0 if not initalised.
	assert(m_vao == 0);
	
	// If not initalised generate buffers and arrays.

	// Generate a vertex array object and return an identifier.
	glGenVertexArrays(1, &m_vao);
	// Generate a vertex buffer object and return an identifier.
	glGenBuffers(1, &m_vbo);

	// Binding is pretty much 'select this to modify' in opengl.
	// It is switching to a state.
	glBindVertexArray(m_vao);
	glBindBuffer(GL_ARRAY_BUFFER, m_vbo);


	// Note that this part of the code will need to be removed/modified
	// and only exists for testing. There should be a loading function here
	// which reads a file and then converts that into verts.
	Vertex vertices[6];
	vertices[0].postion = { -0.5f, 0, 0.5f, 1 };
	vertices[1].postion = { 0.5f, 0, 0.5f, 1 };
	vertices[2].postion = { -0.5f, 0, -0.5f, 1 };

	vertices[3].postion = { -0.5f, 0, -0.5f, 1 };
	vertices[4].postion = { 0.5f, 0, 0.5f, 1 };
	vertices[5].postion = { 0.5f, 0, -0.5f, 1 };

	// We now assagin the data that we have received about the model and pass it
	// to the vbo that is currently bound. Now it knows how large, where to look for
	// the data and what to do with it. It still doesn't know what the data actully is.
	glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(Vertex), vertices, GL_STATIC_DRAW);

	// We now define what is contain within that buffer.
	
	// We are defining the first attribute in the buffer.
	glEnableVertexAttribArray(0);
	// The specifics of the data go here.
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
	// We would need to add more attributes here if more.

	// We bind to 0. 0 is always nothing so doing this is the equivalant to
	// unselecting something. I think this is mostly a safety feature or convention.
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

}