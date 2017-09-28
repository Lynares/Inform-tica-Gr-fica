
#include "objetos.h"

/****************************************************************************
*		_puntos3D
****************************************************************************/
_puntos3D::_puntos3D()
{

}

void 	_puntos3D::draw_puntos(float r, float g, float b, int grosor)
{
    glColor3f(r,g,b);

    glPointSize(grosor);

    glBegin(GL_POINTS);
    for (int i=0;i<vertices.size();i++)
        glVertex3f(vertices[i].x,vertices[i].y,vertices[i].z);
    glEnd();

}

/****************************************************************************
*		_triangulos3D
****************************************************************************/
_triangulos3D::_triangulos3D()
{

	brillo = 1;
	b_normales_caras = false;
	b_normales_vertices = false;
        b_coordenadas_textura = false;
	especular._0 = 1.0;
	especular._1 = 0.2;
	especular._2 = 0.2;
	especular._3 = 1.0;
	ambiente_difusa._0 = 1.0;
	ambiente_difusa._1 = 0.7;
	ambiente_difusa._2 = 0.2;
	ambiente_difusa._3 = 0;

	modo_text = true;

    for(int i = 0; i < 4; i++){
        plano_s[i] = 0.0;
        plano_t[i] = 0.0;
    }

    plano_s[0] = 1.0;
    plano_t[1] = 1.0;


}
void _triangulos3D::draw(float r1, float g1, float b1, float r2, float g2, float b2, int tipoDibujo){

	switch(tipoDibujo){
		case 0:
			draw_puntos(r1,g1,b1,2);
		break;
		case 1:
			draw_aristas(r1,g1,b1,2);
		break;
		case 2:
			draw_solido(r1,g1,b1);
		break;
		case 3:
			draw_solido_ajedrez(r1,g1,b1,r2,g2,b2);
		break;
	}

}

void 	_triangulos3D::draw_aristas(float r, float g, float b, int grosor)
{
    glColor3f(r,g,b);
    int n_v;
    glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);

    glBegin(GL_TRIANGLES);
    for (int i=0;i<caras.size();i++){
    n_v=caras[i]._0;
        glVertex3f(vertices[n_v].x,vertices[n_v].y,vertices[n_v].z);
    n_v=caras[i]._1;
        glVertex3f(vertices[n_v].x,vertices[n_v].y,vertices[n_v].z);
    n_v=caras[i]._2;
        glVertex3f(vertices[n_v].x,vertices[n_v].y,vertices[n_v].z);
    }
    glEnd();

}
void    _triangulos3D::draw_solido(float r, float g, float b)
{
    int n_v;
    glColor3f(r,g,b);

    glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);

    glBegin(GL_TRIANGLES);
    for (int i=0;i<caras.size();i++){
    n_v=caras[i]._0;
        glVertex3f(vertices[n_v].x,vertices[n_v].y,vertices[n_v].z);
    n_v=caras[i]._1;
        glVertex3f(vertices[n_v].x,vertices[n_v].y,vertices[n_v].z);
    n_v=caras[i]._2;
        glVertex3f(vertices[n_v].x,vertices[n_v].y,vertices[n_v].z);
    }
    glEnd();
}
//	            glVertex3fv((GLFloat *) cada una de las cvertices
void 	_triangulos3D::draw_solido_ajedrez(float r1, float g1, float b1, float r2, float g2, float b2)
{

	int n_v;
    glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);

    glBegin(GL_TRIANGLES);
    for (int i=0;i<caras.size();i++){
	if(i%2==0)
	    glColor3f(r1,g1,b1);
	else
	    glColor3f(r2,g2,b2);
    n_v=caras[i]._0;
        glVertex3f(vertices[n_v].x,vertices[n_v].y,vertices[n_v].z);
    n_v=caras[i]._1;
        glVertex3f(vertices[n_v].x,vertices[n_v].y,vertices[n_v].z);
    n_v=caras[i]._2;
        glVertex3f(vertices[n_v].x,vertices[n_v].y,vertices[n_v].z);
    }
    glEnd();

}

void _triangulos3D::calcular_normales_caras(){
	normales_caras.resize(caras.size());
	_vertex3f a1, a2, n;
	float m;

	for(unsigned long i = 0; i < caras.size(); i++){
		//cálculo del producto vectorial
		a1 = vertices[caras[i]._1] - vertices[caras[i]._0];
		a2 = vertices[caras[i]._2] - vertices[caras[i]._0];
		n = a1.cross_product(a2);
		//módulo
		m = sqrt((n.x * n.x) + (n.y * n.y) + (n.z * n.z));
		//normalización
		normales_caras[i] = _vertex3f(n.x / m, n.y / m, n.z / m);
	}

	b_normales_caras = true;
}

