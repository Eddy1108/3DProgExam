#include "PointCloud.h"

PointCloud::PointCloud(Shader& shader) : VisualObject{shader}
{
	mName = "PointCloud";
}

PointCloud::~PointCloud()
{
}

void PointCloud::init()
{
	initializeOpenGLFunctions();

	//Initialize Geometry
	std::ifstream file;

	//Open file
	file.open("Surface/AnkerskogenFixed.txt");
	//file.open("Surface/test.txt");

	if (!file)
	{
		std::cout << "\n\nERROR SURFACE FILE NOT FOUND\n\n";
			return;
	}

	long double x{ 0 };
	long double y{ 0 };
	long double z{ 0 };
	long double size{ 0 };
	file >> size;
	std::cout << "\nSIZE: " << size << std::endl;

	Vertex vertex;

	for (long double i = 0; i < size; i+= 100)
	{
		file >> x >> y >> z;
		//std::cout << "\nCoords: " << x << ", " << y << ", " << z << std::endl;
		vertex.m_xyz[0] = (x - mOffsetX) * mScaleMultiplyX;
		vertex.m_xyz[1] = (y - mOffsetY) * mScaleMultiplyY;
		vertex.m_xyz[2] = z * mScaleMultiplyZ;

		//std::cout << "\nNew Coords: " << vertex.m_xyz[0] << ", " << vertex.m_xyz[1] << ", " << vertex.m_xyz[2] << std::endl;

		mVertices.push_back(vertex);
	}
	file.close();

	glGenVertexArrays(1, &mVAO);
	glBindVertexArray(mVAO);

	glGenBuffers(1, &mVBO);
	glBindBuffer(GL_ARRAY_BUFFER, mVBO);

	glBufferData(GL_ARRAY_BUFFER, mVertices.size() * sizeof(Vertex), mVertices.data(), GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, mVBO);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)0);
	glEnableVertexAttribArray(0);

	// 2nd attribute buffer : colors
// Same parameter list as above but attribute and offset is adjusted accoringly
	glVertexAttribPointer(
		1,
		3,
		GL_FLOAT,
		GL_FALSE,
		sizeof(Vertex),
		reinterpret_cast<GLvoid*>(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	glBindVertexArray(0);
}

void PointCloud::draw()
{
	glBindVertexArray(mVAO);
	glUniformMatrix4fv(mMatrixUniform, 1, GL_FALSE, glm::value_ptr(mMatrix));
	glDrawArrays(GL_POINTS, 0, mVertices.size());
}
