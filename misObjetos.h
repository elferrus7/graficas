#pragma once

#include "Escena.h"

//Clases de objetos particulares
class Cilindro;
class Avion;

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


