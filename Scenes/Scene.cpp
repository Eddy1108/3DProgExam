#include "Scene.h"

Scene::Scene(std::unordered_map<std::string, Shader*> shaders)
	: mShaderPrograms{shaders}
{
}

Scene::~Scene()
{
}

void Scene::init()
{
    if (mSkybox)
    {
        mSkybox->init();
    }
    

    for (auto it = mMap.begin(); it != mMap.end(); it++)
    {
        (*it).second->init();
    }

    for (auto it = mMap2.begin(); it != mMap2.end(); it++)
    {
        (*it).second->init();
    }

    for (auto it = mMap3.begin(); it != mMap3.end(); it++)
    {
        (*it).second->init();
    }
    for (auto it = mMap4.begin(); it != mMap4.end(); it++)
    {
        (*it).second->init();
    }
}

void Scene::draw()
{
    initializeOpenGLFunctions();
 
    mCamera->perspective(60, (float)16 / (float)9, 0.1f, 100.0);

    //Draw Plain Objects
    if (mMap.size() > 0)
    {

        GLint tempPMatrix = mShaderPrograms["plain"]->mPMatrixUniform;
        GLint tempVMatrix = mShaderPrograms["plain"]->mVMatrixUniform;
        glUseProgram(mShaderPrograms["plain"]->getProgram());


        mCamera->init(tempPMatrix, tempVMatrix);
        mCamera->update();

        //Move Player
        mMap["mia"]->move(0.1f, 0.1f, 0.1f);

        //Move Camera
        mCamera->lookAt(
            glm::vec3{ mMap["mia"]->mx, mMap["mia"]->my - 10, mMap["mia"]->mz + 10 },
            glm::vec3{ mMap["mia"]->mx, mMap["mia"]->my ,mMap["mia"]->mz },
            glm::vec3{ 0.0f, 0.0f, 1.0f }
        );



        for (auto it = mMap.begin(); it != mMap.end(); it++)
        {
            (*it).second->draw();
        }
    }

    //Draw Texture Objects
    if (mMap2.size() > 0)
    {
        GLint tempPMatrix = mShaderPrograms["textured"]->mPMatrixUniform;
        GLint tempVMatrix = mShaderPrograms["textured"]->mVMatrixUniform;
        glUseProgram(mShaderPrograms["textured"]->getProgram());

        glUniform1i(mShaderPrograms["textured"]->mTextureUniform, 1);

        mCamera->init(tempPMatrix, tempVMatrix);
        mCamera->update();


        mCamera->lookAt(
            glm::vec3{ mMap["mia"]->mx, mMap["mia"]->my - 10, mMap["mia"]->mz + 10 },
            glm::vec3{ mMap["mia"]->mx, mMap["mia"]->my ,mMap["mia"]->mz },
            glm::vec3{ 0.0f, 0.0f, 1.0f }
        );

        for (auto it = mMap2.begin(); it != mMap2.end(); it++)
        {
            (*it).second->draw();
        }
    }

    //Phong Objects
    if (mMap3.size() > 0)
    {
        GLint tempPMatrix = mShaderPrograms["phong"]->mPMatrixUniform;
        GLint tempVMatrix = mShaderPrograms["phong"]->mVMatrixUniform;
        glUseProgram(mShaderPrograms["phong"]->getProgram());

        glUniform1i(mShaderPrograms["phong"]->mTextureUniform, 1);

        glUniform3f(mShaderPrograms["phong"]->mCameraPositionUniform, mCamera->mPosition.x, mCamera->mPosition.y, mCamera->mPosition.z);
        glUniform3f(mShaderPrograms["phong"]->mLightPositionUniform, mLight->getPosition3D().x, mLight->getPosition3D().y, mLight->getPosition3D().z);

        mCamera->init(tempPMatrix, tempVMatrix);
        mCamera->update();



        mCamera->lookAt(
            glm::vec3{ mMap["mia"]->mx, mMap["mia"]->my - 10, mMap["mia"]->mz + 10 },
            glm::vec3{ mMap["mia"]->mx, mMap["mia"]->my ,mMap["mia"]->mz },
            glm::vec3{ 0.0f, 0.0f, 1.0f }
          );
        

        for (auto it = mMap3.begin(); it != mMap3.end(); it++)
        {
            (*it).second->draw();
        }
    }

    //Billboard Objects
    if (mMap4.size() > 0)
    {

    }

        //Draw Skybox
    if (mSkybox)
    {
        //glDisable(GL_CULL_FACE);
        glDepthFunc(GL_LEQUAL);

        glUseProgram(mShaderPrograms["skybox"]->getProgram());

       
        GLint tempPMatrix = mShaderPrograms["skybox"]->mPMatrixUniform;
        GLint tempVMatrix = mShaderPrograms["skybox"]->mVMatrixUniform;

        glm::mat4 view = glm::mat4(glm::mat3(mCamera->mVMatrix));

        glm::mat4 rotMatrix = glm::mat4(1.0f);
        rotMatrix = glm::rotate(glm::radians(90.f), glm::vec3(1.0f, 0.0f, 0.0f));

        glUniformMatrix4fv(glGetUniformLocation(mShaderPrograms["skybox"]->getProgram(), "rotMatrix"), 1, GL_FALSE, glm::value_ptr(rotMatrix));
        glUniformMatrix4fv(tempVMatrix, 1, GL_FALSE, glm::value_ptr(view));
        glUniformMatrix4fv(tempPMatrix, 1, GL_FALSE, glm::value_ptr(mCamera->mPMatrix));

        mSkybox->draw();

        glDepthFunc(GL_LESS);
    }

    checkCollision();

    drawCollision();
}

