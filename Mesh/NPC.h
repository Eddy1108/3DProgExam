#pragma once
#include "Core/VisualObject.h"
#include "Mesh/ObjLoader.h"
#

class Heightmap;

class NPC : public VisualObject
{
public:
	NPC(Shader& shader);

	void init() override;
	void draw() override;

	void move();

	bool CollectTrophy();

	glm::vec3 mForward{ 0.f, 1.f, 0.f };
	glm::vec3 mUp{ 0.f,0.f,1.f };

	Heightmap* mHeightmap;
	ObjLoader* NPCModel{ nullptr };

	std::vector<VisualObject*> mTrophyList;

private:

	float mSpeed = 0.1f;
	int mTrophies{ 0 };
};

