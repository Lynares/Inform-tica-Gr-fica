HEADERS = \
    vertex.h \
    user_code.h \
    file_ply_stl.h \
    cara.h \
    figura.h

  
SOURCES = \
    practica1.cc \
    user_code.cc \
    file_ply_stl.cc \
    figura.cc

LIBS += -L/casa/dmartin/codigo/funciontecas/freeglut/lib \
    -lglut

CONFIG += console
QT += opengl

