#ifndef FIGURA_H
#define FIGURA_H

#include <GL/gl.h>
#include <vector>
#include "vertex.h"
#include "file_ply_stl.h"
#include "cara.h"
using namespace std;

class Figura{
    private:
        vector<_vertex3f> vertices;
        vector<Cara> caras;
        vector<_vertex3f> normalesCaras;
        vector<_vertex3f> normalesVertices;
        vector<_vertex3f> puntoMedioCaras;
        bool visualizar;
        int modo;
        int fichero;
        int ficheroPerfil;
        int lados;
        int tamPerfil;
        bool tapaSuperior;
        bool tapaInferior;
        _vertex3<float> tapaS;
        _vertex3<float> tapaI;
        int ladosMostrados;
        bool normales;
        void cargarPly();
        void cargarPlyPerfil();
        void draw_vertices();
        void draw_alambre();
        void draw_solido();
        void draw_ajedrez();
        void draw_normales();
        void generarVertices();
        void generarCara(int a, int b, int c);
        void generarTapaInferior();
        void generarTapaSuperior();
        void generarCaras();
        void generarNormalesCaras();
        void generarNormalesVertices();
        void calcularPuntoMedioCaras();
    public:
        Figura();
        Figura(int l);
        ~Figura(){}

        void cambiarPly();
        void cambiarPlyPerfil();
        void cambiarModo(int m){ modo = m; }
        void mostrarLados();
        void draw();
        void cambiarNormales();
};
#endif
