HEADERS = \
    file_ply_stl.hpp \
    vertex.h \
    figura.h \
    user_code.h \
    cara.h

  
SOURCES = \
    practica1.cc \
    file_ply_stl.cc \
    figura.cc \
    user_code.cc

LIBS += -L/casa/dmartin/codigo/funciontecas/freeglut/lib \
    -lglut

CONFIG += console
QT += opengl

