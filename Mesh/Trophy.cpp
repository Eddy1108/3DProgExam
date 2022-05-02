#include "Trophy.h"

Trophy::Trophy(Shader& shader, float x, float y, float z)
	:VisualObject(shader)
{
	//FRONT
	mVertices.push_back(Vertex{ -0.25f,-0.25f,-0.25f,1,0,0 });
	mVertices.push_back(Vertex{ -0.25f,0.25f,-0.25f,1,0,0 });
	mVertices.push_back(Vertex{ -0.25f,0.25f,0.25f,1,0,0 });

	mVertices.push_back(Vertex{ -0.25f,-0.25f,-0.25f,1,0,0 });
	mVertices.push_back(Vertex{ -0.25f,-0.25f,0.25f,1,0,0 });
	mVertices.push_back(Vertex{ -0.25f,0.25f,0.25f,1,0,0 });

	//RIGHT
	mVertices.push_back(Vertex{ -0.25f,0.25f,-0.25f,1,0,0 });
	mVertices.push_back(Vertex{ -0.25f,0.25f,0.25f,1,0,0 });
	mVertices.push_back(Vertex{ 0.25f,0.25f,0.25f,1,0,0 });

	mVertices.push_back(Vertex{ -0.25f,0.25f,-0.25f,1,0,0 });
	mVertices.push_back(Vertex{ 0.25f,0.25f,-0.25f,1,0,0 });
	mVertices.push_back(Vertex{ 0.25f,0.25f,0.25f,1,0,0 });

	//BACK
	mVertices.push_back(Vertex{ 0.25f,0.25f,-0.25f,1,0,0 });
	mVertices.push_back(Vertex{ 0.25f,0.25f,0.25f,1,0,0 });
	mVertices.push_back(Vertex{ 0.25f,-0.25f,0.25f,1,0,0 });

	mVertices.push_back(Vertex{ 0.25f,0.25f,-0.25f,1,0,0 });
	mVertices.push_back(Vertex{ 0.25f,-0.25f,-0.25f,1,0,0 });
	mVertices.push_back(Vertex{ 0.25f,-0.25f,0.25f,1,0,0 });

	//LEFT
	mVertices.push_back(Vertex{ 0.25f,-0.25f,-0.25f,1,0,0 });
	mVertices.push_back(Vertex{ 0.25f,-0.25f,0.25f,1,0,0 });
	mVertices.push_back(Vertex{ -0.25f,-0.25f,0.25f,1,0,0 });

	mVertices.push_back(Vertex{ 0.25f,-0.25f,-0.25f,1,0,0 });
	mVertices.push_back(Vertex{ -0.25f,-0.25f,-0.25f,1,0,0 });
	mVertices.push_back(Vertex{ -0.25f,-0.25f,0.25f,1,0,0 });

	//TOP FRONT
	mVertices.push_back(Vertex{ -0.25f,-0.25f,0.25f,1,0,0 });
	mVertices.push_back(Vertex{ 0.f,0.f,0.75f,1,1,0 });
	mVertices.push_back(Vertex{ -0.25f,0.25f,0.25f,1,0,0 });

	//TOP RIGHT
	mVertices.push_back(Vertex{ -0.25f,0.25f,0.25f,1,0,0 });
	mVertices.push_back(Vertex{ 0.f,0.f,0.75f,1,1,0 });
	mVertices.push_back(Vertex{ 0.25f,0.25f,0.25f,1,0,0 });

	//TOP BACK
	mVertices.push_back(Vertex{ 0.25f,0.25f,0.25f,1,0,0 });
	mVertices.push_back(Vertex{ 0.f,0.f,0.75f,1,1,0 });
	mVertices.push_back(Vertex{ 0.25f,-0.25f,0.25f,1,0,0 });

	//TOP LEFT
	mVertices.push_back(Vertex{ 0.25f,-0.25f,0.25f,1,0,0 });
	mVertices.push_back(Vertex{ 0.f,0.f,0.75f,1,1,0 });
	mVertices.push_back(Vertex{ -0.25f,-0.25f,0.25f,1,0,0 });

	//BOTTOM FRONT
	mVertices.push_back(Vertex{ -0.25f,-0.25f,-0.25f,1,0,0 });
	mVertices.push_back(Vertex{ 0.f,0.f,-0.75f,1,1,0 });
	mVertices.push_back(Vertex{ -0.25f,0.25f,-0.25f,1,0,0 });

	//BOTTOM RIGHT
	mVertices.push_back(Vertex{ -0.25f,0.25f,-0.25f,1,0,0 });
	mVertices.push_back(Vertex{ 0.f,0.f,-0.75f,1,1,0 });
	mVertices.push_back(Vertex{ 0.25f,0.25f,-0.25f,1,0,0 });

	//BOTTOM BACK
	mVertices.push_back(Vertex{ 0.25f,0.25f,-0.25f,1,0,0 });
	mVertices.push_back(Vertex{ 0.f,0.f,-0.75f,1,1,0 });
	mVertices.push_back(Vertex{ 0.25f,-0.25f,-0.25f,1,0,0 });

	//BOTTOM LEFT
	mVertices.push_back(Vertex{ 0.25f,-0.25f,-0.25f,1,0,0 });
	mVertices.push_back(Vertex{ 0.f,0.f,-0.75f,1,1,0 });
	mVertices.push_back(Vertex{ -0.25f,-0.25f,-0.25f,1,0,0 });

	mMatrix = glm::mat4(1.0f);

	mBShape = new AABB();

	move(x, y, z);
}


Trophy::~Trophy()
{
}

void Trophy::init()
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

void Trophy::draw()
{
	if (bDraw)
	{

		glBindVertexArray(mVAO);
		glUniformMatrix4fv(mShader.mMatrixUniform, 1, GL_FALSE, glm::value_ptr(mMatrix));
		glDrawArrays(GL_TRIANGLES, 0, mVertices.size());
	}
}

bool Trophy::activate(float f)
{
	//delete this;
	bDraw = false;
	std::cout << "Activated!!!!!!!!!" << std::endl;

	return true;
}
