//**************************************************************************
// Codigo del usuario
//
// Domingo Martin Perandres 2013
//
// GPL
//**************************************************************************


#include "objeto.h"
#include <GL/gl.h>
#include "user_code.h"
#include "cara.h"
#include "vertex.h"
#include "file_ply_stl.h"

Objeto::Objeto()
{
    activo = false;
    modo = 2;
    fichero = 0;
    cargarPly("beethoven.ply",1,0,1);
}

Objeto &Objeto::operator=(const Objeto &objeto)
{
    vertices = objeto.vertices;
    caras = objeto.caras;
    normalesCaras = objeto.normalesCaras;
    normalesVertices = objeto.normalesVertices;
    activo = objeto.activo;
    modo = objeto.modo;
    fichero = objeto.fichero;
    c1 = objeto.c1;
    c2 = objeto.c2;
    c3 = objeto.c3;

    return *this;
}

void Objeto::cargarPly(char *ply, float color1, float color2, float color3)
{
     vertices.clear();
     caras.clear();

     c1 = color1;
     c2 = color2;
     c3 = color3;

     vector<float> v;
     vector<int> c;

      _file_ply f;

     f.open(ply);
     f.read(v,c);
     f.close();

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

     generarNormalesCaras();
     generarNormalesVertices();
}

void Objeto::generarNormalesCaras()
{
    normalesCaras.clear();

    _vertex3f ab;
    _vertex3f bc;

    _vertex3f n;

    for(int i=0; i < caras.size(); i++)
    {
        ab.x = vertices[caras[i].b].x - vertices[caras[i].a].x;
        ab.y = vertices[caras[i].b].y - vertices[caras[i].a].y;
        ab.z = vertices[caras[i].b].z - vertices[caras[i].a].z;

        bc.x = vertices[caras[i].c].x - vertices[caras[i].b].x;
        bc.y = vertices[caras[i].c].y - vertices[caras[i].b].y;
        bc.z = vertices[caras[i].c].z - vertices[caras[i].b].z;

        n.x = (ab.y*bc.z)-(bc.y*ab.z);
        n.y = (-1)*((ab.x*bc.z)-(bc.x*ab.z));
        n.z = (ab.x*bc.y)-(bc.x*ab.y);

        n.normalize();

        normalesCaras.push_back(n);
    }
}

void Objeto::generarNormalesVertices()
{
    normalesVertices.clear();

    _vertex3f n(0,0,0);

    for(int i=0; i < vertices.size(); i++)
       normalesVertices.push_back(n);

    for(int j=0; j < caras.size(); j++)
    {
        normalesVertices[caras[j].a] += normalesCaras[j];
        normalesVertices[caras[j].b] += normalesCaras[j];
        normalesVertices[caras[j].c] += normalesCaras[j];
    }

    for(int k=0; k < normalesVertices.size(); k++)
        normalesVertices[k] = normalesVertices[k].normalize();
}

void Objeto::cambiarPly()
{
    activo = true;

    fichero = (fichero+1)%4;

    if(fichero == 0)
        cargarPly("ant.ply",c1,c2,c3);
    else if(fichero == 1)
        cargarPly("beethoven.ply",c1,c2,c3);
    else if(fichero == 2)
        cargarPly("big_dodge.ply",c1,c2,c3);
    else if(fichero == 3)
        activo = false;
}

void Objeto::cambiarColor(float color1, float color2, float color3)
{
    c1= color1;
    c2= color2;
    c3= color3;

}

void Objeto::draw()
{
    if(activo)
    {
        if(modo == 0)
            draw_vertices(vertices,c1,c2,c3);
        if(modo == 1)
            draw_alambre(vertices,caras,c1,c2,c3);
        if(modo == 2)
            draw_solido(vertices,caras,c1,c2,c3);
        if(modo == 3)
            draw_ajedrez(vertices,caras,c1,c2,c3);
    }
}

