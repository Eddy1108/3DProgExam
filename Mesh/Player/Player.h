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

	glm::vec3 mForward{ 0.f, 1.f, 0.f };
	glm::vec3 mUp{ 0.f,0.f,1.f };

	float mSpeed = 0.2f;


	ObjLoader* PlayerModel{ nullptr };
	ObjLoader* CameraModel{ nullptr };
	bool bDrawCam{ true };

private:
	float rotate{ 0 };
};

