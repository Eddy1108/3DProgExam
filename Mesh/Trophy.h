#pragma once
#include "Core/VisualObject.h"
#include "glm/glm.hpp"
#include <vector>

class Trophy : public VisualObject
{
public:

	Trophy(Shader& shader, float x, float y, float z);
	~Trophy();



	void init() override;
	void draw() override;
	bool activate(float f = 0) override;

private:
	std::vector<Trophy*> mCollection;
	std::vector<glm::vec2> mPoints;

	bool bDraw{ true };

};

