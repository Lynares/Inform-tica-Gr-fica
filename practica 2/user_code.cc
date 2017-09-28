//**************************************************************************
// Codigo del usuario
//
// Domingo Martin Perandres 2013
//
// GPL
//**************************************************************************

#include "user_code.h"
#include <GL/gl.h>
//**************************************************************************
// Funcion para dibujar los vertices de un cubo unidad
//***************************************************************************

void draw_cube()
{
    GLfloat Vertices[8][3]= {{-0.5,-0.5,0.5},{0.5,-0.5,0.5},{0.5,0.5,0.5},{-0.5,0.5,0.5},{-0.5,-0.5,-0.5},{0.5,-0.5,-0.5},{0.5,0.5,-0.5},{-0.5,0.5,-0.5}};

    glColor3f(0,1,0);
    glPointSize(4);

    glBegin(GL_POINTS);
    for (unsigned i=0;i<8;i++){
        glVertex3fv((GLfloat *) &Vertices[i]);
        }
    glEnd();
}

//**************************************************************************
// Funcion para dibujar vertices
//***************************************************************************

void draw_vertices(vector<_vertex3f> vertices,float color1,float color2,float color3)
{
    glColor3f(color1,color2,color3);

    glPointSize(4);

    glBegin(GL_POINTS);
    for (int i=0;i<vertices.size();i++)
        glVertex3f(vertices[i].x,vertices[i].y,vertices[i].z);
    glEnd();

}
void draw_vertices_Mitad(vector<_vertex3f> vertices,float color1,float color2,float color3)
{
    glColor3f(color1,color2,color3);

    glPointSize(4);

    glBegin(GL_POINTS);
    for (int i=0;i<vertices.size();i++){
        if(vertices[i].y>0){
            glVertex3f(vertices[i].x,vertices[i].y,vertices[i].z);
        }
    }
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
void draw_alambre_Mitad(vector<_vertex3f> vertices,vector<Cara> caras,float color1,float color2,float color3)
{
    glColor3f(color1,color2,color3);

    glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);

    glBegin(GL_TRIANGLES);
    for (int i=0;i<caras.size();i++){
        if(vertices[caras[i].a].y >0 && vertices[caras[i].b].y >0 && vertices[caras[i].c].y >0 ){
            glVertex3f(vertices[caras[i].a].x,vertices[caras[i].a].y,vertices[caras[i].a].z);
            glVertex3f(vertices[caras[i].b].x,vertices[caras[i].b].y,vertices[caras[i].b].z);
            glVertex3f(vertices[caras[i].c].x,vertices[caras[i].c].y,vertices[caras[i].c].z);
        }
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
void draw_solido_Cuatro(vector<_vertex3f> vertices,vector<Cara> caras)
{

    glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);

    glBegin(GL_TRIANGLES);
    for (int i=0;i<caras.size();i++){
        if(vertices[caras[i].a].y >0 && vertices[caras[i].b].y >0 && vertices[caras[i].c].y >0 && vertices[caras[i].a].x <0 && vertices[caras[i].b].x <0 && vertices[caras[i].c].x <0 &&
                 vertices[caras[i].a].z <0 && vertices[caras[i].b].z <0 && vertices[caras[i].c].z <0){
            glColor3f(0.5,1,0);//Verde
            glVertex3f(vertices[caras[i].a].x,vertices[caras[i].a].y,vertices[caras[i].a].z);
            glVertex3f(vertices[caras[i].b].x,vertices[caras[i].b].y,vertices[caras[i].b].z);
            glVertex3f(vertices[caras[i].c].x,vertices[caras[i].c].y,vertices[caras[i].c].z);

        }else if(vertices[caras[i].a].y >0 && vertices[caras[i].b].y >0 && vertices[caras[i].c].y >0 && vertices[caras[i].a].x <0 && vertices[caras[i].b].x <0 && vertices[caras[i].c].x <0 &&
                  vertices[caras[i].a].z >0 && vertices[caras[i].b].z >0 && vertices[caras[i].c].z >0){
            glColor3f(0,0,1);//Azul
            glVertex3f(vertices[caras[i].a].x,vertices[caras[i].a].y,vertices[caras[i].a].z);
            glVertex3f(vertices[caras[i].b].x,vertices[caras[i].b].y,vertices[caras[i].b].z);
            glVertex3f(vertices[caras[i].c].x,vertices[caras[i].c].y,vertices[caras[i].c].z);

        }else if(vertices[caras[i].a].y >0 && vertices[caras[i].b].y >0 && vertices[caras[i].c].y >0 && vertices[caras[i].a].x >0 && vertices[caras[i].b].x >0 && vertices[caras[i].c].x >0 &&
                  vertices[caras[i].a].z >0 && vertices[caras[i].b].z >0 && vertices[caras[i].c].z >0){
            glColor3f(1,0,0);//Rojo
            glVertex3f(vertices[caras[i].a].x,vertices[caras[i].a].y,vertices[caras[i].a].z);
            glVertex3f(vertices[caras[i].b].x,vertices[caras[i].b].y,vertices[caras[i].b].z);
            glVertex3f(vertices[caras[i].c].x,vertices[caras[i].c].y,vertices[caras[i].c].z);

        }else if(vertices[caras[i].a].y >0 && vertices[caras[i].b].y >0 && vertices[caras[i].c].y >0 && vertices[caras[i].a].x >0 && vertices[caras[i].b].x >0 && vertices[caras[i].c].x >0 &&
                  vertices[caras[i].a].z <0 && vertices[caras[i].b].z <0 && vertices[caras[i].c].z <0){
            glColor3f(1,1,0);//Amarillo
            glVertex3f(vertices[caras[i].a].x,vertices[caras[i].a].y,vertices[caras[i].a].z);
            glVertex3f(vertices[caras[i].b].x,vertices[caras[i].b].y,vertices[caras[i].b].z);
            glVertex3f(vertices[caras[i].c].x,vertices[caras[i].c].y,vertices[caras[i].c].z);

        }else if(vertices[caras[i].a].y >0 && vertices[caras[i].b].y >0 && vertices[caras[i].c].y >0 ){
            glColor3f(0,0,0);//Negro
            glVertex3f(vertices[caras[i].a].x,vertices[caras[i].a].y,vertices[caras[i].a].z);
            glVertex3f(vertices[caras[i].b].x,vertices[caras[i].b].y,vertices[caras[i].b].z);
            glVertex3f(vertices[caras[i].c].x,vertices[caras[i].c].y,vertices[caras[i].c].z);
         }



    }
    glEnd();
}
void draw_solido_Mitad(vector<_vertex3f> vertices,vector<Cara> caras,float color1,float color2,float color3)
{
    glColor3f(color1,color2,color3);

    glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);

    glBegin(GL_TRIANGLES);
    for (int i=0;i<caras.size();i++){
        if(vertices[caras[i].a].y >0 && vertices[caras[i].b].y >0 && vertices[caras[i].c].y >0 ){
        glVertex3f(vertices[caras[i].a].x,vertices[caras[i].a].y,vertices[caras[i].a].z);
        glVertex3f(vertices[caras[i].b].x,vertices[caras[i].b].y,vertices[caras[i].b].z);
        glVertex3f(vertices[caras[i].c].x,vertices[caras[i].c].y,vertices[caras[i].c].z);
        }
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
             glColor3f(color1,color1,color3);

        glVertex3f(vertices[caras[i].a].x,vertices[caras[i].a].y,vertices[caras[i].a].z);
        glVertex3f(vertices[caras[i].b].x,vertices[caras[i].b].y,vertices[caras[i].b].z);
        glVertex3f(vertices[caras[i].c].x,vertices[caras[i].c].y,vertices[caras[i].c].z);
    }
    glEnd();
}
void draw_ajedrez_Mitad(vector<_vertex3f> vertices,vector<Cara> caras,float color1,float color2,float color3)
{

    glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);

    glBegin(GL_TRIANGLES);
    for (int i=0;i<caras.size();i++){
        if(i%2 == 0)
            glColor3f(color1,color2,color3);
        else
             glColor3f(color1,color1,color3);
        if(vertices[caras[i].a].y >0 && vertices[caras[i].b].y >0 && vertices[caras[i].c].y >0 ){
            glVertex3f(vertices[caras[i].a].x,vertices[caras[i].a].y,vertices[caras[i].a].z);
            glVertex3f(vertices[caras[i].b].x,vertices[caras[i].b].y,vertices[caras[i].b].z);
            glVertex3f(vertices[caras[i].c].x,vertices[caras[i].c].y,vertices[caras[i].c].z);
        }
    }
    glEnd();
}