void _triangulos3D::calcular_normales_vertices()
{
	if(!b_normales_vertices){

		if(!b_normales_caras)
			calcular_normales_caras();

		normales_vertices.resize(vertices.size());

		for (int i = 0; i < vertices.size(); i++){
			normales_vertices[i].x = 0.0;
			normales_vertices[i].y = 0.0;
			normales_vertices[i].z = 0.0;
		}

		for (int i = 0; i < caras.size(); i++){
			//suma de la normal con los vértices
			normales_vertices[caras[i]._0]+=normales_caras[i];
			normales_vertices[caras[i]._1]+=normales_caras[i];
			normales_vertices[caras[i]._2]+=normales_caras[i];
		}

		//normalización
		for (int i = 0; i < vertices.size(); i++){
			normales_vertices[i].normalize();
		}

		b_normales_vertices = true;
	}
}

void _triangulos3D::draw_iluminacion_plana()
{
  	if(!b_normales_caras)
		calcular_normales_caras();

	glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE);

	glShadeModel(GL_FLAT);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHT1);
	glEnable(GL_NORMALIZE);

	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, (GLfloat *) &ambiente_difusa);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, (GLfloat *) &especular);
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, brillo);

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glBegin(GL_TRIANGLES);

	for (int i = 0; i < caras.size(); i++){
		glNormal3fv((GLfloat *) &normales_caras[i]);
		glVertex3fv((GLfloat *) &vertices[caras[i]._0]);
		glVertex3fv((GLfloat *) &vertices[caras[i]._1]);
		glVertex3fv((GLfloat *) &vertices[caras[i]._2]);
	}

	glEnd();
	glDisable(GL_LIGHTING);

}

void _triangulos3D::draw_iluminacion_suave()
{
	if(!b_normales_vertices)
		calcular_normales_vertices();

	glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE);

	glShadeModel(GL_SMOOTH);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHT1);
	glEnable(GL_NORMALIZE);

	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, (GLfloat *) &ambiente_difusa);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, (GLfloat *) &especular);
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, brillo);

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glBegin(GL_TRIANGLES);

	for (int i = 0; i < caras.size(); i++){
		glNormal3fv((GLfloat *) &normales_vertices[caras[i]._0]);
		glVertex3fv((GLfloat *) &vertices[caras[i]._0]);
		glNormal3fv((GLfloat *) &normales_vertices[caras[i]._1]);
		glVertex3fv((GLfloat *) &vertices[caras[i]._1]);
		glNormal3fv((GLfloat *) &normales_vertices[caras[i]._2]);
		glVertex3fv((GLfloat *) &vertices[caras[i]._2]);
	}

	glEnd();
	glDisable(GL_LIGHTING);

}
//Funcion para cargar una textura
void _triangulos3D::cargarTextura(const string &nombre_archivo){

    //Cargar la imagen
    imagen = new jpg::Imagen(nombre_archivo);
    tamX = imagen->tamX();
    tamY = imagen->tamY();
    texels = imagen->leerPixels();
}
//Funcion con la que aplicamos una textura
void _triangulos3D::draw_textura(const string &nombre_archivo){
	if(imagen == NULL)
        cargarTextura(nombre_archivo);

    glTexImage2D(GL_TEXTURE_2D, 0, 3, tamX, tamY, 0, GL_RGB, GL_UNSIGNED_BYTE, texels);
    //Activación de la textura
    glEnable(GL_TEXTURE_2D);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    //Generación automática de texturas
    if(modo_text){
        glEnable(GL_TEXTURE_GEN_S);
        glEnable(GL_TEXTURE_GEN_T);
        glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_EYE_LINEAR);
        glTexGenfv(GL_S, GL_EYE_PLANE, plano_s);
        glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_EYE_LINEAR);
        glTexGenfv(GL_T, GL_EYE_PLANE, plano_t);
    }


    glColor3f(0.8, 0.8, 0.8);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glBegin(GL_TRIANGLES);

    for(int i = 0; i < caras.size(); i++){
        if(b_coordenadas_textura)
            glTexCoord2f(coordenadas_textura[caras[i]._0].s, coordenadas_textura[caras[i]._0].t);
        glVertex3fv((GLfloat *) &vertices[caras[i]._0]);
        if(b_coordenadas_textura)
            glTexCoord2f(coordenadas_textura[caras[i]._1].s, coordenadas_textura[caras[i]._1].t);
        glVertex3fv((GLfloat *) &vertices[caras[i]._1]);
        if(b_coordenadas_textura)
            glTexCoord2f(coordenadas_textura[caras[i]._2].s, coordenadas_textura[caras[i]._2].t);
        glVertex3fv((GLfloat *) &vertices[caras[i]._2]);

    }

    glEnd();
    glDisable(GL_TEXTURE_2D);
    glDisable(GL_TEXTURE_GEN_S);
    glDisable(GL_TEXTURE_GEN_T);
}

