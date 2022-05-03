#include "Scene0.h"

Scene0::Scene0(std::unordered_map<std::string, Shader*> shaders)
    : Scene(shaders)
{
    mCamera = new Camera();

    mSkybox = new SkyBox(*mShaderPrograms["skybox"]);

    VisualObject* temp;

    ///Create Objects
        //Untextured Objects
    mObjects.push_back(temp = new XYZ(*mShaderPrograms["plain"]));
    temp->setName("XYZ");

    mLight = new Sun(*mShaderPrograms["plain"]);
    mObjects.push_back(mLight);
    mLight->setName("Sun");

    //Task 7:
    //mObjects.push_back(temp = new BezierCurve(*mShaderPrograms["plain"]));
    //temp->setName("Bezier");

    mObjects.push_back(temp = new Enemy(*mShaderPrograms["plain"], mQuadTre));
    temp->setName("Enemy");
    mObjects.push_back(temp = new Bomb(*mShaderPrograms["plain"], mQuadTre));
    temp->setName("Bomb0");



    //Task 8
    mObjects.push_back(temp = new Trophy(*mShaderPrograms["plain"], 8.f, 8.f, 2.f, true));
    temp->setName("RedTrophy0");
    mObjects.push_back(temp = new Trophy(*mShaderPrograms["plain"], 20.f, 10.f, 2.f, true));
    temp->setName("RedTrophy1");
    mObjects.push_back(temp = new Trophy(*mShaderPrograms["plain"], -12.f, 22.f, 2.f, true));
    temp->setName("RedTrophy2");
    mObjects.push_back(temp = new Trophy(*mShaderPrograms["plain"], -15.f, -5.f, 2.f, true));
    temp->setName("RedTrophy3");
    mObjects.push_back(temp = new Trophy(*mShaderPrograms["plain"], 18.f, -8.f, 2.f, true));
    temp->setName("RedTrophy4");
    mObjects.push_back(temp = new Trophy(*mShaderPrograms["plain"], -2.f, -30.f, 2.f, true));
    temp->setName("RedTrophy5");
    mObjects.push_back(temp = new Trophy(*mShaderPrograms["plain"], -26.f, 4.f, 2.f, true));
    temp->setName("RedTrophy6");
    mObjects.push_back(temp = new Trophy(*mShaderPrograms["plain"], 8.f, -15.f, 2.f, true));
    temp->setName("RedTrophy7");
    mObjects.push_back(temp = new Trophy(*mShaderPrograms["plain"], 15.f, 23.f, 2.f, true));
    temp->setName("RedTrophy8");
    mObjects.push_back(temp = new Trophy(*mShaderPrograms["plain"], -17.f, -20.f, 2.f, true));
    temp->setName("RedTrophy9");

    std::vector<VisualObject*> BlueTrophies;

    mObjects.push_back(temp = new Trophy(*mShaderPrograms["plain"], 0.f, 8.f, 2.f, false));
    temp->setName("BlueTrophy0");
    BlueTrophies.push_back(temp);
    mObjects.push_back(temp = new Trophy(*mShaderPrograms["plain"], -9.f, 15.f, 2.f, false));
    temp->setName("BlueTrophy1");
    BlueTrophies.push_back(temp);
    mObjects.push_back(temp = new Trophy(*mShaderPrograms["plain"], 25.f, -22.f, 2.f, false));
    temp->setName("BlueTrophy2");
    BlueTrophies.push_back(temp);
    mObjects.push_back(temp = new Trophy(*mShaderPrograms["plain"], 10.f, -27.f, 2.f, false));
    temp->setName("BlueTrophy3");
    BlueTrophies.push_back(temp);
    mObjects.push_back(temp = new Trophy(*mShaderPrograms["plain"], 25.f, 20.f, 2.f, false));
    temp->setName("BlueTrophy4");
    BlueTrophies.push_back(temp);
    mObjects.push_back(temp = new Trophy(*mShaderPrograms["plain"], -6.f, -18.f, 2.f, false));
    temp->setName("BlueTrophy5");
    BlueTrophies.push_back(temp);
    mObjects.push_back(temp = new Trophy(*mShaderPrograms["plain"], -25.f, -15.f, 2.f, false));
    temp->setName("BlueTrophy6");
    BlueTrophies.push_back(temp);
    mObjects.push_back(temp = new Trophy(*mShaderPrograms["plain"], -30.f, 10.f, 2.f, false));
    temp->setName("BlueTrophy7");
    BlueTrophies.push_back(temp);
    mObjects.push_back(temp = new Trophy(*mShaderPrograms["plain"], -32.f, 25.f, 2.f, false));
    temp->setName("BlueTrophy8");
    BlueTrophies.push_back(temp);
    mObjects.push_back(temp = new Trophy(*mShaderPrograms["plain"], 32.f, 2.f, 2.f, false));
    temp->setName("BlueTrophy9");
    BlueTrophies.push_back(temp);

    //Obj loading tests here
    //mObjects.push_back(temp = new ObjLoader(*mShaderPrograms["plain"], "../3DProgExam/assets/models/bomb.obj", ""));



    ///Textured Objects
//Use mObjects2!
    //mObjects2.push_back(temp = new Billboard(*mShaderPrograms["textured"], mCamera, "../3DProgExam/Assets/tex/jacky.bmp"));
    //temp->setName("Billboard Test");


    ///Phong Objects (+ Texture)
//Use mObjects3!

    //Task 4:
    InteractiveObject* mInteract = new Player(*mShaderPrograms["phong"]);
    mObjects3.push_back(mInteract);
    mInteract->setName("mia");
    dynamic_cast<Player*>(mInteract)->mCam = mCamera;

    //Task 2:
    Heightmap* mHeightmap = new Heightmap(*mShaderPrograms["phong"]);
    mObjects3.push_back(mHeightmap);
    mHeightmap->setName("Heightmap");
    mInteract->mHeightmap = mHeightmap;

    //Task 9:
    NPC* npc = new NPC(*mShaderPrograms["phong"]);
    mObjects3.push_back(npc);
    npc->setName("NPC");
    npc->mHeightmap = mHeightmap;
    npc->mTrophyList = BlueTrophies;

    //Task 10
    mObjects3.push_back(temp = new Fence(*mShaderPrograms["phong"], true));
    temp->setName("Fence1");
    temp->mPosition = glm::vec3(13.f, 10.f, 1.f);
    mObjects3.push_back(temp = new Fence(*mShaderPrograms["phong"], true));
    temp->setName("Fence2");
    temp->mPosition = glm::vec3(13.f, 12.f, 1.f);
    mObjects3.push_back(temp = new Fence(*mShaderPrograms["phong"], true));
    temp->setName("Fence3");
    temp->mPosition = glm::vec3(13.f, 8.f, 1.f);
    mObjects3.push_back(temp = new Fence(*mShaderPrograms["phong"], true));
    temp->setName("Fence4");
    temp->mPosition = glm::vec3(13.f, 6.f, 1.f);
    mObjects3.push_back(temp = new Fence(*mShaderPrograms["phong"], true));
    temp->setName("Fence5");
    temp->mPosition = glm::vec3(13.f, 4.f, 1.f);
    mObjects3.push_back(temp = new Fence(*mShaderPrograms["phong"], true));
    temp->setName("Fence6");
    temp->mPosition = glm::vec3(13.f, 2.f, 1.f);
    mObjects3.push_back(temp = new Fence(*mShaderPrograms["phong"], true));
    temp->setName("Fence7");
    temp->mPosition = glm::vec3(13.f, 0.f, 1.f);

    mObjects3.push_back(temp = new Fence(*mShaderPrograms["phong"], false));
    temp->setName("Fence8");
    temp->mPosition = glm::vec3(-10.f, -12.f, 1.f);
    mObjects3.push_back(temp = new Fence(*mShaderPrograms["phong"], false));
    temp->setName("Fence9");
    temp->mPosition = glm::vec3(-12.f, -12.f, 1.f);
    mObjects3.push_back(temp = new Fence(*mShaderPrograms["phong"], false));
    temp->setName("Fence10");
    temp->mPosition = glm::vec3(-14.f, -12.f, 1.f);
    mObjects3.push_back(temp = new Fence(*mShaderPrograms["phong"], false));
    temp->setName("Fence11");
    temp->mPosition = glm::vec3(-16.f, -12.f, 1.f);
    mObjects3.push_back(temp = new Fence(*mShaderPrograms["phong"], false));
    temp->setName("Fence12");
    temp->mPosition = glm::vec3(-18.f, -12.f, 1.f);
    mObjects3.push_back(temp = new Fence(*mShaderPrograms["phong"], false));
    temp->setName("Fence13");
    temp->mPosition = glm::vec3(-20.f, -12.f, 1.f);
    mObjects3.push_back(temp = new Fence(*mShaderPrograms["phong"], false));
    temp->setName("Fence14");
    temp->mPosition = glm::vec3(-22.f, -12.f, 1.f);
    mObjects3.push_back(temp = new Fence(*mShaderPrograms["phong"], false));
    temp->setName("Fence15");
    temp->mPosition = glm::vec3(-24.f, -12.f, 1.f);
    mObjects3.push_back(temp = new Fence(*mShaderPrograms["phong"], false));
    temp->setName("Fence16");
    temp->mPosition = glm::vec3(-8.f, -12.f, 1.f);
    mObjects3.push_back(temp = new Fence(*mShaderPrograms["phong"], false));
    temp->setName("Fence17");
    temp->mPosition = glm::vec3(-6.f, -12.f, 1.f);

        ///???
    //Use mObjects4!



    ///Dump it all into Unordered lists
    for (auto it = mObjects.begin(); it != mObjects.end(); it++)
    {
        mMap.insert(std::pair<std::string, VisualObject*>{(*it)->getName(), * it});
    }

    for (auto it = mObjects2.begin(); it != mObjects2.end(); it++)
    {
        mMap2.insert(std::pair<std::string, VisualObject*>{(*it)->getName(), * it});
    }

    for (auto it = mObjects3.begin(); it != mObjects3.end(); it++)
    {
        mMap3.insert(std::pair<std::string, VisualObject*>{(*it)->getName(), * it});
    }
    for (auto it = mObjects4.begin(); it != mObjects4.end(); it++)
    {
        mMap4.insert(std::pair<std::string, VisualObject*>{(*it)->getName(), * it});
    }


    //Make Quadtree
    Point2D a{ -40, -40 }, b{ 40,-40 }, c{ 40,40 }, d{ -40,40 };
    mQuadTre->init(a, b, c, d);
    mQuadTre->subDivide(2);
    for (auto it = mObjects.begin(); it != mObjects.end(); it++)
    {
        if ((*it)->mBShape)
        {
            mQuadTre->insert((*it), (*it)->mBShape);
            //std::cout << (*it)->getName() << "    " << (*it)->getPosition2D().x << ", " << (*it)->getPosition2D().y << std::endl;
        }
        //else
        //mQuadTre.insert((*it));
    }
    //for (auto it = mObjects2.begin(); it != mObjects2.end(); it++)
    //{
    //    mQuadTre.insert((*it));
    //}
    for (auto it = mObjects3.begin(); it != mObjects3.end(); it++)
    {
        if ((*it)->mBShape)
        {
            mQuadTre->insert((*it), (*it)->mBShape);
        }
    }
}

Scene0::~Scene0()
{
}

void Scene0::init()
{
    Scene::init();
}

void Scene0::draw()
{
    Scene::draw();

}