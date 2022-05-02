#include "NPC_Cube.h"
#include "logger.h"

NPC_Cube::NPC_Cube(Shader& shader) 
	:VisualObject(shader)
{
	float a = 0.25f;
	float b = -0.25f;

	//front
	mVertices.push_back(Vertex{ b, b, b,  0,0,0 }); // A
	mVertices.push_back(Vertex{ a, b, b,  1,0,0 }); // B
	mVertices.push_back(Vertex{ b, a, b,  0,0,1 }); // C

	mVertices.push_back(Vertex{ b, a, b,  0,0,1 }); // C
	mVertices.push_back(Vertex{ a, b, b,  1,0,0 }); // B
	mVertices.push_back(Vertex{ a, a, b,  1,0,1 }); // D

	//right
	mVertices.push_back(Vertex{ a, b, b,  1,0,0 }); // B
	mVertices.push_back(Vertex{ a, a, b,  1,0,1 }); // D
	mVertices.push_back(Vertex{ a, b, a,  0,1,1 }); // H

	mVertices.push_back(Vertex{ a, b, a,  0,1,1 }); // H
	mVertices.push_back(Vertex{ a, a, b,  1,0,1 }); // D
	mVertices.push_back(Vertex{ a, a, a,  1,1,1 }); // F

	//back
	mVertices.push_back(Vertex{ b, b, a,  1,1,0 }); // G
	mVertices.push_back(Vertex{ a, b, a,  0,1,1 }); //H
	mVertices.push_back(Vertex{ b, a, a,  0,1,0 }); // E

	mVertices.push_back(Vertex{ b, a, a,  0,1,0 }); // E
	mVertices.push_back(Vertex{ a, b, a,  0,1,1 }); // H
	mVertices.push_back(Vertex{ a, a, a,  1,1,1 }); // F

	//left
	mVertices.push_back(Vertex{ b, b, b,  0,0,0 }); //A
	mVertices.push_back(Vertex{ b, a, b,  0,0,1 }); //C
	mVertices.push_back(Vertex{ b, b, a,  1,1,0 }); //G

	mVertices.push_back(Vertex{ b, b, a,  1,1,0 }); //G
	mVertices.push_back(Vertex{ b, a, b,  0,0,1 }); //C
	mVertices.push_back(Vertex{ b, a, a,  0,1,0 }); //E


	//top
	mVertices.push_back(Vertex{ b, a, b,  0,0,1 }); //C
	mVertices.push_back(Vertex{ a, a, b,  1,0,1 }); //D
	mVertices.push_back(Vertex{ b, a, a,  0,1,0 }); //E

	mVertices.push_back(Vertex{ b, a, a,  0,1,0 }); //E
	mVertices.push_back(Vertex{ a, a, b,  1,0,1 }); //D
	mVertices.push_back(Vertex{ a, a, a,  1,1,1 }); //F

	//bottom
	mVertices.push_back(Vertex{ b, b, b,  0,0,0 }); // A
	mVertices.push_back(Vertex{ a, b, b,  1,0,0 }); // B
	mVertices.push_back(Vertex{ b, b, a,  1,1,0 }); // G

	mVertices.push_back(Vertex{ b, b, a,  1,1,0 }); // G
	mVertices.push_back(Vertex{ a, b, b,  1,0,0 }); // B
	mVertices.push_back(Vertex{ a, b, a,  0,1,1 }); // H

	mMatrix = glm::mat4(1.0f);
}