void _triangulos3D::draw_textura_iluminacion_plana(const string &nombre_archivo){

    if(imagen == NULL){
        cargarTextura(nombre_archivo);
        glTexImage2D(GL_TEXTURE_2D, 0, 3, tamX, tamY, 0, GL_RGB, GL_UNSIGNED_BYTE, texels);
    }

    GLfloat material_blanco[4] = {1,1,1,1};

    if(!b_normales_caras)
        calcular_normales_caras();

    //Activar iluminación
    glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE);
    glShadeModel(GL_FLAT);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
//    glEnable(GL_LIGHT1);
    glEnable(GL_NORMALIZE);

    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, material_blanco);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, (GLfloat *) &especular);
    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, brillo);

    //Activar textura
    glEnable(GL_TEXTURE_2D);
    //glBindTexture(GL_TEXTURE_2D, ident_textura);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    //Generación automática de texturas
    if(modo_text){
        glEnable(GL_TEXTURE_GEN_S);
        glEnable(GL_TEXTURE_GEN_T);
        glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_EYE_LINEAR);
        glTexGenfv(GL_S, GL_EYE_PLANE, plano_s);
        glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_EYE_LINEAR);
        glTexGenfv(GL_T, GL_EYE_PLANE, plano_t);
    }

    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glBegin(GL_TRIANGLES);

    for(int i = 0; i < caras.size(); i++){
        if(b_coordenadas_textura)
            glTexCoord2f(coordenadas_textura[caras[i]._0].s, coordenadas_textura[caras[i]._0].t);
        glVertex3fv((GLfloat *) &vertices[caras[i]._0]);
        if(b_coordenadas_textura)
            glTexCoord2f(coordenadas_textura[caras[i]._1].s, coordenadas_textura[caras[i]._1].t);
        glVertex3fv((GLfloat *) &vertices[caras[i]._1]);
        if(b_coordenadas_textura)
            glTexCoord2f(coordenadas_textura[caras[i]._2].s, coordenadas_textura[caras[i]._2].t);
        glVertex3fv((GLfloat *) &vertices[caras[i]._2]);

    }

    glEnd();
    glDisable(GL_LIGHTING);
    glDisable(GL_TEXTURE_2D);
    glDisable(GL_TEXTURE_GEN_S);
    glDisable(GL_TEXTURE_GEN_T);

}

void _triangulos3D::draw_textura_iluminacion_suave(const string &nombre_archivo){

    if(imagen == NULL){
        cargarTextura(nombre_archivo);
        glTexImage2D(GL_TEXTURE_2D, 0, 3, tamX, tamY, 0, GL_RGB, GL_UNSIGNED_BYTE, texels);
    }

    GLfloat material_blanco[4] = {1,1,1,1};

    if(!b_normales_caras)
        calcular_normales_caras();

    //Activar iluminación
    glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE);
    glShadeModel(GL_SMOOTH);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_NORMALIZE);

    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, material_blanco);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, (GLfloat *) &especular);
    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, brillo);

    //Activar textura
    glEnable(GL_TEXTURE_2D);
    //glBindTexture(GL_TEXTURE_2D, ident_textura);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    //Generación automática de texturas
    if(modo_text){
        glEnable(GL_TEXTURE_GEN_S);
        glEnable(GL_TEXTURE_GEN_T);
        glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_EYE_LINEAR);
        glTexGenfv(GL_S, GL_EYE_PLANE, plano_s);
        glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_EYE_LINEAR);
        glTexGenfv(GL_T, GL_EYE_PLANE, plano_t);
    }

    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glBegin(GL_TRIANGLES);

    for(int i = 0; i < caras.size(); i++){
        if(b_coordenadas_textura)
            glTexCoord2f(coordenadas_textura[caras[i]._0].s, coordenadas_textura[caras[i]._0].t);
        glVertex3fv((GLfloat *) &vertices[caras[i]._0]);
        if(b_coordenadas_textura)
            glTexCoord2f(coordenadas_textura[caras[i]._1].s, coordenadas_textura[caras[i]._1].t);
        glVertex3fv((GLfloat *) &vertices[caras[i]._1]);
        if(b_coordenadas_textura)
            glTexCoord2f(coordenadas_textura[caras[i]._2].s, coordenadas_textura[caras[i]._2].t);
        glVertex3fv((GLfloat *) &vertices[caras[i]._2]);

    }

    glEnd();
    glDisable(GL_LIGHTING);
    glDisable(GL_TEXTURE_2D);
    glDisable(GL_TEXTURE_GEN_S);
    glDisable(GL_TEXTURE_GEN_T);

}

