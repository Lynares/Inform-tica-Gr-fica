//**************************************************************************
// Práctica 1
//
// Domingo Martin Perandres 2013-2016
//
// GPL
//**************************************************************************

#include "stdlib.h"
#include "stdio.h"
#include "vertex.h"
#include "objetos.h"
#include <GL/glut.h>
#include <ctype.h>
#include <cmath>

const char* coche = "big_dodge";
const char* hormiga = "ant";
const char* beethoven = "beethoven";
const char* perfil = "perfil";

Objeto plyC(coche);
Objeto plyH(hormiga);
Objeto plyB(beethoven);

ObjetoR pNegro(perfil, 100, true);
ObjetoR_text pMadera(perfil, 100,true);

Jerarquico modelo;

int tipo = 0;//puntos, aristas...
int objeto = 0;//cubo, piramide, coche, etc
int contador = 0;
GLfloat light_position[4] = {1.0,0,0.0,0.0}; //Foco desde la derecha
GLfloat light_position2[4] = {0.0,1.0,0.0,0.0}; //Foco desde arriba
int posicionLuz = 0;
ObjetoR_text lata("lata-pcue", 20, false);
ObjetoR_text lata_inf("lata-pinf", 20, false);
ObjetoR_text lata_sup("lata-psup", 20, false);

int accion = 0;
bool reposo = true;

// tamaño de los ejes
const int AXIS_SIZE=5000;

// variables que definen la posicion de la camara en coordenadas polares
GLfloat Observer_distance;
GLfloat Observer_angle_x;
GLfloat Observer_angle_y;

// variables que controlan la ventana y la transformacion de perspectiva
GLfloat Window_width,Window_height,Front_plane,Back_plane;

// variables que determninan la posicion y tamaño de la ventana X
int UI_window_pos_x=50,UI_window_pos_y=50,UI_window_width=500,UI_window_height=500;

//**************************************************************************
//
//***************************************************************************

void idle()
{
/*    if(reposo){
        if(accion == 0)
            modelo.avanzar();
        if(accion == 1)
            modelo.retroceder();
        if(accion == 2)
            modelo.elevar();
        if(accion == 3)
            modelo.bajar();
        if(accion == 4)
            modelo.girarD();
        if(accion == 5)
            modelo.girarI();

    accion = accion%6;

    glutPostRedisplay();
    }*/
}

void clear_window()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
}

//**************************************************************************
// Funcion para definir la transformación de proyeccion
//***************************************************************************

void change_projection()
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    // formato(x_minimo,x_maximo, y_minimo, y_maximo,Front_plane, plano_traser)
    //  Front_plane>0  Back_plane>PlanoDelantero)
    glFrustum(-Window_width,Window_width,-Window_height,Window_height,Front_plane,Back_plane);
}

//**************************************************************************
// Funcion para definir la transformación de vista (posicionar la camara)
//***************************************************************************

void change_observer()
{
    // posicion del observador
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glTranslatef(0,0,-Observer_distance);
    glRotatef(Observer_angle_x,1,0,0);
    glRotatef(Observer_angle_y,0,1,0);
}

//**************************************************************************
// Funcion que dibuja los ejes utilizando la primitiva grafica de lineas
//***************************************************************************

void draw_axis()
{
    glBegin(GL_LINES);
    // eje X, color rojo
    glColor3f(1,0,0);
    glVertex3f(-AXIS_SIZE,0,0);
    glVertex3f(AXIS_SIZE,0,0);
    // eje Y, color verde
    glColor3f(0,1,0);
    glVertex3f(0,-AXIS_SIZE,0);
    glVertex3f(0,AXIS_SIZE,0);
    // eje Z, color azul
    glColor3f(0,0,1);
    glVertex3f(0,0,-AXIS_SIZE);
    glVertex3f(0,0,AXIS_SIZE);
    glEnd();
}

//**************************************************************************
// Funcion que dibuja los objetos
//***************************************************************************
void luces(){
	
	GLfloat color_luz_2[4] = {0.0,1.0,0.0,0.0};
	
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glLightfv(GL_LIGHT0, GL_POSITION, light_position); //Posiciones de la luz declaradas globales
	glLightfv(GL_LIGHT1, GL_POSITION, light_position2);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, color_luz_2);
	glLightfv(GL_LIGHT1, GL_SPECULAR, color_luz_2);

}

