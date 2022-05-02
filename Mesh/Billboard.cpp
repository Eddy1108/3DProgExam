#include "Billboard.h"

Billboard::Billboard(Shader& shader, Camera* cam)
	:VisualObject(shader)
{
	mCam = cam;

	mVertices.push_back(Vertex(-1.f, -1.f, 0.f, 1.f, 0.f, 0.f, 0.f, 0.f)); //A
	mVertices.push_back(Vertex(-1.f, 1.f, 0.f, 0.f, 1.f, 0.f, 0.f, 1.f)); //C
	mVertices.push_back(Vertex(1.f, 1.f, 0.f, 0.f, 0.f, 1.f, 1.f, 1.f)); //D

	mVertices.push_back(Vertex(-1.f, -1.f, 0.f, 1.f, 0.f, 0.f, 0.f, 0.f)); //A
	mVertices.push_back(Vertex(1.f, -1.f, 0.f, 0.f, 1.f, 0.f, 1.f, 0.f)); //B
	mVertices.push_back(Vertex(1.f, 1.f, 0.f, 0.f, 0.f, 1.f, 1.f, 1.f)); //D

	mMatrix = glm::mat4(1.0f);
	move(0.f, 0.f, 10.f);

	
}

Billboard::~Billboard()
{
}

void Billboard::init()
{
	VisualObject::initTexture();

	mTexture = new Texture("../3DProgExam/Assets/tex/jacky.bmp");
}

void Billboard::draw()
{
	//RotateToCamMatrix();
	RotateToCamDirect();

	//Not needed but to overwrite other textures in this slot we must do this each draw call
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, mTexture->id());

	VisualObject::draw();

}

void Billboard::RotateToCamMatrix()
{
	billView = glm::inverse(mCam->mVMatrix);

	glm::vec4 leftVectorX = billView[0];
	glm::vec4 upVectorY = billView[1];
	glm::vec4 forwardVectorZ = billView[2];

	mMatrix[0] = leftVectorX;
	mMatrix[1] = upVectorY;
	mMatrix[2] = forwardVectorZ;

}

void Billboard::RotateToCamDirect()
{
	billView = glm::lookAt(mPosition, mCam->mPosition, mCam->mUp);

	billView = glm::inverse(billView);

	glm::vec4 leftVectorX = billView[0];
	glm::vec4 upVectorY = billView[1];
	glm::vec4 forwardVectorZ = billView[2];

	mMatrix[0] = leftVectorX;
	mMatrix[1] = upVectorY;
	mMatrix[2] = forwardVectorZ;
}
