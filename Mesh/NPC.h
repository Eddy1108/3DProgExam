#pragma once
#include "Core/VisualObject.h"
#include "Mesh/ObjLoader.h"
#include <chrono>

class Heightmap;

class NPC : public VisualObject
{
public:
	NPC(Shader& shader);

	void init() override;
	void draw() override;

	void move();

	bool CollectTrophy();

	//Activate STUN
	bool activate(float f = 0) override;

	glm::vec3 mForward{ 0.f, 1.f, 0.f };
	glm::vec3 mUp{ 0.f,0.f,1.f };

	Heightmap* mHeightmap;
	ObjLoader* NPCModel{ nullptr };

	std::vector<VisualObject*> mTrophyList;


private:

	bool bStunned{ false };
	float mSpeed = 0.25f;
	int mTrophies{ 0 };

	std::chrono::steady_clock::time_point TimeStart;
	std::chrono::steady_clock::time_point TimeEnd;

};