void draw_objects()
{

	if(tipo == 0){

		if(objeto == 0){
			if(contador==0)
			plyB.draw_iluminacion_suave();
			else if(contador==1)
			plyB.draw_iluminacion_plana();
			else if(contador==2)
			plyB.draw_puntos(0,0,1,3);
			else if(contador==3)
			plyB.draw_aristas(0,0,1,3);
			else if(contador==4)
			plyB.draw_solido(0,0,1);
			else if(contador==5)
			plyB.draw_solido_ajedrez(0,0,1,0,0,0);
		 }else if(objeto == 1){
			if(contador==0)
			plyC.draw_iluminacion_suave();
			else if(contador==1)
			plyC.draw_iluminacion_plana();
			else if(contador==2)
			plyC.draw_puntos(0,0,1,3);
			else if(contador==3)
			plyC.draw_aristas(0,0,1,3);
			else if(contador==4)
			plyC.draw_solido(0,0,1);
			else if(contador==5)
			plyC.draw_solido_ajedrez(0,0,1,0,0,0);
		}else if(objeto == 2){
			if(contador==0)
			plyH.draw_iluminacion_suave();
			else if(contador==1)
			plyH.draw_iluminacion_plana();
			else if(contador==2)
			plyH.draw_puntos(0,0,1,3);
			else if(contador==3)
			plyH.draw_aristas(0,0,1,3);
			else if(contador==4)
			plyH.draw_solido(0,0,1);
			else if(contador==5)
			plyH.draw_solido_ajedrez(0,0,1,0,0,0);
		}
	}else if(tipo == 1){
			if(contador==0)
			pNegro.draw_iluminacion_suave();
			else if(contador==1)
			pNegro.draw_iluminacion_plana();
			else if(contador==2)
			pNegro.draw_puntos(0,0,1,3);
			else if(contador==3)
			pNegro.draw_aristas(0,0,1,3);
			else if(contador==4)
			pNegro.draw_solido(0,0,1);
			else if(contador==5)
			pNegro.draw_solido_ajedrez(0,0,1,0,0,0);
		
	}else if(tipo == 2){
		pMadera.draw_textura("text-madera.jpg");
	}else if(tipo == 3){
		if(objeto==0)
			pMadera.draw_textura_iluminacion_suave("text-madera.jpg");
		else 
			pMadera.draw_textura_iluminacion_plana("text-madera.jpg");
	}else if(tipo == 4){
		glPushMatrix();
		glScalef(5,5,5);
		lata.draw_textura("text-lata-1.jpg");
	    	lata_sup.draw_textura("gris.jpg");
    		lata_inf.draw_textura("gris.jpg");
		glPopMatrix();
	}
}

//**************************************************************************
//
//***************************************************************************

void draw_scene(void)
{
    clear_window();
    luces();
    change_observer();
    draw_axis();
    draw_objects();
    glutSwapBuffers();
}

//***************************************************************************
// Funcion llamada cuando se produce un cambio en el tamaño de la ventana
//
// el evento manda a la funcion:
// nuevo ancho
// nuevo alto
//***************************************************************************

void change_window_size(int Ancho1,int Alto1)
{
    change_projection();
    glViewport(0,0,Ancho1,Alto1);
    glutPostRedisplay();
}

//***************************************************************************
// Funcion llamada cuando se produce aprieta una tecla normal
//
// el evento manda a la funcion:
// codigo de la tecla
// posicion x del raton
// posicion y del raton
//***************************************************************************

void normal_keys(unsigned char Tecla1,int x,int y)
{
	if (toupper(Tecla1) == 'Q') exit(0);

	if (toupper(Tecla1) == 'L'){
		tipo = (tipo + 1) % 5; 
		draw_scene(); //tipo = 0 puntos, 1 = líneas, 2 = sólido, 3 = ajedrez
	}
	if (toupper(Tecla1) == 'C'){
		objeto = (objeto + 1) % 3; 
		draw_scene() ; 
	}
	if (toupper(Tecla1) == 'I'){
		contador = (contador + 1) % 6; 
		draw_scene() ; 
	}

/*
    if (Tecla1=='S'){modelo.cambiarModo(2); draw_scene();}
    if (Tecla1=='s'){obj1.cambiarModo(2); draw_scene();}
    if (Tecla1=='A'){modelo.cambiarModo(3); draw_scene();}
    if (Tecla1=='a'){obj1.cambiarModo(3); draw_scene();}
    if (toupper(Tecla1)=='1'){obj1.cambiarPly(); draw_scene();}
    if (toupper(Tecla1)=='2'){obj2.cambiarPly(); draw_scene();}
    if (toupper(Tecla1)=='3'){ modelo.activar(); draw_scene();}
}
    if (Tecla1=='Z'){reposo = false; modelo.avanzar(); draw_scene();}
    if (Tecla1=='z'){reposo = false; modelo.retroceder(); draw_scene();}
    if (Tecla1=='X'){reposo = false; modelo.girarD(); draw_scene();}
    if (Tecla1=='x'){reposo = false; modelo.girarI(); draw_scene();}
    if (Tecla1=='C'){reposo = false; modelo.elevar(); draw_scene();}
    if (Tecla1=='c'){reposo = false; modelo.bajar(); draw_scene();}
    if (Tecla1=='B'){reposo = false; modelo.incrementarVelAvance();}
    if (Tecla1=='b'){reposo = false; modelo.decrementarVelAvance();}
    if (Tecla1=='N'){reposo = false; modelo.incrementarVelGiro();}
    if (Tecla1=='n'){reposo = false; modelo.decrementarVelGiro();}
    if (Tecla1=='M'){reposo = false; modelo.incrementarVelElevacion();}
    if (Tecla1=='m'){reposo = false; modelo.decrementarVelElevacion();}
    if (toupper(Tecla1)=='I'){reposo = true; accion++;}
    if (toupper(Tecla1)=='+'){modelo.cambiarModo();  draw_scene();}
    if (Tecla1=='4'){obj1.cambiarModo(4); draw_scene();}
    if (Tecla1=='5'){obj1.cambiarModo(5); draw_scene();}
    if (Tecla=='-'){

    }
*/
}

