#pragma once

#include "Escena.h"
 


//Clases de objetos particulares
class Cilindro;
class Avion;

class Paralelepipedo;

class Avion : Objeto
{
  public:
	Avion(GLfloat r,GLfloat g,GLfloat b);
    ~Avion();
	void forma();
};

class Cilindro : Objeto
{
  public:
	GLfloat radio,altura;
	int lados;
	Cilindro(GLfloat radio,GLfloat altura,int lados,
	         GLfloat r,GLfloat g,GLfloat b);
    ~Cilindro();
	void forma();
  private:
	void tapa(GLfloat signoNormal);
	void cuerpo();
};

/* ---------------------------------------------------------------- */
/* ------------ Definición de la clase Paralelepipedo ------------- */
/* ---------------------------------------------------------------- */

class Paralelepipedo : Objeto
{
	public:
		GLfloat largo, alto, ancho;
		Paralelepipedo(GLfloat largo, GLfloat alto, GLfloat ancho);
		~Paralelepipedo();
		void forma();
};

