#pragma once
#include <QOpenGLFunctions_4_1_Core>
#include <QMatrix4x4>
#include <vector>
#include <iostream>
#include "glm/glm.hpp"
#include "glm/gtc/type_ptr.hpp"

#include "texture.h"
#include "vertex.h"
#include "shader.h"
#include "Core/CollisionShapes.h"

class RenderWindow;

class VisualObject : public QOpenGLFunctions_4_1_Core {
public:

	VisualObject() = delete;
	VisualObject(Shader& shader);
	~VisualObject();
	virtual void init();
	virtual void initTexture();
	virtual void draw();
	virtual void move(float x, float y, float z);
	virtual void move(float dt) { ; }
	virtual bool activate(float f = 0) { return false; };

	glm::vec2 getPosition2D();
	glm::vec3 getPosition3D();

	void setName(std::string name);
	std::string getName() const;

	glm::mat4 mMatrix;
	Shader& mShader;
	float mx, my, mz; // position

	CollisionShape* mBShape{ nullptr };

	std::vector<Vertex> mVertices;
	std::vector<GLint> mIndices;
protected:


	//void loadTexture(std::string dir);
	//void useTexture();



	GLuint mVAO{ 0 };
	GLuint mVBO{ 0 };
	GLuint mEAB{ 0 }; //Holds the indices (Element Array Buffer - EAB) or EBO


	GLint mMatrixUniform{ 0 };
	
	//QMatrix4x4 mPosition;
	glm::vec3 mPosition;
	glm::mat4 mRotation;
	glm::mat4 mScale;
	glm::vec3 mVelocity;

	std::string mName;

	//Texture* mTexture[2]{ nullptr };
};
