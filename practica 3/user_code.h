#ifndef USER_CODE_H
#define USER_CODE_H

#include <vector>
#include "vertex.h"
#include "cara.h"

void draw_vertices(vector<_vertex3f> vertices, float color1, float color2, float color3);

void draw_alambre(vector<_vertex3f> vertices,vector<Cara> caras,float color1, float color2, float color3);

void draw_solido(vector<_vertex3f> vertices,vector<Cara> caras, float color1, float color2, float color3);

void draw_ajedrez(vector<_vertex3f> vertices,vector<Cara> caras,float color1, float color2, float color3);

#endif
