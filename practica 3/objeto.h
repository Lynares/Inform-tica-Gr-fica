//**************************************************************************
// Práctica 1
//
// Domingo Martin Perandres 2013
//
// GPL
//**************************************************************************

#ifndef OBJETO_H
#define OBJETO_H

#include <GL/gl.h>
#include <vector>
#include "vertex.h"
#include "cara.h"
#include "file_ply_stl.h"

using namespace std;

class Objeto{
    private:
        vector<_vertex3f> vertices;
        vector<Cara> caras;
        vector<_vertex3f> normalesCaras;
        vector<_vertex3f> normalesVertices;
        bool activo;
        int modo;
        int fichero;
        void generarNormalesCaras();
        void generarNormalesVertices();
        float c1,c2,c3;
    public:
        Objeto();
        Objeto &operator=(const Objeto &objeto);
        ~Objeto(){}
        void cargarPly(char *ply,float color1,float color2,float color3);
        void cambiarPly();
        void cambiarModo(int m){ modo = m; }
        void cambiarColor(float color1, float color2, float color3);
        void activar(){ if (activo) activo = false; else activo = true;}
        void draw();
};

#endif
