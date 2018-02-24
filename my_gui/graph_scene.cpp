#include "graphic_scene.h"
#include "yhgegl.h"
#include <QMouseEvent>

graphscene::~graphscene()
{
    delete tet;
}

void graphscene::initializeGL()
{
    show_region_=true;
    show_point_=false;
    show_mesh_=false;
    show_coordinate_=false;
    tet =new YHGE::MyTetStruct;
    initializeOpenGLFunctions();
    glClearColor(0.83f,0.83f,0.83f,0.4f);
    glClearDepth(1.0);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
}

void graphscene::resizeGL(int w, int h)
{

}

void graphscene::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    glRotatef( xRot/16,  1.0,  0.0,  0.0 );
    glRotatef( yRot/16,  0.0,  1.0,  0.0 );
    glRotatef( zRot/16,  0.0,  0.0,  1.0 );

    if (show_region_)
    {
        show_region();
    }

    if (show_point_)
    {
        show_point();
    }

    if (show_mesh_)
    {
        show_mesh();
    }

    if (show_coordinate_)
    {
        show_coordinate();
    }
    //glFlush();
}

void graphscene::show_region()
{
    glColor3f(1.0f, 1.0f, 1.0f);
    glBegin(GL_LINES);
    int n=tet->boundary().size();
    YHGE::TriMesh t=tet->boundary();
    for (int i = 0; i < n; ++i)
    {
        //std::cout<<i<<std::endl;
                 //if(!YHGX::is_inifint())
        YHGE::vec3 p0 = t[i].vertex[0];
        YHGE::vec3 p1 = t[i].vertex[1];
        YHGE::vec3 p2 = t[i].vertex[2];

        glVertex(p0);glVertex(p1);
        glVertex(p0);glVertex(p2);
        glVertex(p1);glVertex(p2);
    }//std::cout<<"ok"<<std::endl;
    glEnd();
}

void graphscene::show_point()
{
    glPointSize(3.0f);
    glColor3f(1.0f,0.0f,0.0f);
    glBegin(GL_POINTS);
    std::vector<YHGE::vec3> b=tet->boundary_point(); int n=b.size();
    for (int i=0;i<n;++i)
    {
        glVertex(b[i]);
    }
    glEnd();
}

void graphscene::show_mesh()
{

}

void graphscene::show_coordinate()
{
    glColor3f(0.0f,0.0f,0.0f);
    glBegin(GL_LINES);
    glVertex3f(0.0f, 0.0f, 0.0f);
    glVertex3f(1.0, 0.0f, 0.0f);
    glEnd();
    glPushMatrix();
    glTranslatef(1.0, 0.0f, 0.0f);
    glRotatef(90.0f,0.0f,1.0f,0.0f);
    //glutWireCone(0.027,0.09,10,10);
    glPopMatrix();
}

void graphscene::normalizeAngle(int *angle)
{
    while(*angle<0)
        *angle+=360*16;
    while(*angle>360*16)
        *angle-=360*16;
}

void graphscene::setXRotation(const QString& qangle)
{
    int angle=qangle.toInt()*16;
    normalizeAngle(&angle);
    if(angle!=xRot)
    {
        xRot=angle;
        emit xRotationChanged(QString::number(angle/16>180?angle/16-360:angle/16));
        update();
    }
}

void graphscene::setYRotation(const QString& qangle)
{
    int angle=qangle.toInt()*16;
    normalizeAngle(&angle);
    if(angle!=yRot)
    {
        yRot=angle;
        emit yRotationChanged(QString::number(angle/16>180?angle/16-360:angle/16));
        update();
    }
}

void graphscene::setZRotation(const QString& qangle)
{
    int angle=qangle.toInt()*16;
    normalizeAngle(&angle);
    if(angle!=zRot)
    {
        zRot=angle;
        emit zRotationChanged(QString::number(angle/16>180?angle/16-360:angle/16));
        update();
    }
}

void graphscene::setRegionState(bool toggled)
{
    show_region_=toggled;
    update();
}

void graphscene::setPointState(bool toggled)
{
    show_point_=toggled;
    update();
}

void graphscene::mousePressEvent(QMouseEvent *event)
{
    switch (event->buttons())
    {
    case Qt::LeftButton:
        lastPos=event->pos();
        break;
    case Qt::RightButton:
        setXRotation(0);
        setYRotation(0);
        setZRotation(0);
        break;
    }
}

void graphscene::mouseMoveEvent(QMouseEvent *event)
{
    int dx=event->x()-lastPos.x();
    int dy=event->y()-lastPos.y();
    switch(event->buttons())
    {
    case Qt::LeftButton:
//        setXRotation(xRot+2*dy);
//        setYRotation(yRot+2*dx);
//        setZRotation(zRot+2*dx);
        setXRotation(QString::number((xRot+2*dy)/16));
        setYRotation(QString::number((yRot+2*dx)/16));
        setZRotation(QString::number((zRot+2*dx)/16));
        break;
    }
}