void Scene::drawCollision()
{
    for (auto it = mMap.begin(); it != mMap.end(); it++)
    {
        if ((*it).second->mBShape)
        {
            if ((*it).second->mBShape->mType == CollisionShape::Type::AABB)
            {

            DrawAABB(
                dynamic_cast<AABB*>((*it).second->mBShape)->mPosition,
                dynamic_cast<AABB*>((*it).second->mBShape)->mExtent
              );

            };
        }
    }

    DrawAABB(mQuadTre.m_ne->mShape->mPosition, mQuadTre.m_ne->mShape->mExtent);
    DrawAABB(mQuadTre.m_nw->mShape->mPosition, mQuadTre.m_nw->mShape->mExtent);
    DrawAABB(mQuadTre.m_se->mShape->mPosition, mQuadTre.m_se->mShape->mExtent);
    DrawAABB(mQuadTre.m_sw->mShape->mPosition, mQuadTre.m_sw->mShape->mExtent);
}

void Scene::checkCollision()
{
    glm::vec2 playerPos = mMap["mia"]->getPosition2D();
    auto subtre = mQuadTre.find(playerPos);
    for (auto it = subtre->m_Objects.begin(); it < subtre->m_Objects.end(); it++)
    {
        if ((*it)->mBShape && (*it)->getName() == "Trophy" && mMap["mia"]->mBShape->overlap((*it)->mBShape))
        {
            (*it)->activate();
        }

        //std::cout << "POS: "<< (*it)->getName() << "     :" << (*it)->getPosition2D().x << ", " << (*it)->getPosition2D().y << std::endl;
        
    }

    //std::cout << "A: " << subtre->m_a.first << ", " << subtre->m_a.second << "   B: " << subtre->m_c.first << ", " << subtre->m_c.second << std::endl;
    //std::cout << subtre->m_Objects.size() << std::endl;

}

void Scene::DrawAABB(glm::vec3 position, glm::vec3 extent)
{
    static uint32_t VAO{};
    if (VAO == 0)
    {
        std::vector<Vertex> verts;
        float size{ 1.f };
        verts.push_back(Vertex{ -size,  size, -size, 1,1,1 });
        verts.push_back(Vertex{ size,  size, -size, 1,1,1 });
        verts.push_back(Vertex{ size,  size,  size, 1,1,1 });

        verts.push_back(Vertex{ -size,  size,  size, 1,1,1 });
        verts.push_back(Vertex{ -size, -size, -size, 1,1,1 });
        verts.push_back(Vertex{ size, -size, -size, 1,1,1 });
        verts.push_back(Vertex{ size, -size,  size, 1,1,1 });
        verts.push_back(Vertex{ -size, -size,  size, 1,1,1 });


        std::vector<GLuint> indices{ 0,1,1,2,2,3,3,0,4,5,5,6,6,7,7,4,0,4,1,5,2,6,3,7 };

        uint32_t VBO{};
        uint32_t EAB{};

        initializeOpenGLFunctions();
        //Vertex Array Object - VAO
        glGenVertexArrays(1, &VAO);
        glBindVertexArray(VAO);

        //Vertex Buffer Object to hold vertices - VBO
        glGenBuffers(1, &VBO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);

        glBufferData(GL_ARRAY_BUFFER, verts.size() * sizeof(Vertex), verts.data(), GL_STATIC_DRAW);

        // 1rst attribute buffer : vertices
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)0);
        glEnableVertexAttribArray(0);

        // 2nd attribute buffer : colors
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)(3 * sizeof(GLfloat)));
        glEnableVertexAttribArray(1);

        //Second buffer - holds the indices (Element Array Buffer - EAB):
        glGenBuffers(1, &EAB);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EAB);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint), indices.data(), GL_STATIC_DRAW);
    }

    glm::mat4 matrix(1.f);
    matrix[3].x = position.x;
    matrix[3].y = position.y;
    matrix[3].z = position.z;

    matrix[0].x = extent.x;
    matrix[1].y = extent.y;
    matrix[2].z = extent.z;

    //GLint prog = 0;
    //glGetIntegerv(GL_CURRENT_PROGRAM, &prog);

    glUseProgram(mShaderPrograms["plain"]->getProgram());

    glBindVertexArray(VAO);
    glUniformMatrix4fv(mShaderPrograms["plain"]->mMatrixUniform,          //the location of the matrix in the shader
        1,                       //count
        GL_FALSE,                //transpose the matrix before sending it?
        glm::value_ptr(matrix));    //the data of the matrix

    glDrawElements(GL_LINES, 24, GL_UNSIGNED_INT, 0);

    glBindVertexArray(0);

    //glUseProgram(prog);

}
