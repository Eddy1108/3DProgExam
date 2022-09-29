#pragma once

#include <math.h>
#include <iostream>

#include <vector>

#include "Core/VisualObject.h"

class PointCloud : public VisualObject
{
public:

	PointCloud(Shader& shader);
	~PointCloud();

	void init() override;
	void draw() override;

	long double mScaleMultiplyX{ 0.1f };
	long double mScaleMultiplyY{ 0.1f };
	long double mScaleMultiplyZ{ 0.001f };

	long double mOffsetX{ 612500 };
	long double mOffsetY{ 6742790 };

	//long double mOffsetX{ 0 };
	//long double mOffsetY{ 0 };
};

