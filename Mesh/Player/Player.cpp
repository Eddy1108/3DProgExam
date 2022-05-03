#include "Player.h"
#include "mesh/Heightmap.h"

#include "glm/gtx/rotate_vector.hpp"
#include "glm/gtx/vector_angle.hpp"

Player::Player(Shader& shader)
	: InteractiveObject(shader)
{
	//Player model from here : https://sketchfab.com/3d-models/among-us-428bb9a3637e458c8336e4a7aefd4e3d
	PlayerModel = new ObjLoader(shader, "../3DProgExam/Assets/models/crew.obj", "../3DProgExam/Assets/tex/pew.bmp");
	CameraModel = new ObjLoader(shader, "../3DProgExam/Assets/models/camera2.obj", "../3DProgExam/Assets/tex/gray.bmp");

	mBShape = new AABB();
}

void Player::init()
{
	initializeOpenGLFunctions();

	PlayerModel->init();
	CameraModel->init();

}

void Player::draw()
{
	PlayerModel->draw();
	
	updateFakeCam();

	if (bDrawCam)
	{
		CameraModel->draw();
	}
}

void Player::move(float x, float y, float z)
{
	rotate = 0;

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

	

	if (SMove) mPosition += mSpeed * -mForward;

	//If colliding with a fence, the player can only go backwards, BUG: Player can walk backwards through fences :)
	if (!bBlocked)
	{
		if (WMove) mPosition += mSpeed * mForward;

		if (AMove) rotate = 3;

		if (DMove) rotate = -3;
	}



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

	//Reset is player is blocked;
	bBlocked = false;
}

void Player::updateFakeCam()
{

	CameraModel->mMatrix[3].x = mCameraOffset.x; CameraModel->mMatrix[3].y = mCameraOffset.y; CameraModel->mMatrix[3].z = mCameraOffset.z;
	CameraModel->mMatrix = glm::rotate(CameraModel->mMatrix, glm::radians(rotate), glm::vec3{ 0.f,0.f,1.f });

}

void Player::CollectTrophy()
{
	++mTrophies;
	std::cout << "Player Trophies: " << mTrophies << std::endl;

	if (mTrophies == 10)
	{
		WinState = 1;
	}
}

bool Player::activate(float f)
{
	if (!bStunned)
	{
		bStunned = true;
		TimeStart = std::chrono::steady_clock::now();
		std::cout << "PLAYER STUNNED" << std::endl;

		return true;
	}
	else
		return false;
}
