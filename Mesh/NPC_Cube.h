#pragma once
#include "Core/VisualObject.h"
#include "mesh/Graph.h"

class NPC_Cube : public VisualObject
{
public:

	NPC_Cube(Shader& shader);
	NPC_Cube(Shader& shader, int func);
	~NPC_Cube();

	void init() override;
	void draw() override;
	void move(float x, float y, float z) override;
	
	bool activate(float f) override;

	float func(float x);
	float func2(float x);
	float func3(float x, float y);

private:
	float mx{ 0 };
	float my{ 0 };
	float mz{ 0 };

	int funcUse{ 0 };

	bool dirRight{ true };
};

