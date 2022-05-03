#pragma once
#include "Core/VisualObject.h"
#include "Mesh/ObjLoader.h"

class Fence : public VisualObject
{
public:
	Fence(Shader& shader, bool useX);

	void init() override;
	void draw() override;

	void move();

	ObjLoader* FenceModel{ nullptr };

private:
	bool useX{ false };
};

