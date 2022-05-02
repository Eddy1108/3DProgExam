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

    InteractiveObject* mInteract = new InteractiveObject(*mShaderPrograms["plain"]);
    mObjects.push_back(mInteract);
    mInteract->setName("mia");

    mLight = new Light(*mShaderPrograms["plain"]);
    mObjects.push_back(mLight);
    mLight->setName("Light");

    mObjects.push_back(temp = new ObjLoader(*mShaderPrograms["plain"], "../3DProgExam/assets/models/monkey2.obj", ""));
    temp->setName("Mario");
    temp->move(-5, 0, 0);

    //mObjects.push_back(temp = new ObjLoader(*mShaderPrograms["plain"], "../3DProgExam/assets/models/arthur.obj", ""));

    mObjects.push_back(temp = new Trophy(*mShaderPrograms["plain"], 8.f, 8.f, 0.f));
    temp->setName("Trophy");


        //Textured Objects
    //Use mObjects2!
    mObjects2.push_back(temp = new TriangleSurface(*mShaderPrograms["textured"]));
    temp->setName("TriangleSurface");
    mObjects2.push_back(temp = new Triangle(*mShaderPrograms["textured"]));
    temp->setName("Triangle");
    mObjects2.push_back(temp = new ObjLoader(*mShaderPrograms["textured"], "../3DProgExam/assets/models/WA2.obj", "../3DProgExam/Assets/tex/waluigi_body.bmp"));
    temp->setName("Waluigi");
    mObjects2.push_back(temp = new Billboard(*mShaderPrograms["textured"], mCamera));
    temp->setName("Billboard");

    
        //Phong Objects
    //Use mObjects3!
    Heightmap* mHeightmap = new Heightmap(*mShaderPrograms["phong"]);
    mObjects3.push_back(mHeightmap);
    mHeightmap->setName("Heightmap");
    mInteract->mHeightmap = mHeightmap;

        //Billboards
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
    Point2D a{ -20, -20 }, b{ 20,-20 }, c{ 20,20 }, d{ -20,20 };
    mQuadTre.init(a, b, c, d);
    mQuadTre.subDivide(2);
    for (auto it = mObjects.begin(); it != mObjects.end(); it++)
    {
        if ((*it)->mBShape)
        {
            mQuadTre.insert((*it), (*it)->mBShape);
            std::cout << (*it)->getName() << "    " << (*it)->getPosition2D().x << ", " << (*it)->getPosition2D().y << std::endl;
        }
        //else
        //mQuadTre.insert((*it));
    }
    //for (auto it = mObjects2.begin(); it != mObjects2.end(); it++)
    //{
    //    mQuadTre.insert((*it));
    //}
    //for (auto it = mObjects3.begin(); it != mObjects3.end(); it++)
    //{
    //    mQuadTre.insert((*it));
    //}
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