//***************************************************************************
// Funcion llamada cuando se produce aprieta una tecla especial
//
// el evento manda a la funcion:
// codigo de la tecla
// posicion x del raton
// posicion y del raton

//***************************************************************************

void special_keys(int Tecla1,int x,int y)
{
    switch (Tecla1){
        case GLUT_KEY_LEFT:Observer_angle_y--;break;
        case GLUT_KEY_RIGHT:Observer_angle_y++;break;
        case GLUT_KEY_UP:Observer_angle_x--;break;
        case GLUT_KEY_DOWN:Observer_angle_x++;break;
        case GLUT_KEY_PAGE_UP:Observer_distance*=1.2;break;
        case GLUT_KEY_PAGE_DOWN:Observer_distance/=1.2;break;
        }
    glutPostRedisplay();
}

//***************************************************************************
// Funcion de incializacion
//***************************************************************************

void initialize(void)
{
    // se inicalizan la ventana y los planos de corte
    Window_width=.5;
    Window_height=.5;
    Front_plane=1;
    Back_plane=1000;

    // se inicia la posicion del observador, en el eje z
    Observer_distance=10*Front_plane;
    Observer_angle_x=0;
    Observer_angle_y=0;

    // se indica cual sera el color para limpiar la ventana	(r,v,a,al)
    // blanco=(1,1,1,1) rojo=(1,0,0,1), ...
    glClearColor(1,1,1,1);

    // se habilita el z-bufer
    glEnable(GL_DEPTH_TEST);
    change_projection();
    glViewport(0,0,UI_window_width,UI_window_height);
}

//***************************************************************************
// Programa principal
//
// Se encarga de iniciar la ventana, asignar las funciones e comenzar el
// bucle de eventos
//***************************************************************************

int main(int argc, char **argv)
{
    // se llama a la inicialización de glut
    glutInit(&argc, argv);

    // se indica las caracteristicas que se desean para la visualización con OpenGL
    // Las posibilidades son:
    // GLUT_SIMPLE -> memoria de imagen simple
    // GLUT_DOUBLE -> memoria de imagen doble
    // GLUT_INDEX -> memoria de imagen con color indizado
    // GLUT_RGB -> memoria de imagen con componentes rojo, verde y azul para cada pixel
    // GLUT_RGBA -> memoria de imagen con componentes rojo, verde, azul y alfa para cada pixel
    // GLUT_DEPTH -> memoria de profundidad o z-bufer
    // GLUT_STENCIL -> memoria de estarcido
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);

    // posicion de la esquina inferior izquierdad de la ventana
    glutInitWindowPosition(UI_window_pos_x,UI_window_pos_y);

    // tamaño de la ventana (ancho y alto)
    glutInitWindowSize(UI_window_width,UI_window_height);

    // llamada para crear la ventana, indicando el titulo (no se visualiza hasta que se llama
    // al bucle de eventos)
    glutCreateWindow("Practica 4");

    // asignación de la funcion llamada "dibujar" al evento de dibujo
    glutDisplayFunc(draw_scene);
    // asignación de la funcion llamada "cambiar_tamanio_ventana" al evento correspondiente
    glutReshapeFunc(change_window_size);
    // asignación de la funcion llamada "tecla_normal" al evento correspondiente
    glutKeyboardFunc(normal_keys);
    // asignación de la funcion llamada "tecla_Especial" al evento correspondiente
    glutSpecialFunc(special_keys);

    // funcion de inicialización
    initialize();

    glutIdleFunc(idle);

    // inicio del bucle de eventos
    glutMainLoop();
    return 0;
}
