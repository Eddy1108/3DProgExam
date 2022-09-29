#ifndef ROLLINGBALL_H
#define ROLLINGBALL_H

#include "octahedronball.h"
#include "trianglesurface.h"
#include "Math/Barycentric.h"

class Line;

class RollingBall : public OctahedronBall
{
public:
    RollingBall(int n);
    ~RollingBall() override;
    void init(GLint matrixUniform) override;
    void draw() override;
    void move(double* dt) override;
    void setSurface(VisualObject* surface);
    glm::vec3 getPosition();
    glm::vec3 findNormal(glm::vec3 v0, glm::vec3 v1, glm::vec3 v2);
protected:
    VisualObject* triangle_surface{nullptr};
private:
    int oldTriangleIndex{-1};
    glm::vec3 oldNormal{0.0, 0.0, 1.0};
    glm::vec3 mVelocity{0.5,0,0}; // Her gir vi den en litt ekstra start fart, for at den skal trille over kanten
    glm::vec3 mAcceleration{0,0,0};
    glm::vec3 mGravity{0,0,-9.80665};

    float mMass {0.0175f}; //kg
    float mRadius {0.0175f}; // m

    float timeSlowDown {1};

    //Debug
    Line* mVelocityLine {nullptr};
    Line* mAccelerationLine {nullptr};
};
#endif // ROLLINGBALL_H
