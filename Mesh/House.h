#pragma once
#include "Core/VisualObject.h"

class House : public VisualObject
{
public:

	House(Shader& shader, bool bRoof = true);
	~House();

	void init() override;
	void draw() override;
	void move(float x, float y, float z) override;

private:
	float mx{ 0 };
	float my{ 0 };
	float mz{ 0 };
};

