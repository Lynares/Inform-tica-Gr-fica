//**************************************************************************
// Práctica 1
//
// Domingo Martin Perandres 2013
//
// GPL
//**************************************************************************

#include <GL/gl.h>
#include <vector>
#include "vertex.h"
#include "cara.h"
using namespace std;

void draw_cube();

void draw_vertices(vector<_vertex3f> Vertices, float color1, float color2, float color3);
void draw_vertices_Mitad(vector<_vertex3f> vertices,float color1,float color2,float color3);

void draw_alambre(vector<_vertex3f> vertices,vector<Cara> caras,float color1,float color2,float color3);
void draw_alambre_Mitad(vector<_vertex3f> vertices,vector<Cara> caras,float color1,float color2,float color3);

void draw_solido(vector<_vertex3f> vertices,vector<Cara> caras,float color1,float color2,float color3);
void draw_solido_Mitad(vector<_vertex3f> vertices,vector<Cara> caras,float color1,float color2,float color3);
void draw_solido_Cuatro(vector<_vertex3f> vertices,vector<Cara> caras);
void draw_ajedrez(vector<_vertex3f> vertices,vector<Cara> caras,float color1,float color2,float color3);
void draw_ajedrez_Mitad(vector<_vertex3f> vertices,vector<Cara> caras,float color1,float color2,float color3);
