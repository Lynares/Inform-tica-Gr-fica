#ifndef OBJETOR_H
#define OBJETOR_H

#include "cara.h"
#include "vertex.h"
#include <vector>

class ObjetoR{
    private:
        vector<_vertex3f> vertices;
        vector<Cara> caras;
        vector<_vertex3f> normalesCaras;
        vector<_vertex3f> normalesVertices;
        bool activo;
        int modo;
        int fichero;
        int lados;
        int tamPerfil;
        bool tapaSuperior;
        bool tapaInferior;
        _vertex3<float> tapaS;
        _vertex3<float> tapaI;
        float c1,c2,c3;

        void generarVertices();
        void generarCara(int a, int b, int c);
        void generarTapaInferior();
        void generarTapaSuperior();
        void generarCaras();
        void generarNormalesCaras();
        void generarNormalesVertices();
    public:
        ObjetoR();
        ObjetoR &operator=(const ObjetoR &objetoR);
        ~ObjetoR(){}
        void cargarPly(char *ply, float color1, float color2, float color3);
        void cambiarPly();
        void cambiarModo(int m){ modo = m; }
        void cambiarLados(int l){ lados = l; }
        void activar(){ activo=true; }
        void cambiarColor(float color1, float color2, float color3);
        void draw();
};

#endif