/****************************************************************************
*		_cubo
****************************************************************************/
_cubo::_cubo(float tam)
{
_vertex3f vertice;

vertice.x=-tam;vertice.y=-tam;vertice.z=tam;
vertices.push_back(vertice);
vertice.x=tam;vertice.y=-tam;vertice.z=tam;
vertices.push_back(vertice);
vertice.x=tam;vertice.y=tam;vertice.z=tam;
vertices.push_back(vertice);
vertice.x=-tam;vertice.y=tam;vertice.z=tam;
vertices.push_back(vertice);
vertice.x=-tam;vertice.y=-tam;vertice.z=-tam;
vertices.push_back(vertice);
vertice.x=tam;vertice.y=-tam;vertice.z=-tam;
vertices.push_back(vertice);
vertice.x=tam;vertice.y=tam;vertice.z=-tam;
vertices.push_back(vertice);
vertice.x=-tam;vertice.y=tam;vertice.z=-tam;
vertices.push_back(vertice);

_vertex3i c;
c._0=3;c._1=0;c._2=1;
caras.push_back(c);
c._0=3;c._1=1;c._2=2;
caras.push_back(c);
c._0=2;c._1=1;c._2=5;
caras.push_back(c);
c._0=2;c._1=5;c._2=6;
caras.push_back(c);
c._0=4;c._1=5;c._2=6;
caras.push_back(c);
c._0=7;c._1=4;c._2=6;
caras.push_back(c);
c._0=7;c._1=0;c._2=4;
caras.push_back(c);
c._0=3;c._1=0;c._2=7;
caras.push_back(c);
c._0=0;c._1=4;c._2=1;
caras.push_back(c);
c._0=4;c._1=1;c._2=5;
caras.push_back(c);
c._0=7;c._1=3;c._2=2;
caras.push_back(c);
c._0=7;c._1=2;c._2=6;
caras.push_back(c);
}

/****************************************************************************
*		_piramide
****************************************************************************/
_piramide::_piramide(float tam, float al)
{

_vertex3f vertice;

vertice.x=0;vertice.y=al;vertice.z=0;
vertices.push_back(vertice);
vertice.x=-tam;vertice.y=-al;vertice.z=-tam;
vertices.push_back(vertice);
vertice.x=0;vertice.y=-al;vertice.z=tam;
vertices.push_back(vertice);
vertice.x=tam;vertice.y=-al;vertice.z=-tam;
vertices.push_back(vertice);

_vertex3i c;
c._0=0;c._1=1;c._2=2;
caras.push_back(c);
c._0=0;c._1=2;c._2=3;
caras.push_back(c);
c._0=0;c._1=3;c._2=1;
caras.push_back(c);
c._0=1;c._1=2;c._2=3;
caras.push_back(c);

}
/****************************************************************************
*		Objeto
****************************************************************************/


Objeto::Objeto(){}

//Constructor para la clase Objeto
Objeto::Objeto(const char* nombre_archivo){

    vector<double> v_float;
    vector<unsigned long> v_long;
    _vertex3f v3f;
    _vertex3i v3i;
    float y_mayor = -100000.0, x_mayor = -100000.0, y_menor = 100000.0, x_menor = 100000.0;

    _file_ply::read(nombre_archivo, v_float, v_long);

    for(int i = 0; i < v_float.size(); i+=3){
        v3f._0 = v_float[i];
        v3f._1 = v_float[i+1];
        v3f._2 = v_float[i+2];
        vertices.push_back(v3f);
        
        if(v3f._1 > y_mayor)
            y_mayor = v3f._1;
        if(v3f._0 > x_mayor)
            x_mayor = v3f._0;

        if(v3f._1 < y_menor)
            y_menor = v3f._1;
        if(v3f._0 < x_menor)
            x_menor = v3f._0;
    }

    for(int i = 0; i < v_long.size(); i+=3){
        v3i._0 = v_long[i];
        v3i._1 = v_long[i+1];
        v3i._2 = v_long[i+2];
        caras.push_back(v3i);
    }



plano_s[0]/=(x_mayor - x_menor);
plano_t[1]/=(y_mayor - y_menor);
}

    void Objeto::cambiarColor(float color1, float color2, float color3)
    {
        c1= color1;
        c2= color2;
        c3= color3;

    }

