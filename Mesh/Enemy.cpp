#include "Enemy.h"

#include "Mesh/NPC.h"
#include "Mesh/Player/Player.h"

#include <chrono>

Enemy::Enemy(Shader& shader, QuadTre* quadtreRef)
	:VisualObject(shader), QuadtreRef{quadtreRef}
{

	EnemyModel = new ObjLoader(shader, "../3DProgExam/Assets/models/enemy2.obj", "../3DProgExam/Assets/tex/white.bmp");
}

void Enemy::init()
{
	EnemyModel->init();

	mPosition = glm::vec3(-3.f, -3.f, 7.f);
	mMatrix = glm::mat4(1.f);

	TimeStart = std::chrono::steady_clock::now();
}

void Enemy::draw()
{
	if (bPlay)
	{

		move();

		//Calculate 2 seconds passing and then spawn a bomb
		auto TimeEnd = std::chrono::steady_clock::now();
		long long test = std::chrono::duration_cast<std::chrono::seconds>(TimeEnd - TimeStart).count();
		if (test > 2.f)
		{
			std::cout << "Bomb Spawned" << std::endl;
			TimeStart = std::chrono::steady_clock::now();

			SpawnBomb();
		}

	}
	EnemyModel->draw();

	for (int i = 0; i < Bomblist.size(); i++)
	{
		Bomblist[i]->draw();
		Bomblist[i]->bPlay = bPlay;
	}
}

void Enemy::move()
{
	float dir{ .3f };

	//Bezier code is being weird so this will be use for now
	if (mPosition.x > 30.f)
	{
		tempDir = false;
	}
	else if (mPosition.x < -30.f)
	{
		tempDir = true;
	}

	if (tempDir)
	{
		mPosition.x += dir;
		mPosition.y += dir;
	}
	else
	{
		mPosition.x -= dir;
		mPosition.y -= dir;
	}

	mMatrix[3].x = mPosition.x;
	mMatrix[3].y = mPosition.y;
	mMatrix[3].z = mPosition.z;

	EnemyModel->mMatrix = mMatrix;
}

void Enemy::SpawnBomb()
{
	Bomb* temp;
	Bomblist.push_back(temp = new Bomb(mShader, QuadtreRef));
	QuadtreRef->insert(temp, temp->mBShape);
	temp->setName("Bomb" + std::to_string(Bomblist.size()));
	temp->init();
	temp->mPosition = mPosition;
}





Bomb::Bomb(Shader& shader, QuadTre* quadRef)
	:VisualObject(shader), QuadtreRef{ quadRef }
{
	mBShape = new AABB();
	BombModel = new ObjLoader(shader, "../3DProgExam/Assets/models/bomb.obj", "../3DProgExam/Assets/tex/white.bmp");

	mMatrix = glm::mat4{ 1.f };
	mPosition = glm::vec3{ 0.f };
}

void Bomb::init()
{
	BombModel->init();
}

void Bomb::draw()
{
	if (bPlay)
		move();

	BombModel->draw();

	//Check Collision?
	QuadTre* subtre = QuadtreRef->find(glm::vec2{mPosition.x, mPosition.y});
	for (auto it = subtre->m_Objects.begin(); it < subtre->m_Objects.end(); it++)
	{
		//Check for the player
		if ((*it)->mBShape && dynamic_cast<Player*>(*it) != nullptr && mBShape->overlap((*it)->mBShape))
		{

			if ((*it)->activate())
			{
				std::cout << "PLAYER STUNNED" << std::endl;
			}


		}

		if ((*it)->mBShape && dynamic_cast<NPC*>(*it) != nullptr && mBShape->overlap((*it)->mBShape))
		{
			std::cout << "NPC FOUND" << std::endl;

			//if ((*it)->activate())
			//{
			//	dynamic_cast<Player*>((*it))->CollectTrophy();
			//}

		}
	}

}

void Bomb::move()
{
	//Deleting them does weird stuff so we'll just move them away for now
	if (mPosition.z < deathZ)
	{
		mPosition = glm::vec3{ 50.f, 50.f, mPosition.z  };
	}
	else
		mPosition.z -= 0.1f;

	mMatrix[3].x = mPosition.x;
	mMatrix[3].y = mPosition.y;
	mMatrix[3].z = mPosition.z;

	if (mBShape)
	{
		mBShape->mPosition = mPosition;
	}

	BombModel->mMatrix = mMatrix;
}
