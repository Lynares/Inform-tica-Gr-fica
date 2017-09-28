HEADERS = \
    vertex.h \
    objetos.h \
    file_ply_stl.h
	

SOURCES = \
    practica1.cc \
    objetos.cc \
    file_ply_stl.cc

LIBS += -L/casa/dmartin/codigo/funciontecas/freeglut/lib \
    -lglut

CONFIG += console
QT += opengl

