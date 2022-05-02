#include "Door.h"

Door::Door(Shader& shader)
	:VisualObject(shader)
{
	float width = 2.f;
	float height = 5.0f;

	mVertices.push_back(Vertex{ 0, 0, 0,  0,0,0 });
	mVertices.push_back(Vertex{ width, 0, 0,  1,0,0 });
	mVertices.push_back(Vertex{ width, 0, height,  0,0,1 });

	mVertices.push_back(Vertex{ 0, 0, 0,  0,0,0 });
	mVertices.push_back(Vertex{ 0, 0, height,  1,0,0 });
	mVertices.push_back(Vertex{ width, 0, height,  0,0,1 });

}

Door::~Door()
{
}

void Door::init()
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

void Door::draw()
{
	if (bActivated)
	{
		rotateDoor(1.f);
	}
	

	glBindVertexArray(mVAO);
	glUniformMatrix4fv(mShader.mMatrixUniform, 1, GL_FALSE, glm::value_ptr(mMatrix));
	glDrawArrays(GL_TRIANGLES, 0, mVertices.size());
}

void Door::move(float x, float y, float z)
{
	mx += x;
	my += y;
	mz += z;

	glm::vec3 pos = glm::vec3( mx,my,mz );
	mPosition = pos;
	glm::translate(mMatrix, pos);
	

}

bool Door::activate(float f)
{
	bActivated = true;

	return true;

}

void Door::rotateDoor(float dt)
{

	int dir = 1;

	if (bOpen)
	{
		dir = -1;
	}

	dt *= dir;

	glm::rotate(mRotation, dt, glm::vec3(0.f, 0.f, 1.f));

	mMatrix = mMatrix * mRotation;

	rotation += dt;

	//std::cout << "ROTATION: " << rotation << std::endl;
	if (!bOpen && rotation >= 90 || bOpen && rotation <= 0)
	{
		bOpen = !bOpen;
		bActivated = false;

	}
}
