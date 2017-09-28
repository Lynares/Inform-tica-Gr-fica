
#include "objetoR.h"
#include "user_code.h"
#include "cara.h"
#include "vertex.h"
#include "file_ply_stl.h"
#include <math.h>
#include <vector>

#define PI 3.141592

ObjetoR::ObjetoR()
{
    activo = false;
    modo = 2;
    fichero = 6;
    lados = 20;
    c1 = 0;
    c2 = 0;
    c3 = 1;
    cargarPly("peon.ply",c1,c2,c3);
}

ObjetoR &ObjetoR::operator=(const ObjetoR &objetoR)
{
    vertices = objetoR.vertices;
    caras = objetoR.caras;
    normalesCaras = objetoR.normalesCaras;
    normalesVertices = objetoR.normalesVertices;
    activo = objetoR.activo;
    modo = objetoR.modo;
    fichero = objetoR.fichero;
    lados = objetoR.lados;
    tamPerfil = objetoR.tamPerfil;
    tapaSuperior = objetoR.tapaSuperior;
    tapaInferior = objetoR.tapaInferior;
    tapaS = objetoR.tapaS;
    tapaI = objetoR.tapaI;
    c1 = objetoR.c1;
    c2 = objetoR.c2;
    c3 = objetoR.c3;

    return *this;
}

void ObjetoR::cargarPly(char *ply, float color1, float color2, float color3)
{
    vertices.clear();
    caras.clear();

    c1 = color1;
    c2 = color2;
    c3 = color3;

    tapaSuperior = false;
    tapaInferior = false;

    vector<float> perfil;
    vector<int> c;

    _file_ply f;

    f.open(ply);
    f.read(perfil,c);
    f.close();

    _vertex3f vertice;

    for(int i=0; i < perfil.size();i+=3)
    {
        vertice(perfil[i],perfil[i+1],perfil[i+2]);

        if(i == 0)
        {
            if(vertice.x == 0)
            {
                tapaInferior = true;
                tapaI = vertice;
            }
            else
                vertices.push_back(vertice);
        }

        if(i != 0)
            vertices.push_back(vertice);
    }

    if(vertices[vertices.size()-1].x == 0)
    {
        tapaSuperior = true;
        tapaS = vertices[vertices.size()-1];
        vertices.pop_back();
    }

    tamPerfil = vertices.size();

    generarVertices();
    generarCaras();
}

void ObjetoR::generarVertices()
{
    double grados = 360/lados*1.0;

    _vertex3f vertice;

    for(int i=0; i < lados-1; i++)
    {
        for(int j=0; j < tamPerfil; j++)
        {
            vertice.x = vertices[i*tamPerfil+j].x*cos(grados*PI/180.0) + vertices[i*tamPerfil+j].z*sin(grados*PI/180.0);
            vertice.y = vertices[i*tamPerfil+j].y;
            vertice.z = vertices[i*tamPerfil+j].x*(-1)*sin(grados*PI/180.0) + vertices[i*tamPerfil+j].z*cos(grados*PI/180.0);

            vertices.push_back(vertice);
        }
    }

    if(tapaInferior)
        vertices.push_back(tapaI);
    if(tapaSuperior)
        vertices.push_back(tapaS);
}

void ObjetoR::generarCara(int a,int b, int c)
{
    Cara cara;

    cara.a = a;
    cara.b = b;
    cara.c = c;

    caras.push_back(cara);
}

void ObjetoR::generarCaras()
{
    for(int i=0; i < tamPerfil-1;i++)
    {
        for(int j=0; j < lados; j++)
        {
            generarCara(i+j*tamPerfil,i+((j+1)%lados)*tamPerfil,(i+1)%tamPerfil+j*tamPerfil);
            generarCara(i+((j+1)%lados)*tamPerfil,((i+1)%tamPerfil)+((j+1)%lados)*tamPerfil,(i+1)%tamPerfil+j*tamPerfil);
        }
    }

    if(tapaInferior)
        generarTapaInferior();

    if(tapaSuperior)
        generarTapaSuperior();

    generarNormalesCaras();
    generarNormalesVertices();
}

void ObjetoR::generarTapaInferior()
{
    int modulo;

    if(tapaSuperior)
        modulo = vertices.size()-2;
    else
        modulo = vertices.size()-1;

    for(int i=0; i < lados; i++)
        generarCara(modulo,(i*tamPerfil + tamPerfil)%modulo,i*tamPerfil);
}

void ObjetoR::generarTapaSuperior()
{
    int modulo;

    if(tapaInferior)
        modulo = vertices.size()-2;
    else
        modulo = vertices.size()-1;


    for(int i=0; i < lados; i++)
        generarCara(vertices.size()-1,i*tamPerfil + tamPerfil-1,((tamPerfil-1)+(i+1)*tamPerfil)%modulo);
}

void ObjetoR::generarNormalesCaras()
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

void ObjetoR::generarNormalesVertices()
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

void ObjetoR::cambiarPly()
{
    activo = true;

    fichero = (fichero+1)%7;

    if(fichero == 0)
        cargarPly("peon.ply",c1,c2,c3);
    else if(fichero == 1)
        cargarPly("perfil1.ply",c1,c2,c3);
    else if(fichero == 2)
        cargarPly("perfil2.ply",c1,c2,c3);
    else if(fichero == 3)
        cargarPly("perfil3.ply",c1,c2,c3);
    else if(fichero == 4)
        cargarPly("perfil4.ply",c1,c2,c3);
    else if(fichero == 5)
        cargarPly("perfil5.ply",c1,c2,c3);
    else if(fichero == 6)
        activo = false;
}

void ObjetoR::cambiarColor(float color1, float color2, float color3)
{
    c1 = color1;
    c2 = color2;
    c3 = color3;

}


void ObjetoR::draw()
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