NPC_Cube::NPC_Cube(Shader& shader, int func)
	: VisualObject(shader), funcUse{func}
{
	float a = 0.25f;
	float b = -0.25f;

	//front
	mVertices.push_back(Vertex{ b, b, b,  0,0,0 }); // A
	mVertices.push_back(Vertex{ a, b, b,  1,0,0 }); // B
	mVertices.push_back(Vertex{ b, a, b,  0,0,1 }); // C

	mVertices.push_back(Vertex{ b, a, b,  0,0,1 }); // C
	mVertices.push_back(Vertex{ a, b, b,  1,0,0 }); // B
	mVertices.push_back(Vertex{ a, a, b,  1,0,1 }); // D

	//right
	mVertices.push_back(Vertex{ a, b, b,  1,0,0 }); // B
	mVertices.push_back(Vertex{ a, a, b,  1,0,1 }); // D
	mVertices.push_back(Vertex{ a, b, a,  0,1,1 }); // H

	mVertices.push_back(Vertex{ a, b, a,  0,1,1 }); // H
	mVertices.push_back(Vertex{ a, a, b,  1,0,1 }); // D
	mVertices.push_back(Vertex{ a, a, a,  1,1,1 }); // F

	//back
	mVertices.push_back(Vertex{ b, b, a,  1,1,0 }); // G
	mVertices.push_back(Vertex{ a, b, a,  0,1,1 }); //H
	mVertices.push_back(Vertex{ b, a, a,  0,1,0 }); // E

	mVertices.push_back(Vertex{ b, a, a,  0,1,0 }); // E
	mVertices.push_back(Vertex{ a, b, a,  0,1,1 }); // H
	mVertices.push_back(Vertex{ a, a, a,  1,1,1 }); // F

	//left
	mVertices.push_back(Vertex{ b, b, b,  0,0,0 }); //A
	mVertices.push_back(Vertex{ b, a, b,  0,0,1 }); //C
	mVertices.push_back(Vertex{ b, b, a,  1,1,0 }); //G

	mVertices.push_back(Vertex{ b, b, a,  1,1,0 }); //G
	mVertices.push_back(Vertex{ b, a, b,  0,0,1 }); //C
	mVertices.push_back(Vertex{ b, a, a,  0,1,0 }); //E


	//top
	mVertices.push_back(Vertex{ b, a, b,  0,0,1 }); //C
	mVertices.push_back(Vertex{ a, a, b,  1,0,1 }); //D
	mVertices.push_back(Vertex{ b, a, a,  0,1,0 }); //E

	mVertices.push_back(Vertex{ b, a, a,  0,1,0 }); //E
	mVertices.push_back(Vertex{ a, a, b,  1,0,1 }); //D
	mVertices.push_back(Vertex{ a, a, a,  1,1,1 }); //F

	//bottom
	mVertices.push_back(Vertex{ b, b, b,  0,0,0 }); // A
	mVertices.push_back(Vertex{ a, b, b,  1,0,0 }); // B
	mVertices.push_back(Vertex{ b, b, a,  1,1,0 }); // G

	mVertices.push_back(Vertex{ b, b, a,  1,1,0 }); // G
	mVertices.push_back(Vertex{ a, b, b,  1,0,0 }); // B
	mVertices.push_back(Vertex{ a, b, a,  0,1,1 }); // H

	mMatrix = glm::mat4(1.0f);
}

NPC_Cube::~NPC_Cube()
{
}

void NPC_Cube::init()
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

	//mMatrix.translate(1.f, 1.f, 1.f);
}

void NPC_Cube::draw()
{

	glBindVertexArray(mVAO);
	glUniformMatrix4fv(mShader.mMatrixUniform, 1, GL_FALSE, glm::value_ptr(mMatrix));
	glDrawArrays(GL_TRIANGLES, 0, mVertices.size());

	move(0.1f, 0, 0);
}

void NPC_Cube::move(float x, float y, float z)
{

	mx += x;

	if (mx > 20.f && dirRight)
	{
		dirRight = false;
	}

	if (mx < -10.f && !dirRight)
	{
		dirRight = true;
	}

	if (!dirRight)
	{
		mx -= x * 2;
	}
	
	//my += y;
	//mz += z;
	float temp;

	switch (funcUse)
	{
	case 0:
		temp = func(mx) - my;
		my = func(mx);
		break;
	case 1:
		temp = func2(mx) - my;
		my = func2(mx);
		break;
	default:
		temp = 0.f;
		my = 0.f;
		break;
	}



	float temp2 = 0; //func3(mx, my) - mz;
	//mz = func3(mx, my);

	if (dirRight)
	{
		//QVector4D pos{ mx,my,mz,1.0f };
		//mPosition.setColumn(3, pos);
		//mMatrix = mPosition;
		move(mx, my, mz);
	}
	else 
	{
		//QVector4D pos{ mx,my,mz,1.0f };
		//mPosition.setColumn(3, pos);
		//mMatrix = mPosition;
		move(mx, my, mz);
	}
	
}

bool NPC_Cube::activate(float f)
{
	if (funcUse == 1)
		funcUse = 0;
	else 
		funcUse++;

	std::string test = std::to_string(funcUse);

	Logger* mLogger = Logger::getInstance();
	mLogger->logText(test);

	return true;
}


float NPC_Cube::func(float x)
{
	return ((-1027.f / 155316.f) * pow(x, 2) + (16075.f / 155316.f) * x + (98963.f / 25886.f));
}

float NPC_Cube::func2(float x)
{
	return ((23.f / 252.f) * pow(x, 3) + (-31.f / 63.f) * pow(x, 2) + (-55.f / 84.f) * x + (41.f / 14.f));
}

float NPC_Cube::func3(float x, float y)
{
	return sin(x + y);
}