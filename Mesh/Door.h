#pragma once
#include "Core/VisualObject.h"

class Door : public VisualObject
{
public:

	Door(Shader& shader);
	~Door();

	void init() override;
	void draw() override;
	void move(float x, float y, float z) override;
	bool activate(float f = 0) override;
	void rotateDoor(float dt);

private:
	float mx{ 0 };
	float my{ 0 };
	float mz{ 0 };

	float rotation{ 0 };

	bool bActivated{ false };
	bool bOpen{ false };

};

