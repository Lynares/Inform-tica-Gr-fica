#include "figura.h"
#include "vertex.h"
#include "file_ply_stl.h"
#include <math.h>

#define PI 3.141592
/*
  *Constructor por defecto, nos carga uno de los tres
  *ply de la primera práctica
  *
  */
Figura::Figura(){
    visualizar = false;
    modo = 1;
    fichero=1;

    cargarPly();
}
/*
  *Constructor para crear una figura por revolucion.
  *El parámetro que le pasamos es el número de lados que queremos generarle,
  *de modo que si queremos un determinado numero de lados podemos hacerlo.
  *
  */
Figura::Figura(int l){
    visualizar = true;
    modo = 1;
    ficheroPerfil = 0;
    lados = l;
    ladosMostrados = 0;
    normales = false;
    cargarPlyPerfil();
}
/*
  *Método para cargar un fichero ply de la primera práctica
  *
  *
  */
void Figura::cargarPly(){
     char *ply;
     vertices.clear();
     caras.clear();

     vector<float> v;
     vector<int> c;

     if(fichero == 0)
         ply= "ant.ply";
     if(fichero == 1)
         ply= "beethoven.ply";
     if(fichero == 2)
         ply= "big_dodge.ply";

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
/*
  *Método para cargar un ply de un perfil, que dará como resultado una figura generada
  *por revolución
  *
  */
void Figura::cargarPlyPerfil(){
    char *ply;

    vertices.clear();
    caras.clear();

    tapaSuperior = false;
    tapaInferior = false;

    vector<float> perfil;
    vector<int> c;

    if(ficheroPerfil == 0)
        ply= "perfil1.ply";
    if(ficheroPerfil == 1)
        ply= "perfil2.ply";
    if(ficheroPerfil == 2)
        ply= "perfil3.ply";
    if(ficheroPerfil == 3)
        ply= "perfil4.ply";


    _file_ply f;

    f.open(ply);
    f.read(perfil,c);
    f.close();

    _vertex3f vertice;

    for(int i=0; i < perfil.size();i+=3){
        vertice(perfil[i],perfil[i+1],perfil[i+2]);

        if(i == 0){
            if(vertice.x == 0){
                tapaInferior = true;
                tapaI = vertice;
            }else
                vertices.push_back(vertice);
        }

        if(i != 0)
            vertices.push_back(vertice);
    }

    if(vertices[vertices.size()-1].x == 0){
        tapaSuperior = true;
        tapaS = vertices[vertices.size()-1];
        vertices.pop_back();
    }

    tamPerfil = vertices.size();

    generarVertices();
    generarCaras();
}
/*
  *Método para dibujar vertices.
  *
  *
  */
void Figura::draw_vertices(){
    glColor3f(0,0,1);

    glPointSize(4);

    glBegin(GL_POINTS);
    for (int i=0;i<caras.size();i++)
        glVertex3f(vertices[caras[i].a].x,vertices[caras[i].b].y,vertices[caras[i].c].z);
    glEnd();

}
/*
  *Método para dibujar en alambre
  *
  *
  */
void Figura::draw_alambre(){
    glColor3f(0,0,1);

    glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);

    glBegin(GL_TRIANGLES);
    for (int i=0;i<caras.size();i++){
        glVertex3f(vertices[caras[i].a].x,vertices[caras[i].a].y,vertices[caras[i].a].z);
        glVertex3f(vertices[caras[i].b].x,vertices[caras[i].b].y,vertices[caras[i].b].z);
        glVertex3f(vertices[caras[i].c].x,vertices[caras[i].c].y,vertices[caras[i].c].z);
    }
    glEnd();
}
/*
  *Método para dibujar en solido
  *
  *
  */
