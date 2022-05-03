#include "Fence.h"

Fence::Fence(Shader& shader, bool useX)
	:VisualObject(shader), useX{useX}
{
	//change model based on which orientation is wanted, should probably have done this in mMatrix instead oops
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
	move();	//static, only need to move it once.
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
