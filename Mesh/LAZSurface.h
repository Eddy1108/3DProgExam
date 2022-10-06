#ifndef LAZSURFACE_H
#define LAZSURFACE_H

//#include "visualobject.h"
#include "Core/VisualObject.h"

#include "Mesh/PointCloud.h"
#include "renderwindow.h"

class Equidistance;

struct Hull {
    int indekser[3];
    int naboer[3];
};

struct SquareWHeights {
    float height;
    int iteration;
};

class LAZSurface : public VisualObject
{
public:
    LAZSurface(const std::string txtFileName, PointCloud* cloud, const QVector2D mGridSize, Shader& shader, const QVector3D offset = QVector3D(0.f, 0.f, 0.f), const float scale = 1);
    void construct(const std::string txtFileName);
    void readFile(const std::string txtFileName);
    void init() override;
    void draw() override;
    void addToAverageHeight(int xIndex, int yIndex, float height);
    float getAverageHeight(int x, int y);
    Equidistance* constructEquidistance();
    std::vector<QVector3D> getTriangleVertices(QVector3D pos);
    //void deLaunay();
    //void triangulate(std::vector<QVector3D>* points);
    static QVector3D calcBarycentric(QVector2D point, QVector2D p1, QVector2D p2, QVector2D p3);

    bool drawEquidistanceLines{ true };

protected:
    const float mScale{ 1 };
    const int mGridSizeX;
    const int mGridSizeY;
    const QVector3D mOffset;
    float xMax{ 0 }, xMin{ 0 }, yMax{ 0 }, yMin{ 0 };
    float zMax{ 0 }, zMin{ 0 };
    Equidistance* mEquiLines{ nullptr };
    int mEquidistance{ 10 };

    PointCloud* mCloud{nullptr};

    std::vector<int> mIndices;
    std::vector<std::vector<SquareWHeights>> mHeightInArea;
};

#endif // LAZSURFACE_H