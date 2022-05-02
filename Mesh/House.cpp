#include "House.h"

House::House(Shader& shader, bool bRoof)
	:VisualObject(shader)
{
	float z = 5;
	float spike = 10;

	///FRONT WALL
		//LEFT SIDE
	mVertices.push_back(Vertex{ 0, 0, 0,  0,0,0, 0,0 });
	mVertices.push_back(Vertex{ 5, 0, 0,  0,1,0 ,1,0});
	mVertices.push_back(Vertex{ 5, 0, z,  0,0,0 ,0,1});

	mVertices.push_back(Vertex{ 0, 0, 0,  0,0,0, 0,0});
	mVertices.push_back(Vertex{ 0, 0, z,  0,1,0, 1,0 });
	mVertices.push_back(Vertex{ 5, 0, z,  0,0,0, 0,1 });

		//RIGHT SIDE
	mVertices.push_back(Vertex{ 7, 0, 0,  0,0,0 });
	mVertices.push_back(Vertex{ 12, 0, 0,  0,1,0 });
	mVertices.push_back(Vertex{ 12, 0, z,  0,0,0 });

	mVertices.push_back(Vertex{ 7, 0, 0,  0,0,0 });
	mVertices.push_back(Vertex{ 7, 0, z,  0,1,0 });
	mVertices.push_back(Vertex{ 12, 0, z,  0,0,0 });


	///LEFT WALL
	mVertices.push_back(Vertex{ 0, 0, 0,  0,0,0 });
	mVertices.push_back(Vertex{ 0, 12, 0,  0,1,0 });
	mVertices.push_back(Vertex{ 0, 12, z,  0,0,0 });

	mVertices.push_back(Vertex{ 0, 0, 0,  0,0,0 });
	mVertices.push_back(Vertex{ 0, 0, z,  0,1,0 });
	mVertices.push_back(Vertex{ 0, 12, z,  0,0,0 });

	///RIGHT WALL
	mVertices.push_back(Vertex{ 12, 0, 0,  0,0,0 });
	mVertices.push_back(Vertex{ 12, 12, 0,  0,1,0 });
	mVertices.push_back(Vertex{ 12, 12, z,  0,0,0 });

	mVertices.push_back(Vertex{ 12, 0, 0,  0,0,0 });
	mVertices.push_back(Vertex{ 12, 0, z,  0,1,0 });
	mVertices.push_back(Vertex{ 12, 12, z,  0,0,0 });

	///BACK WALL
	mVertices.push_back(Vertex{ 0, 12, 0,  0,1,0 });
	mVertices.push_back(Vertex{ 12, 12, 0,  0,1,0 });
	mVertices.push_back(Vertex{ 12, 12, z,  0,1,0 });

	mVertices.push_back(Vertex{ 0, 12, 0,  0,1,0 });
	mVertices.push_back(Vertex{ 0, 12, z,  0,1,0 });
	mVertices.push_back(Vertex{ 12, 12, z,  0,1,0 });

	if (bRoof)
	{
		///ROOF
			//FRONT
		mVertices.push_back(Vertex{ 0, 0, z,  0,1,0 });
		mVertices.push_back(Vertex{ 12, 0, z,  0,1,0 });
		mVertices.push_back(Vertex{ 6, 6, spike,  0,0,1 });
			//LEFT
		mVertices.push_back(Vertex{ 0, 0, z,  0,1,0 });
		mVertices.push_back(Vertex{ 0, 12, z,  0,1,0 });
		mVertices.push_back(Vertex{ 6, 6, spike,  0,0,1 });
			//RIGHT
		mVertices.push_back(Vertex{ 12, 0, z,  0,1,0 });
		mVertices.push_back(Vertex{ 12, 12, z,  0,1,0 });
		mVertices.push_back(Vertex{ 6, 6, spike,  0,0,1 });
			//BACK
		mVertices.push_back(Vertex{ 0, 12, z,  0,1,0 });
		mVertices.push_back(Vertex{ 12, 12, z,  0,1,0 });
		mVertices.push_back(Vertex{ 6, 6, spike,  0,0,1 });
	}

}

House::~House()
{
}

void House::init()
{

	initializeOpenGLFunctions();

	//Vertex Array Object - VAO
	glGenVertexArrays(1, &mVAO);
	glBindVertexArray(mVAO);

	//Vertex Buffer Object to hold vertices - VBO
	glGenBuffers(1, &mVBO);
	glBindBuffer(GL_ARRAY_BUFFER, mVBO);

	glBufferData(GL_ARRAY_BUFFER,      //what buffer type
		mVertices.size() * sizeof(Vertex),			   //how big buffer do we need
		mVertices.data(),             //the actual vertices
		GL_STATIC_DRAW				 //should the buffer be updated on the GPU
	);

	// 1st attribute buffer : vertices
	glBindBuffer(GL_ARRAY_BUFFER, mVBO);
	glVertexAttribPointer(
		0,                  // attribute. No particular reason for 0, but must match layout(location = 0) in the vertex shader.
		3,                  // size / number of elements of data type
		GL_FLOAT,           // data type
		GL_FALSE,           // normalize data
		sizeof(Vertex),  // stride
		reinterpret_cast<GLvoid*>(0));          // array buffer offset
	glEnableVertexAttribArray(0);

	// 2nd attribute buffer : colors
	// Same parameter list as above but attribute and offset is adjusted accoringly
	glVertexAttribPointer(
		1,
		3,
		GL_FLOAT,
		GL_FALSE,
		sizeof(Vertex),
		reinterpret_cast<GLvoid*>(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	glBindVertexArray(0);	//release


}

void House::draw()
{

	glBindVertexArray(mVAO);
	glUniformMatrix4fv(mShader.mMatrixUniform, 1, GL_FALSE, glm::value_ptr(mMatrix));
	glDrawArrays(GL_TRIANGLES, 0, mVertices.size());
}

void House::move(float x, float y, float z)
{
	mx += x;
	my += y;
	mz += z;

	glm::vec3 pos = glm::vec3(mx, my, mz);
	mPosition = pos;
	glm::translate(mMatrix, pos);

}