/****************************************************************************
*		ObjetoR
****************************************************************************/
ObjetoR::ObjetoR(){}


ObjetoR::ObjetoR(const char *nombreArchivo, int num_caras, bool tapa){

	Objeto p(nombreArchivo);

    static const double pi = 3.1416;
    double alfa = 2*pi/num_caras, static_alfa = 2*pi/num_caras;;
    int indice = 0;

    if(tapa){
        _vertex3f v;
        v._0 = 0;
        v._1 = p.vertices[0].y;
        v._2 = 0;
        p.vertices.insert(p.vertices.begin(), v);

        v._0 = 0;
        v._1 = p.vertices[p.vertices.size()-1].y;
        v._2 = 0;
        p.vertices.push_back(v);

    }

    for(int i = 0; i < num_caras; i++) {
        for(int j = 0; j < p.vertices.size(); j++){
            _vertex3f v;
            v._0 = p.vertices[j]._0*cos(alfa);
            v._1 = p.vertices[j]._1;
            v._2 = p.vertices[j]._0*sin(alfa);
            vertices.push_back(v);
        }
        alfa += static_alfa;
    }

    for(int i = 0; i < p.vertices.size()-1; i++){
        for(int j = 0; j < num_caras; j++){
            indice = i*p.vertices.size() + j;
            _vertex3i caras_sup(i + j * p.vertices.size(), i + ((j + i)%num_caras)*p.vertices.size(), (i+1)%p.vertices.size()+ (j*p.vertices.size()));
            _vertex3i caras_inf(i + ((j + 1)%num_caras)*p.vertices.size(), ((i + 1)%p.vertices.size())+((j + 1)%num_caras)*p.vertices.size(), (i+1)%p.vertices.size()+(j*p.vertices.size()));
            caras.push_back(caras_sup);
            caras.push_back(caras_inf);
        }
    }
}

/****************************************************************************
*		ObjetoR_text
****************************************************************************/
//Constructor por defecto
ObjetoR_text::ObjetoR_text(){}

//Constructor para la clase
ObjetoR_text::ObjetoR_text(const char* nombre_archivo,  int num_caras, bool tapa){

    Objeto perfil(nombre_archivo);

    _vertex3f vertice_aux;
    _vertex3i cara_aux;
    _vertex2f textura_aux;
    vector<float> distancias;
    float distancia_total = 0.0;
    int num_caras_aux;
    static const double pi = 3.1416;
    double alfa = 2*pi/num_caras, static_alfa = 2*pi/num_caras;
    int indice = 0;
	if(tapa){
        _vertex3f v;
        v._0 = 0;
        v._1 = perfil.vertices[0].y;
        v._2 = 0;
        perfil.vertices.insert(perfil.vertices.begin(), v);

        v._0 = 0;
        v._1 = perfil.vertices[perfil.vertices.size()-1].y;
        v._2 = 0;
        perfil.vertices.push_back(v);

    }

    //Cálculo de distancias para las coordenadas de textura
    num_caras_aux = perfil.vertices.size();
    for(int i = 0; i < num_caras_aux -1; i++){
        distancias.push_back(distancia_total);
        distancia_total += sqrt((perfil.vertices[i].x-perfil.vertices[i+1].x) * (perfil.vertices[i].x-perfil.vertices[i+1].x)
                + (perfil.vertices[i].y-perfil.vertices[i+1].y) * (perfil.vertices[i].y-perfil.vertices[i+1].y)
                + (perfil.vertices[i].z-perfil.vertices[i+1].z) * (perfil.vertices[i].z-perfil.vertices[i+1].z));
    }

    for(int i = 1; i < num_caras_aux - 1; i++)
        distancias[i] = 1.0 - (distancias[i]/distancia_total); //Normalizar distancias

    distancias[0] = 1.0; //Primera distancia
    distancias.push_back(0.0); //Última distancia

    //Tratamiento de los vértices
    for(int i = 0; i < num_caras + 1; i++){
        textura_aux.s = i/(1.0*num_caras);
        for(int j = 0; j < num_caras_aux; j++){
            vertice_aux.x = perfil.vertices[j].x * cos(alfa);
            vertice_aux.z = perfil.vertices[j].x * sin(alfa);
            vertice_aux.y = perfil.vertices[j].y;

            vertices.push_back(vertice_aux);
            textura_aux.t = distancias[j];
            coordenadas_textura.push_back(textura_aux);
        }
        alfa += static_alfa;
    }

    //Asignación manual de coordenadas de textura
    modo_text = false;
    b_coordenadas_textura = true;

    //Tratamiento de las caras
    for(int j = 0; j < num_caras; j++){
        for(int i = 0; i < num_caras_aux - 1; i++){
            cara_aux._0 = i + (j + 1) * num_caras_aux;
            cara_aux._1 = i + 1 + (j + 1) * num_caras_aux;
            cara_aux._2 = i + 1 + (j * num_caras_aux);
            caras.push_back(cara_aux);

            cara_aux._0 = i + 1 + (j * num_caras_aux);
            cara_aux._1 = i + (j * num_caras_aux);
            cara_aux._2 = i + (j + 1) * num_caras_aux;
            caras.push_back(cara_aux);
        }
    }
}

