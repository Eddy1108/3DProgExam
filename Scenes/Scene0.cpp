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


    //Make Quadtree
    Point2D a{ -40, -40 }, b{ 40,-40 }, c{ 40,40 }, d{ -40,40 };
    mQuadTre->init(a, b, c, d);
    mQuadTre->subDivide(2);
    for (auto it = mObjects.begin(); it != mObjects.end(); it++)
    {
        if ((*it)->mBShape)
        {
            mQuadTre->insert((*it), (*it)->mBShape);    //Insert objects with a collision shape into the quadtre
        }

    }

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