#ifndef FIGURA_H
#define FIGURA_H

#include <GL/gl.h>
#include <vector>
#include "vertex.h"
#include "cara.h"
#include "file_ply_stl.hpp"

using namespace std;

class Figura{
	private:
		vector<_vertex3f> vertices;
		vector<Cara> caras;
		int modo;
		int fichero;
		float c1,c2,c3;
	public:
		Figura(float color1, float color2, float color3);
		Figura &operator=(const Figura &figura);
		~Figura(){} //Destructor de la clase
		void leerPly(char *ply, float color1, float color2, float color3);
		void cambiarPly();
        void cambiarModo(int m){modo=m;}
		void draw();

};
#endif
