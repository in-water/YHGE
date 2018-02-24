#-------------------------------------------------
#
# Project created by QtCreator 2018-02-04T18:02:52
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = my_gui
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    meshes.cpp \
    yhge_type.cpp \
    graph_scene.cpp \
    tet_struct.cpp

LIBS += -L$$PWD/../../../../../usr/lib/x86_64-linux-gnu/ -lglut -lGL -lGLU -lCGAL -lgmp

INCLUDEPATH += $$PWD/../../../../../usr/lib/x86_64-linux-gnu
DEPENDPATH += $$PWD/../../../../../usr/lib/x86_64-linux-gnu

HEADERS += \
    meshes.h \
    glsl_linear.h \
    vecg.h \
    geometry.h \
    matrix.h \
    line_stream.h \
    yhge_type.h \
    mainwindow.h \
    graphic_scene.h \
    tet_struct.h \
    yhgegl.h