/****************************************************************************
*		Jerarquico
****************************************************************************/
Jerarquico::Jerarquico()
{
        activo = true;

        modo = 2;

	const char* cub = "cubo";
        Objeto cubo("cubo");
        cubo.cambiarModo(2);
        cubo.activar();

	const char* cilin = "f";
  	ObjetoR cilindro("f",100,true);
        cilindro.cambiarModo(2);
        cilindro.activar();

	const char* p1 = "perfilU1";
        Objeto perfilU1("perfilU1");
        perfilU1.cambiarModo(2);
        perfilU1.activar();

	const char* p2 = "perfilU2.ply";
        Objeto perfilU2("perfilU2");
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
        //cubo.cambiarColor(0.2,0.3,0.4);
        cubo.draw(0.2,0.3,0.4,0.2,0.3,0.4,3);
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
        perfilU1.draw(0.6,0.4,1,0.6,0.4,1,3);
    }

    void Jerarquico::cuerpo()
    {
        glTranslatef(-2.5,0,-2.5);
        perfilU2.draw(0.6,0.4,1,0.6,0.4,1,3);
    }

    void Jerarquico::brazo()
    {

        glTranslatef(-0.5,-0.5,-1.5);
        glScalef(20.5,1,3);
    //    cubo.cambiarColor(0.3,0.4,0.5);
        cubo.draw(0.3,0.4,0.5,0.2,0.3,0.4,3);
    }

    void Jerarquico::cable()
    {
        glTranslatef(0,-5,0);
        glScalef(0.1,5,0.1);
  //      cilindro.cambiarColor(0.1,0.1,0.1);
        cilindro.draw(0.1,0.1,0.1,0.1,0.1,0.1,3);
    }

    void Jerarquico::mercancia()
    {

        glTranslatef(-1,-1,-1);
        glScalef(2,2,2);
//        cubo.cambiarColor(0.6,0.4,1);
        cubo.draw(0.6,0.4,1,0.6,0.4,1,3);
    }

    void Jerarquico::eje()
    {
        glTranslatef(-3.625,-0.75,-0.125);
        glScalef(0.25,2.5,0.25);
        cubo.draw(0.6,0.4,1,0.6,0.4,1,3);
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
          //  draw();
        }
    }

    void Jerarquico::retroceder()
    {
        if(desplazamiento-velDesplazamiento > 0.0)
        {
            desplazamiento-=velDesplazamiento;
         //   draw();
        }
    }

    void Jerarquico::girarI()
    {
        giro += velGiro;
        giro = giro%360;
      //  draw();
    }

    void Jerarquico::girarD()
    {
        giro -= velGiro;
        giro = giro%360;
        //draw();
    }

    void Jerarquico::elevar()
    {
        if(elevacion+velElevacion < 65)
        {
            elevacion+=velElevacion;
        //    draw();
        }
    }

    void Jerarquico::bajar()
    {
        if(elevacion-velElevacion > 0)
        {
            elevacion-=velElevacion;
        //    draw();
        }
    }
    void Jerarquico::cambiarModo(int m){

        cubo.cambiarModo(m);
        cilindro.cambiarModo(m);
        perfilU1.cambiarModo(m);
        perfilU2.cambiarModo(m);

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

