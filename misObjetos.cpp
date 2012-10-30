#include "misObjetos.h"

//Metodos de avion
Avion::Avion(GLfloat r,GLfloat g,GLfloat b):Objeto()
{
  	this->colorR = r;
	this->colorG = g;
	this->colorB = b;
}

void Avion::forma()
{
    typedef M3DVector3f Triangulo[3];
    Triangulo avion[]=
    {	
	    {{ 0.0f, 0.0f, 60.0f},{ -15.0f, 0.0f, 30.0f},{ 15.0f,0.0f,30.0f}},
	    {{ 15.0f, 0.0f,  30.0f},{ 0.0f,  15.0f, 30.0f},{ 0.0f,  0.0f,  60.0f}},
        {{ 0.0f, 0.0f, 60.0f },{ 0.0f, 15.0f, 30.0f },{ -15.0f, 0.0f, 30.0f }},
	    {{ -15.0f, 0.0f, 30.0f },{ 0.0f, 15.0f, 30.0f },{ 0.0f, 0.0f, -56.0f }},
	    {{ 0.0f, 0.0f, -56.0f },{ 0.0f, 15.0f, 30.0f },{ 15.0f,0.0f,30.0f }},
	    {{ 15.0f,0.0f,30.0f },{-15.0f, 0.0f, 30.0f  },{ 0.0f, 0.0f, -56.0f }},
	    {{ 0.0f,2.0f,27.0f },{ -60.0f, 2.0f, -8.0f },{ 60.0f, 2.0f, -8.0f }},
	    {{ 60.0f, 2.0f, -8.0f},{0.0f, 7.0f, -8.0f},{0.0f,2.0f,27.0f }},
	    {{60.0f, 2.0f, -8.0f},{-60.0f, 2.0f, -8.0f},{0.0f,7.0f,-8.0f }},
	    {{0.0f,2.0f,27.0f},{0.0f, 7.0f, -8.0f},{-60.0f, 2.0f, -8.0f}},
	    {{-30.0f, -0.50f, -57.0f},{30.0f, -0.50f, -57.0f},{0.0f,-0.50f,-40.0f}},
	    {{ 0.0f,-0.5f,-40.0f },{30.0f, -0.5f, -57.0f},{0.0f, 4.0f, -57.0f }},
	    {{ 0.0f, 4.0f, -57.0f },{ -30.0f, -0.5f, -57.0f },{ 0.0f,-0.5f,-40.0f }},
	    {{ 30.0f,-0.5f,-57.0f },{ -30.0f, -0.5f, -57.0f },{ 0.0f, 4.0f, -57.0f }},
	    {{ 0.0f,0.5f,-40.0f },{ 3.0f, 0.5f, -57.0f },{ 0.0f, 25.0f, -65.0f }},
	    {{ 0.0f, 25.0f, -65.0f },{ -3.0f, 0.5f, -57.0f},{ 0.0f,0.5f,-40.0f }},
	    {{ 3.0f,0.5f,-57.0f },{ -3.0f, 0.5f, -57.0f },{ 0.0f, 25.0f, -65.0f }},
    };

    glBegin(GL_TRIANGLES);
	for (int i=0; i<17; i++) {
		//TODO Agregar normales
		M3DVector3f normal;
		m3dFindNormal(normal, avion[i][0], avion[i][1], avion[i][2]);
		glNormal3f(normal[0], normal[1], normal[2]);
		glVertex3fv(avion[i][0]);
		glVertex3fv(avion[i][1]);
		glVertex3fv(avion[i][2]);
	}
    glEnd();
}

//Metodos del cilindro

Cilindro::Cilindro(GLfloat radio,GLfloat altura,int lados,
	               GLfloat r,GLfloat g,GLfloat b)
{
  this->radio = radio;
  this->altura = altura;
  this->lados = lados;
  this->colorR = r;
  this->colorG = g;
  this->colorB = b;
}
	
void Cilindro::forma()
{
  glPushMatrix();
  tapa(-1.0);
  cuerpo();
  glTranslatef(0.0, 0.0, altura);
  tapa(1.0);
  glPopMatrix();
}
	
