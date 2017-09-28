HEADERS = \
    file_ply_stl.h \
    vertex.h \
    objeto.h \
    objetoR.h \
    jerarquico.h \
    user_code.h \
    cara.h
  
SOURCES = \
    practica1.cc \
    file_ply_stl.cc \
    objeto.cc \
    objetoR.cc \
    jerarquico.cc \
    user_code.cc \
    cara.cc


LIBS += -L/casa/dmartin/codigo/funciontecas/freeglut/lib \
    -lglut

CONFIG += console
QT += opengl

