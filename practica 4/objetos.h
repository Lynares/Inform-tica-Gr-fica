//**************************************************************************
// Práctica 1 usando objetos
//**************************************************************************

#include <vector>
#include <GL/gl.h>
#include "vertex.h"
#include <stdlib.h>
#include "file_ply_stl.hpp"
#include "jpg_imagen.hpp"

using namespace std;

//const float AXIS_SIZE=5000;

//*************************************************************************
// clase punto
//*************************************************************************

class _puntos3D
{
public:

  
	_puntos3D();
void 	draw_puntos(float r, float g, float b, int grosor);

vector<_vertex3f> vertices;
};

//*************************************************************************
// clase triángulo
//*************************************************************************

class _triangulos3D: public _puntos3D
{
public:

	_triangulos3D();
	void 	draw_aristas(float r, float g, float b, int grosor);
	void    draw_solido(float r, float g, float b);
	void 	draw_solido_ajedrez(float r1, float g1, float b1, float r2, float g2, float b2);
	void draw(float r1, float g1, float b1, float r2, float g2, float b2, int tipo);
	void draw_iluminacion_plana();
	void draw_iluminacion_suave();
	void draw_textura(const string &nombre_archivo);
	void draw_textura_iluminacion_plana(const string &nombre_archivo);
	void draw_textura_iluminacion_suave(const string &nombre_archivo);
        void draw(int modo, float r1, float g1, float b1, float r2, float g2, float b2, GLuint ident_textura);
        void cargarTextura(const string &nombre_archivo);

	void calcular_normales_caras();
	void calcular_normales_vertices();

	vector<_vertex3i> caras;
	vector<_vertex3f> normales_caras;
	vector<_vertex3f> normales_vertices;
	vector<_vertex2f> coordenadas_textura;  //texels


	bool b_normales_caras;
	bool b_normales_vertices;
	bool b_coordenadas_textura;

	_vertex4f ambiente_difusa;  //coeficientes ambiente y difuso
	_vertex4f especular;        //coeficiente especular
	float brillo;               //exponente del brillo

	bool modo_text; //generacion automatica o no de las coordenadas de textura
	GLfloat
	    plano_s[4], //si modo_text=true se usan estos coeficientes para la
	    plano_t[4]; //generacion automatica de las coordenadas de textura

protected:

	GLuint ident_textura; //Entero que se asigna a la textura
	jpg::Imagen *imagen;// = NULL; //Imagen que vamos a leer
	unsigned char* texels;
	unsigned long tamX, tamY;

};


//*************************************************************************
// clase cubo
//*************************************************************************

class _cubo: public _triangulos3D
{
public:

	_cubo(float tam=0.5);
};


//*************************************************************************
// clase piramide
//*************************************************************************

class _piramide: public _triangulos3D
{
public:

	_piramide(float tam=0.5, float al=0.75);
};

//*************************************************************************
// clase Objeto
//*************************************************************************

class Objeto: public _triangulos3D{
    private:
        bool activo;
        int modo;
        int fichero;
        float c1,c2,c3;
    public:
	Objeto();
	Objeto(const char *nombreArchivo);
       
        void cambiarModo(int m){ modo = m; }
        void cambiarColor(float color1, float color2, float color3);
        void activar(){ if (activo) activo = false; else activo = true;}

};
//*************************************************************************
// clase ObjetoR
//*************************************************************************

class ObjetoR: public _triangulos3D{
    private:
        bool activo;
        int modo;
        int fichero;
        int lados;
        int tamPerfil;
        float c1,c2,c3;

    public:
        ObjetoR();
	ObjetoR(const char *nombreArchivo, int num_caras, bool tapa);

        void cambiarModo(int m){ modo = m; }
        void cambiarLados(int l){ lados = l; }
        void activar(){ activo=true; }
        void cambiarColor(float color1, float color2, float color3);

};
//*************************************************************************
// clase ObjetoR_text
//*************************************************************************

class ObjetoR_text: public _triangulos3D{
    private:
        bool activo;
        int modo;
        int fichero;
        int lados;
        int tamPerfil;
        float c1,c2,c3;

    public:
        ObjetoR_text();
	ObjetoR_text(const char* nombre_archivo, int num_caras, bool tapa);


        void cambiarModo(int m){ modo = m; }
        void cambiarLados(int l){ lados = l; }
        void activar(){ activo=true; }
        void cambiarColor(float color1, float color2, float color3);

};
//*************************************************************************
// clase Jerarquico
//*************************************************************************

class Jerarquico: public _triangulos3D{
    private:
        Objeto cubo;
        ObjetoR cilindro;
        Objeto perfilU1;
        Objeto perfilU2;

        bool activo;
        int modo;

        float desplazamiento;
        int giro;
        int elevacion;
        float velDesplazamiento;
        int velGiro;
        int velElevacion;

        void rail();
        void railes();
        void base();
        void cuerpo();
        void brazo();
        void cable();
        void mercancia();
        void eje();
        void cableMercancia();
        void brazoCableMercancia();
        void cuerpoBrazoCableMercancia();
        void baseCuerpoBrazoCableMercancia();
     //   void grua();

    public:
        Jerarquico();
        ~Jerarquico(){}

        void avanzar();
        void retroceder();
        void girarI();
        void girarD();
        void elevar();
        void bajar();
        void cambiarModo(int m);
        void incrementarVelAvance();
        void decrementarVelAvance();
        void incrementarVelGiro();
        void decrementarVelGiro();
        void incrementarVelElevacion();
        void decrementarVelElevacion();
        void cambiarModo();
    void grua();
        void activar(){ if(activo) activo = false; else activo = true; }
        void draw();
};