void Figura::draw_solido(){
    glColor3f(0,0,1);

    glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);

    glBegin(GL_TRIANGLES);
    for (int i=0;i<caras.size();i++){
        glVertex3f(vertices[caras[i].a].x,vertices[caras[i].a].y,vertices[caras[i].a].z);
        glVertex3f(vertices[caras[i].b].x,vertices[caras[i].b].y,vertices[caras[i].b].z);
        glVertex3f(vertices[caras[i].c].x,vertices[caras[i].c].y,vertices[caras[i].c].z);
    }
    glEnd();
}
/*
  *Método para dibujar en ajedrez.
  *
  *
  */
void Figura::draw_ajedrez(){
    glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);

    glBegin(GL_TRIANGLES);
    for (int i=0;i<caras.size();i++){
        if(i%2 == 0)
            glColor3f(1,0,1);
        else
            glColor3f(0,1,0);

        glVertex3f(vertices[caras[i].a].x,vertices[caras[i].a].y,vertices[caras[i].a].z);
        glVertex3f(vertices[caras[i].b].x,vertices[caras[i].b].y,vertices[caras[i].b].z);
        glVertex3f(vertices[caras[i].c].x,vertices[caras[i].c].y,vertices[caras[i].c].z);
    }
    glEnd();
}
/*
  *Método para dibujar las normales.
  *
  *
  */
void Figura::draw_normales(){
    glColor3f(0,1,0.5);

    glBegin(GL_LINES);
    for (int i=0;i < puntoMedioCaras.size();i++){
        glVertex3f(puntoMedioCaras[i].x,puntoMedioCaras[i].y,puntoMedioCaras[i].z);
        glVertex3f(puntoMedioCaras[i].x+normalesCaras[i].x,puntoMedioCaras[i].y+normalesCaras[i].y,puntoMedioCaras[i].z+normalesCaras[i].z);
    }
    glEnd();

        glColor3f(1,0.7,0.1);

    glBegin(GL_LINES);
    for (int j=0;j < normalesVertices.size();j++){
        glVertex3f(vertices[j].x,vertices[j].y,vertices[j].z);
        glVertex3f(vertices[j].x+normalesVertices[j].x,vertices[j].y+normalesVertices[j].y,vertices[j].z+normalesVertices[j].z);
    }
    glEnd();
}
/*
  *Método para generar los vertices de una figura generada por revolución
  *
  *
  */
void Figura::generarVertices(){
//Antes ibamos de 0 a 360 ahora de 30 a 150 y de 30 a 210.
    double grados = 150/lados*1.0;

    _vertex3f vertice;

    for(int i=0; i < lados-1; i++){
        for(int j=0; j < tamPerfil; j++){

            vertice.x = vertices[i*tamPerfil+j].x*cos(30) + vertices[i*tamPerfil+j].z*sin(30);
            vertice.y = vertices[i*tamPerfil+j].y;
            vertice.z = vertices[i*tamPerfil+j].x*(-1)*sin(grados*PI/180.0) + vertices[i*tamPerfil+j].z*cos(30);

            vertices.push_back(vertice);
        }
    }

    if(tapaInferior)
        vertices.push_back(tapaI);
    if(tapaSuperior)
        vertices.push_back(tapaS);

}
/*
  *Método para generar una cara de una figura generada por revolución
  *
  *
  */
void Figura::generarCara(int a,int b, int c){
    Cara cara;

    cara.a = a;
    cara.b = b;
    cara.c = c;

    caras.push_back(cara);
}
/*
  *Método para generar caras de una figura generada por revolución a partir
  *del método anterior generarCara
  *
  */
