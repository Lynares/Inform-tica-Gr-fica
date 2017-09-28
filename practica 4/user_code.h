//**************************************************************************
// Práctica 1
//**********************************************************************

#include <GL/gl.h>
#include "stdlib.h"


//**************************************************************************
// estructuras de datos para los modelos
//**************************************************************************

struct vertices
{
float coord[3];
};


struct caras
{
int ind_c[3];
};

struct solido{
int n_v;
int n_c;
vertices *ver;
caras    *car;
};


//**************************************************************************
// funciones para construir modelos sólidos poligonales
//**************************************************************************

void construir_cubo(float tam, solido *cubo);
void construir_piramide(float tam, float al, solido *piramide);

//**************************************************************************
// funciones de visualización
//**************************************************************************

void draw_puntos(vertices *ver, int n_v, int grosor)
{
    glColor3f(0.0,0.0,1.0);

    glPointSize(grosor);

    glBegin(GL_POINTS);
    for (int i=0;i<n_v;i++)
        glVertex3f(ver[i],ver[i+1],ver[i+2]);
    glEnd();
}
void draw_arista_solido(solido *malla, float r, float g, float b, int modo, int grosor)
{
    glColor3f(r,g,b);

    if(modo == 0)
	glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
    else
        glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);

    glBegin(GL_TRIANGLES);
    for (int i=0;i<caras.size();i++){
        glVertex3f(malla,malla,malla);
        glVertex3f(malla,malla,malla);
        glVertex3f(malla,malla,malla);
    }
    glEnd();
}
void draw_solido_ajedrez(solido *malla, float r1, float g1, float b1, float r2, float g2, float b2)
{
    glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);

    glBegin(GL_TRIANGLES);
    for (int i=0;i<caras.size();i++)
    {
        if(i%2 == 0)
            glColor3f(r1,g1,b1);
        else
             glColor3f(r2,g2,b2);

        glVertex3f(malla,malla,malla);
        glVertex3f(malla,malla,malla);
        glVertex3f(malla,malla,malla);
    }
    glEnd();
}


