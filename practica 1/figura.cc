#include "figura.h"
#include <GL/gl.h>
#include "user_code.h"
#include "cara.h"
#include "vertex.h"
#include "file_ply_stl.cc"

Figura::Figura(float color1,float color2, float color3)
{
    modo = 1;
    fichero = 0;
    leerPly("ant",color1,color2,color3);
}

Figura &Figura::operator=(const Figura &figura)
{
    vertices = figura.vertices;
    caras = figura.caras;
    modo = figura.modo;
    fichero = figura.fichero;
    c1 = figura.c1;
    c2 = figura.c2;
    c3 = figura.c3;

    return *this;
}

void Figura::leerPly(char *ply, float color1, float color2, float color3)
{
     vertices.clear();
     caras.clear();

     c1 = color1;
     c2 = color2;
     c3 = color3;

     vector<float> v;
     vector<int> c;

     ply::read(ply,v,c);

     _vertex3f vertice;

     for(int i=0; i < v.size();i+=3){
         vertice(v[i],v[i+1],v[i+2]);
         vertices.push_back(vertice);
     }

     Cara cara;

     for(int i=0; i < c.size(); i+=3){
         cara.a = c[i];
         cara.b = c[i+1];
         cara.c = c[i+2];
         caras.push_back(cara);
     }

}

void Figura::cambiarPly()
{
    fichero = (fichero+1)%3;

    if(fichero == 0)
        leerPly("ant",c1,c2,c3);
    else if(fichero == 1)
        leerPly("beethoven",c1,c2,c3);
    else if(fichero == 2)
        leerPly("big_dodge",c1,c2,c3);

}

void Figura::draw()
{
    if(modo == 0)
        draw_vertices(vertices,c1,c2,c3);
    if(modo == 1)
        draw_alambre(vertices,caras,c1,c2,c3);
    if(modo == 2)
        draw_solido(vertices,caras,c1,c2,c3);
    if(modo == 3)
        draw_ajedrez(vertices,caras,c1,c2,c3);
    if(modo == 4)
        draw_alambre_Mitad(vertices,caras,c1,c2,c3);
    if(modo == 5)
        draw_solido_Mitad(vertices,caras,c1,c2,c3);
    if(modo == 6)
        draw_ajedrez_Mitad(vertices,caras,c1,c2,c3);
    if(modo == 7)
        draw_vertices_Mitad(vertices,c1,c2,c3);
    if(modo == 8)
        draw_solido_Cuatro(vertices,caras);
}

