#include "Fence.h"

Fence::Fence(Shader& shader, bool useX)
	:VisualObject(shader), useX{useX}
{
	//ObjLoader(shader, "../3DProgExam/Assets/models/crew.obj", "../3DProgExam/Assets/tex/pew.bmp");
	
	if (useX)
		FenceModel = new ObjLoader(shader, "../3DProgExam/Assets/models/fenceX.obj", "");
	else
		FenceModel = new ObjLoader(shader, "../3DProgExam/Assets/models/fenceY.obj", "");
	
	mBShape = new AABB();
	dynamic_cast<AABB*>(mBShape)->mExtent = glm::vec3(0.1f);

	mMatrix = glm::mat4(1.0f);
}

void Fence::init()
{
	FenceModel->init();
	move();
}

void Fence::draw()
{
	FenceModel->draw();
}

void Fence::move()
{
	mMatrix[3].x = mPosition.x;
	mMatrix[3].y = mPosition.y;
	mMatrix[3].z = mPosition.z;

	FenceModel->mMatrix = mMatrix;

	if (mBShape)
	{
		mBShape->mPosition = mPosition;
	}
}