void Figura::generarCaras(){
    for(int i=0; i < tamPerfil-1;i++){
        for(int j=0; j < lados-ladosMostrados; j++){
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

    calcularPuntoMedioCaras();
}
/*
  *Método para generar la tapa inferior de una figura generada por revolución
  *
  *
  */
void Figura::generarTapaInferior(){
    int modulo;

    if(tapaSuperior)
        modulo = vertices.size()-2;
    else
        modulo = vertices.size()-1;

    for(int i=0; i < lados-ladosMostrados; i++)
        generarCara(modulo,(i*tamPerfil + tamPerfil)%modulo,i*tamPerfil);
}
/*
  *Método para generar la tapa superior de una figura generada por revolución
  *
  *
  */
void Figura::generarTapaSuperior(){
    int modulo;

    if(tapaInferior)
        modulo = vertices.size()-2;
    else
        modulo = vertices.size()-1;


    for(int i=0; i < lados-ladosMostrados; i++)
        generarCara(vertices.size()-1,i*tamPerfil + tamPerfil-1,((tamPerfil-1)+(i+1)*tamPerfil)%modulo);
}
/*
  *Método para calcular las normales de las caras
  *
  *
  */
void Figura::generarNormalesCaras(){
    normalesCaras.clear();

    _vertex3f ab;
    _vertex3f bc;

    _vertex3f n;

    for(int i=0; i < caras.size(); i++){
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
/*
  *Método para generar las normales de los vertices
  *
  *
  */
void Figura::generarNormalesVertices(){
    normalesVertices.clear();

    _vertex3f n(0,0,0);

    for(int i=0; i < vertices.size(); i++)
       normalesVertices.push_back(n);

    for(int j=0; j < caras.size(); j++){
        normalesVertices[caras[j].a] += normalesCaras[j];
        normalesVertices[caras[j].b] += normalesCaras[j];
        normalesVertices[caras[j].c] += normalesCaras[j];
    }

    for(int k=0; k < normalesVertices.size(); k++)
        normalesVertices[k] = normalesVertices[k].normalize();
}
/*
  *Método para calcular el punto medio de las caras
  *
  *
  */

void Figura::calcularPuntoMedioCaras(){

    puntoMedioCaras.clear();

    _vertex3f p;

    for (int i=0;i<caras.size();i++){
        p.x = vertices[caras[i].a].x;
        p.x += vertices[caras[i].b].x;
        p.x += vertices[caras[i].c].x;

        p.y = vertices[caras[i].a].y;
        p.y += vertices[caras[i].b].y;
        p.y += vertices[caras[i].c].y;

        p.z = vertices[caras[i].a].z;
        p.z += vertices[caras[i].b].z;
        p.z += vertices[caras[i].c].z;

        p.x = p.x / 3.0;
        p.y = p.y / 3.0;
        p.z = p.z / 3.0;

        puntoMedioCaras.push_back(p);
    }
}

/*
  *Método para cambiar de fichero ply, nor referimos
  *a beethoven, hormiga y coche, también podremos no visualizarlo
  *
  */
void Figura::cambiarPly(){
    visualizar = true;

    fichero = (fichero+1)%4;

    if(fichero == 3)
        visualizar = false;
    else
        cargarPly();
}
/*
  *Método para cambiar de perfil de entre los ficheros ply creados para
  *generarlos por revolución
  *
  */
void Figura::cambiarPlyPerfil(){
    visualizar = true;

    ficheroPerfil = (ficheroPerfil+1)%4;

    if(ficheroPerfil == 6)
        visualizar = false;
    else
        cargarPlyPerfil();
}
/*
  *Método para mostrar las partes, con esto me refiero a los lados que anteriormente
  *le pasamos como parámetro al constructor de Figura
  *
  */
void Figura::mostrarLados(){
    ladosMostrados++;

    ladosMostrados = ladosMostrados%(lados+1);

    cargarPlyPerfil();
}
/*
*Método para cambiar si se muestran las normales o no.
*
*
*/
void Figura::cambiarNormales(){
    if(normales)
           normales=false;
    else
           normales=true;
}
/*
*Método para cambiar el modo de dibujo.
*
*
*/
void Figura::draw(){
  if(visualizar){
      if(modo == 0)
          draw_vertices();
      if(modo == 1)
          draw_alambre();
      if(modo == 2)
          draw_solido();
      if(modo == 3)
          draw_ajedrez();
      if(normales)
          draw_normales();
  }
}
