
#include "user_code.h"
#include <GL/gl.h>

void draw_vertices(vector<_vertex3f> vertices,float color1,float color2,float color3)
{
    glColor3f(color1,color2,color3);

    glPointSize(4);

    glBegin(GL_POINTS);
    for (int i=0;i<vertices.size();i++)
        glVertex3f(vertices[i].x,vertices[i].y,vertices[i].z);
    glEnd();

}

void draw_alambre(vector<_vertex3f> vertices,vector<Cara> caras,float color1,float color2,float color3)
{
    glColor3f(color1,color2,color3);

    glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);

    glBegin(GL_TRIANGLES);
    for (int i=0;i<caras.size();i++){
        glVertex3f(vertices[caras[i].a].x,vertices[caras[i].a].y,vertices[caras[i].a].z);
        glVertex3f(vertices[caras[i].b].x,vertices[caras[i].b].y,vertices[caras[i].b].z);
        glVertex3f(vertices[caras[i].c].x,vertices[caras[i].c].y,vertices[caras[i].c].z);
    }
    glEnd();
}

void draw_solido(vector<_vertex3f> vertices,vector<Cara> caras,float color1,float color2,float color3)
{
    glColor3f(color1,color2,color3);

    glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);

    glBegin(GL_TRIANGLES);
    for (int i=0;i<caras.size();i++){
        glVertex3f(vertices[caras[i].a].x,vertices[caras[i].a].y,vertices[caras[i].a].z);
        glVertex3f(vertices[caras[i].b].x,vertices[caras[i].b].y,vertices[caras[i].b].z);
        glVertex3f(vertices[caras[i].c].x,vertices[caras[i].c].y,vertices[caras[i].c].z);
    }
    glEnd();
}

void draw_ajedrez(vector<_vertex3f> vertices,vector<Cara> caras,float color1,float color2,float color3)
{
    glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);

    glBegin(GL_TRIANGLES);
    for (int i=0;i<caras.size();i++)
    {
        if(i%2 == 0)
            glColor3f(color1,color2,color3);
        else
             glColor3f(color3,color2,color1);

        glVertex3f(vertices[caras[i].a].x,vertices[caras[i].a].y,vertices[caras[i].a].z);
        glVertex3f(vertices[caras[i].b].x,vertices[caras[i].b].y,vertices[caras[i].b].z);
        glVertex3f(vertices[caras[i].c].x,vertices[caras[i].c].y,vertices[caras[i].c].z);
    }
    glEnd();
}

