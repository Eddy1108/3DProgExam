QT          += core gui widgets opengl

TEMPLATE    = app
CONFIG      += c++17

TARGET      = 3D-programmering

SOURCES += main.cpp \
    Core/Camera.cpp \
    Core/CollisionShapes.cpp \
    Core/Vertex.cpp \
    Core/VisualObject.cpp \
    Core/XYZ.cpp \
    Core/quadtree.cpp \
    Core/shader.cpp \
    Core/texture.cpp \
    Light/Light.cpp \
    Math/Barycentric.cpp \
    Math/BezierCurve.cpp \
    Mesh/Billboard.cpp \
    Mesh/Disc.cpp \
    Mesh/Door.cpp \
    Mesh/Graph.cpp \
    Mesh/Heightmap.cpp \
    Mesh/House.cpp \
    Mesh/Kube.cpp \
    Mesh/NPC_Cube.cpp \
    Mesh/ObjLoader.cpp \
    Mesh/OctahedronBall.cpp \
    Mesh/Player/InteractiveObject.cpp \
    Mesh/SkyBox.cpp \
    Mesh/Triangle.cpp \
    Mesh/TriangleSurface.cpp \
    Mesh/Trophy.cpp \
    Scenes/Scene.cpp \
    Scenes/Scene0.cpp \
    Scenes/Scene1.cpp \
    Scenes/SceneSwitcher.cpp \
    Shaders/PhongShader.cpp \
    Shaders/PlainShader.cpp \
    Shaders/SkyBoxShader.cpp \
    Shaders/TextureShader.cpp \
    logger.cpp \
    mainwindow.cpp \
    renderwindow.cpp

HEADERS += \
    Core/Camera.h \
    Core/CollisionShapes.h \
    Core/Vertex.h \
    Core/VisualObject.h \
    Core/XYZ.h \
    Core/quadtree.h \
    Core/shader.h \
    Core/texture.h \
    Light/Light.h \
    Math/Barycentric.h \
    Math/BezierCurve.h \
    Mesh/Billboard.h \
    Mesh/Disc.h \
    Mesh/Door.h \
    Mesh/Graph.h \
    Mesh/Heightmap.h \
    Mesh/House.h \
    Mesh/Kube.h \
    Mesh/NPC_Cube.h \
    Mesh/ObjLoader.h \
    Mesh/OctahedronBall.h \
    Mesh/Player/InteractiveObject.h \
    Mesh/SkyBox.h \
    Mesh/Triangle.h \
    Mesh/TriangleSurface.h \
    Mesh/Trophy.h \
    Scenes/Scene.h \
    Scenes/Scene0.h \
    Scenes/Scene1.h \
    Scenes/SceneSwitcher.h \
    Shaders/PhongShader.h \
    Shaders/PlainShader.h \
    Shaders/SkyBoxShader.h \
    Shaders/TextureShader.h \
    logger.h \
    mainwindow.h \
    renderwindow.h \
# external libs
#    stb_image/stb_image.h \
    glm/glm.hpp

FORMS += \
    mainwindow.ui

DISTFILES += \
    Assets/tex/heightmap.bmp \
    Assets/tex/hund.bmp \
    Assets/tex/linus.bmp \
    Shaders/phongshader.frag \
    Shaders/phongshader.vert \
    Shaders/plainshader.frag \
    Shaders/plainshader.vert \
    Shaders/plainshaderChad.frag \
    Shaders/plainshaderChad.vert \
    Shaders/textureshader.frag \
    Shaders/textureshader.vert
