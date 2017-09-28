#include "jerarquico.h"

Jerarquico::Jerarquico()
{
    activo = true;

    modo = 2;

    beethoven.cargarPly("beethoven.ply",0,0,1);
    beethoven.cambiarModo(2);
    beethoven.activar();

    cubo.cargarPly("cubo.ply",0,0,1);
    cubo.cambiarModo(2);
    cubo.activar();

    cilindro.cargarPly("f.ply",0.1,0.1,0.1);
    cilindro.cambiarModo(2);
    cilindro.activar();

    perfilU1.cargarPly("perfilU1.ply",0.3,0.4,0.5);
    perfilU1.cambiarModo(2);
    perfilU1.activar();

    perfilU2.cargarPly("perfilU2.ply",0.7,0.3,0.2);
    perfilU2.cambiarModo(2);
    perfilU2.activar();

    desplazamiento = 0;
    giro = 0;
    elevacion = 0;

    velDesplazamiento = 0.1;
    velGiro = 1;
    velElevacion = 1;
}

void Jerarquico::rail()
{
    glPushMatrix();
    glScalef(20,1,1);
    cubo.cambiarColor(0.2,0.3,0.4);
    cubo.draw();
    glPopMatrix();
}

void Jerarquico::railes()
{
    glPushMatrix();
    glTranslatef(0.0,0.0,1.5);
    rail();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.0,0.0,-2.5);
    rail();
    glPopMatrix();
}

void Jerarquico::base()
{
    glTranslatef(0,1.5,3.5);
    glRotatef(180,1,0,0);
    perfilU1.draw();
}

void Jerarquico::cuerpo()
{
    glTranslatef(-2.5,0,-2.5);
    perfilU2.draw();
}

void Jerarquico::brazo()
{
    glPushMatrix();
    glTranslatef(0,0.5,0);
    glScalef(1,5,1);
    cilindro.cambiarColor(1,1,0);
    cilindro.draw();
    glPopMatrix();

    glTranslatef(-0.5,-0.5,-1.5);
    glScalef(20.5,1,3);
    cubo.cambiarColor(0.3,0.4,0.5);
    cubo.draw();
}

void Jerarquico::cable()
{
    glTranslatef(0,-5,0);
    glScalef(0.1,5,0.1);
    cilindro.cambiarColor(0.1,0.1,0.1);
    cilindro.draw();
}

void Jerarquico::mercancia()
{
    glPushMatrix();
    glTranslatef(0,-1.5,0);
    beethoven.cambiarColor(1,0.5,0.5);
    beethoven.draw();
    glPopMatrix();

    glTranslatef(-1,-1,-1);
    glScalef(2,2,2);
    cubo.cambiarColor(0.6,0.4,1);
    cubo.draw();
}

void Jerarquico::eje()
{
    glTranslatef(-3.625,-0.75,-0.125);
    glScalef(0.25,2.5,0.25);
    cubo.draw();
}

void Jerarquico::cableMercancia()
{
    glPushMatrix();
    cable();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0,-6,0);
    mercancia();
    glPopMatrix();
}

void Jerarquico::brazoCableMercancia()
{
    glPushMatrix();
    glTranslatef(3.5,0,-1.125);
    glScalef(1,1,2.25);
    glRotatef(90,1,0,0);
    eje();
    glPopMatrix();

    glPushMatrix();
    brazo();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(20,0,0);
    glRotatef(-elevacion,0,0,1);
    cableMercancia();
    glPopMatrix();

}

void Jerarquico::cuerpoBrazoCableMercancia()
{
    glPushMatrix();
    glTranslatef(3.5,0,0);
    eje();
    glPopMatrix();

    glPushMatrix();
    cuerpo();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-1,3,0);
    glRotatef(elevacion,0,0,1);
    brazoCableMercancia();
    glPopMatrix();
}

void Jerarquico::baseCuerpoBrazoCableMercancia()
{
    glPushMatrix();
    base();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(3.5,1.5,0);
    glRotatef(giro,0,1,0);
    cuerpoBrazoCableMercancia();
    glPopMatrix();
}

void Jerarquico::grua()
{
    glPushMatrix();
    railes();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(desplazamiento,0,0);
    baseCuerpoBrazoCableMercancia();
    glPopMatrix();
}

void Jerarquico::avanzar()
{
    if(desplazamiento+velDesplazamiento < 13.0)
    {
        desplazamiento+=velDesplazamiento;
        draw();
    }
}

void Jerarquico::retroceder()
{
    if(desplazamiento-velDesplazamiento > 0.0)
    {
        desplazamiento-=velDesplazamiento;
        draw();
    }
}

void Jerarquico::girarI()
{
    giro += velGiro;
    giro = giro%360;
    draw();
}

void Jerarquico::girarD()
{
    giro -= velGiro;
    giro = giro%360;
    draw();
}

void Jerarquico::elevar()
{
    if(elevacion+velElevacion < 65)
    {
        elevacion+=velElevacion;
        draw();
    }
}

void Jerarquico::bajar()
{
    if(elevacion-velElevacion > 0)
    {
        elevacion-=velElevacion;
        draw();
    }
}
void Jerarquico::cambiarModo(int m){

    cubo.cambiarModo(m);
    cilindro.cambiarModo(m);
    perfilU1.cambiarModo(m);
    perfilU2.cambiarModo(m);
    beethoven.cambiarModo(m);
}
void Jerarquico::incrementarVelAvance()
{
    if(velDesplazamiento < 0.9)
        velDesplazamiento+=0.1;
}

void Jerarquico::decrementarVelAvance()
{
    if(velDesplazamiento > 0.2)
        velDesplazamiento-=0.1;
}

void Jerarquico::incrementarVelGiro()
{
    if(velGiro < 10)
        velGiro+=1;
}

void Jerarquico::decrementarVelGiro()
{
    if(velGiro > 1)
       velGiro-=1;
}

void Jerarquico::incrementarVelElevacion()
{
    if(velElevacion < 10)
        velElevacion+=1;
}

void Jerarquico::decrementarVelElevacion()
{
    if(velElevacion > 1)
        velElevacion-=1;
}

void Jerarquico::cambiarModo()
{
    modo++;
    modo = modo%4;
    cubo.cambiarModo(modo);
    perfilU1.cambiarModo(modo);
    perfilU2.cambiarModo(modo);
    cilindro.cambiarModo(modo);
    beethoven.cambiarModo(modo);
}


void Jerarquico::draw()
{
    if(activo)
    {
        glPushMatrix();
        grua();
        glPopMatrix();
    }
}
