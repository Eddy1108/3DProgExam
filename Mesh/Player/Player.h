#pragma once
#include "Mesh/Player/InteractiveObject.h"
#include "Mesh/ObjLoader.h"


class Player : public InteractiveObject
{
public:
	Player(Shader& shader);

	void init() override;
	void draw() override;
	void move(float x, float y, float z) override;

	void updateFakeCam();
	void CollectTrophy();

	glm::vec3 mForward{ 0.f, 1.f, 0.f };
	glm::vec3 mUp{ 0.f,0.f,1.f };

	
	int WinState{ 0 };	//0 = Playing, 1 = WIN, 2 = LOSE

	ObjLoader* PlayerModel{ nullptr };
	ObjLoader* CameraModel{ nullptr };
	bool bDrawCam{ true };

private:
	float rotate{ 0 };
	float mSpeed = 0.2f;

	int mTrophies{ 0 };
};

