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





