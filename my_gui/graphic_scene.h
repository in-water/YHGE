#ifndef GRAPHIC_SCENE_H
#define GRAPHIC_SCENE_H
#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <GL/glut.h>
#include "yhgegl.h"
#include "tet_struct.h"

class graphscene:public QOpenGLWidget,protected QOpenGLFunctions
{
    Q_OBJECT
public:
    ~graphscene();

    void initializeGL();
    void resizeGL(int w, int h);
    void paintGL();
    void show_region();
    void show_point();
    void show_mesh();
    void show_coordinate();

public slots:
//    void setXRotation(int angle);
//    void setYRotation(int angle);
//    void setZRotation(int angle);

    void setXRotation(const QString& angle);
    void setYRotation(const QString& angle);
    void setZRotation(const QString& angle);
    void setRegionState(bool toggled);
    void setPointState(bool toggled);

signals:
    void xRotationChanged(const QString&);
    void yRotationChanged(const QString&);
    void zRotationChanged(const QString&);

protected:
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);

public:
    YHGE::MyTetStruct* tet;
    int vertex_number_=500;

private:
    QPoint lastPos;

    void normalizeAngle(int* angle);
    int xRot;
    int yRot;
    int zRot;

    bool show_region_;
    bool show_point_;
    bool show_mesh_;
    bool show_coordinate_;
};

#endif // GRAPHIC_SCENE_H