void Cilindro::tapa(GLfloat signoNormal)
{
  glBegin(GL_TRIANGLE_FAN);
  GLfloat angulo=0.0;
  GLfloat dangulo=2*M_PI/lados;
  GLfloat x,y;
  glNormal3f(0.0,0.0,signoNormal);
  glVertex3f(0.0,0.0,0.0);
  for (int i=0; i<=lados; i++) {
	  x=radio*cos(angulo);
	  y=radio*sin(angulo);
	  glVertex3f(x,y,0.0);
	  angulo+=dangulo;
  }
  glEnd();
}
	
void Cilindro::cuerpo()
{
  glBegin(GL_QUAD_STRIP);
  GLfloat angulo=0.0;
  GLfloat dangulo=2*M_PI/lados;
  GLfloat x,y;
  for (int i=0; i<=lados; i++) {
	  x=cos(angulo);
	  y=sin(angulo);
	  glNormal3f(x,y,0.0);
	  x*=radio;
	  y*=radio;
	  glVertex3f(x,y,0.0);
	  glVertex3f(x,y,altura);
	  angulo+=dangulo;
  }
  glEnd();
}


/* ---------------------------------------------------------------- */
/* -------------------- Métodos Paralelepipedo -------------------- */
/* ---------------------------------------------------------------- */

Paralelepipedo::Paralelepipedo(GLfloat largo, GLfloat alto, GLfloat ancho):Objeto()
{
	this->largo = largo;
	this->alto = alto;
	this->ancho = ancho;
}

void Paralelepipedo::forma()
{

	//Primer cuadro
	M3DVector3f normal;
	
	M3DVector3f point1 = {0.0f,0.0f,0.0f};
	M3DVector3f point2 = {0.0f, alto, 0.0f};
	M3DVector3f point3 = {largo, 0.0f, 0.0f};
	M3DVector3f point4 = {largo, alto, 0.0f};
	glBegin(GL_QUAD_STRIP);
	
	m3dFindNormal(normal, point1, point1, point1);

	glNormal3fv(normal);

	glVertex3fv(point1);

	glVertex3fv(point2); 

	glVertex3fv(point3);

	glVertex3fv(point4);

	//Segundo cuadro
	
	M3DVector3f point5 = {largo, 0.0f, ancho};
	M3DVector3f point6 = {largo, alto, ancho};
	M3DVector3f normal2;
	m3dFindNormal(normal2,point4,point5,point6);

	glNormal3fv(normal2);

	glVertex3fv(point5);

	glVertex3fv(point6); 
	
	//Tercer cuadro
	M3DVector3f point7 = {0.0f, 0.0f, ancho};
	M3DVector3f point8 = {0.0f, alto, ancho};
	M3DVector3f normal3;
	m3dFindNormal(normal3,point6,point7,point8);

	glNormal3fv(normal3);

	glVertex3fv(point7);

	glVertex3fv(point8);

	//Cuarto cuadro

	M3DVector3f normal4;
	m3dFindNormal(normal4,point1,point2,point8);
	glNormal3fv(normal4);
	glVertex3fv(point1);

	glVertex3fv(point2); 

	glEnd();

	//Base
	glBegin(GL_QUADS);
	
	M3DVector3f normal5;
	m3dFindNormal(normal5,point1,point7,point5);
	glNormal3fv(normal5);
	//Esquina inferior izquierda
	glVertex3fv(point1);

	//Esquina superior izquierda
	glVertex3fv(point7); 

	//Esquina superior derecha
	glVertex3fv(point5);

	//Esquina inferior derecha
	glVertex3fv(point3);
 
	glEnd();

	//Tapa
	glBegin(GL_QUADS);
	M3DVector3f normal6;
	m3dFindNormal(normal6,point2,point8,point6);
	glNormal3fv(normal6);
	//Esquina inferior izquierda
	glVertex3fv(point2);

	//Esquina superior izquierda
	glVertex3fv(point8); 

	//Esquina superior derecha
	glVertex3fv(point6);

	//Esquina inferior derecha
	glVertex3fv(point4);

	glEnd();
}





