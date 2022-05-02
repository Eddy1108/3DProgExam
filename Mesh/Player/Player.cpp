#include "Player.h"
#include "mesh/Heightmap.h"

//#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtx/rotate_vector.hpp"
#include "glm/gtx/vector_angle.hpp"

Player::Player(Shader& shader)
	: InteractiveObject(shader)
{
	PlayerModel = new ObjLoader(shader, "../3DProgExam/Assets/models/crew.obj", "../3DProgExam/Assets/tex/pew.bmp");
	CameraModel = new ObjLoader(shader, "../3DProgExam/Assets/models/camera2.obj", "../3DProgExam/Assets/tex/gray.bmp");

	mBShape = new AABB();
}

void Player::init()
{
	initializeOpenGLFunctions();

	mMatrix = glm::mat4(1.0f);

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

	//EBO
	glGenBuffers(1, &mEAB);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mEAB);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, mIndices.size() * sizeof(GLuint), mIndices.data(), GL_STATIC_DRAW);


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

	// 3rd attribute buffer : UV
	glVertexAttribPointer(
		2,
		2,
		GL_FLOAT,
		GL_FALSE,
		sizeof(Vertex),
		reinterpret_cast<GLvoid*>(6 * sizeof(GLfloat)));
	glEnableVertexAttribArray(2);

	glBindVertexArray(0);

	PlayerModel->init();
	CameraModel->init();

}

void Player::draw()
{
	PlayerModel->draw();
	

	if (bDrawCam)
	{
		updateFakeCam();
		CameraModel->draw();
	}

}

void Player::move(float x, float y, float z)
{
	rotate = 0;

	if (WMove) mPosition += mSpeed * mForward;

	if (SMove) mPosition += mSpeed * -mForward;

	if (AMove) rotate = 3;

	if (DMove) rotate = -3;

	glm::vec3 pos(mPosition.x, mPosition.y, mPosition.z);

	if (mHeightmap && mHeightmap->IsInside(pos))
	{
		//mz = mHeightmap->getHeight(glm::vec3(mx, my, mz));
		mPosition.z = mHeightmap->getHeight(pos);
	}

	


	mMatrix = glm::rotate(mMatrix, glm::radians(rotate), glm::vec3{ 0.f,0.f,1.f });

	mMatrix[3].x = mPosition.x;
	mMatrix[3].y = mPosition.y;
	mMatrix[3].z = mPosition.z;
	

	mForward = glm::rotate(mForward, glm::radians(rotate), mUp);














	//Final stuff dont mind this
	if (mBShape)
	{
		mBShape->mPosition = mPosition;
	}
	PlayerModel->mMatrix = mMatrix;

	mCameraOffset = glm::vec3{ mPosition.x + -mForward.x * 10.f, mPosition.y + -mForward.y * 10.f, mPosition.z + 10.f };
}

void Player::updateFakeCam()
{

	CameraModel->mMatrix[3].x = mCameraOffset.x; CameraModel->mMatrix[3].y = mCameraOffset.y; CameraModel->mMatrix[3].z = mCameraOffset.z;
	CameraModel->mMatrix = glm::rotate(CameraModel->mMatrix, glm::radians(rotate), glm::vec3{ 0.f,0.f,1.f });

}
