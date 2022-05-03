#include "NPC.h"
#include "Mesh/Heightmap.h"

NPC::NPC(Shader& shader)
	:VisualObject(shader)
{
	NPCModel = new ObjLoader(shader, "../3DProgExam/Assets/models/crew.obj", "../3DProgExam/Assets/tex/white.bmp");

	mBShape = new AABB();
}

void NPC::init()
{
	NPCModel->init();

	mPosition = glm::vec3(0.f, 1.f, 2.f);
	mMatrix = glm::mat4(1.f);
}

void NPC::draw()
{
	if (bPlay)
		move();
	
	
	NPCModel->draw();
}

void NPC::move()
{
	if (bStunned)
	{
		TimeEnd = std::chrono::steady_clock::now();

		auto test = std::chrono::duration_cast<std::chrono::seconds>(TimeEnd - TimeStart).count();
		//std::cout << "STUN Start: " << test << std::endl;

		if (test > 1.f)
		{
			bStunned = false;
		}
		else
			return;
	}

	mPosition += mSpeed * mForward;

	if (mHeightmap && mHeightmap->IsInside(mPosition))
	{
		mPosition.z = mHeightmap->getHeight(mPosition);
	}

	mMatrix[3].x = mPosition.x;
	mMatrix[3].y = mPosition.y;
	mMatrix[3].z = mPosition.z;

	//If there are tropies left, make forward vector to next one
	if (mTrophies < mTrophyList.size())
	{
		mForward = glm::normalize(mTrophyList[mTrophies]->mPosition - mPosition);
	}
	else
		mForward = glm::vec3{ 0.f };	//else stand still
	
	//Update collision shape location
	if (mBShape)
	{
		mBShape->mPosition = mPosition;
		mBShape->mPosition.z += .2f;
	}
	NPCModel->mMatrix = mMatrix;
}

bool NPC::CollectTrophy()
{
	++mTrophies;
	std::cout << "NPC Trophies: " << mTrophies << std::endl;

	if (mTrophies >= 10)
	{
		return true;
	}

	return false;
}

bool NPC::activate(float f)
{
	if (!bStunned)
	{
		bStunned = true;
		TimeStart = std::chrono::steady_clock::now();
		std::cout << "NPC STUNNED" << std::endl;

		return true;
	}
	else
		return false;
}
