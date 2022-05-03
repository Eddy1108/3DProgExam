#pragma once
#include "Core/VisualObject.h"
#include "Mesh/ObjLoader.h"
#include "Math/BezierCurve.h"
#include "Core/quadtree.h"

class Bomb;

class Enemy : public VisualObject
{
public:
	Enemy(Shader& shader, QuadTre* quadtreRef);

	void init() override;
	void draw() override;

	void move();

	void SpawnBomb();

	std::vector<Bomb*> Bomblist;

	ObjLoader* EnemyModel{ nullptr };
	BezierCurve* mCurve{ nullptr };
	QuadTre* QuadtreRef{ nullptr };

private:

	bool tempDir{ false };

	std::chrono::steady_clock::time_point TimeStart;
};

class Bomb : public VisualObject 
{
public:
	Bomb(Shader& shader, QuadTre* quadRef);

	void init();
	void draw();

	void move();

	ObjLoader* BombModel{ nullptr };
	QuadTre* QuadtreRef{ nullptr };

private:

	float deathZ{ -5 };
};

