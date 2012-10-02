#include <map>
#include <math.h>
#include <string>
// Para Windows:
#include <gl/glut.h>
// Para Mac OS:
//include <GLUT/glut.h>
#define _USE_MATH_DEFINES
#include "math3d.h"
//include "glm.h"

#define MAX_NOMBRE 512
#define MAX_LUCES  8
#define SPECULAR_SHININESS 120.0

using namespace std;

class Objeto;
class Cubo;
class Esfera;
class Tetera;
class Cilindro;
class Avion;
class Modelo;

class Luz;
class Escena;
class Camara;



class Objeto
{
  public:
	GLfloat colorR,colorG,colorB;
	GLfloat posX,posY,posZ;
	GLfloat velX,velY,velZ;
	GLfloat rotX,rotY,rotZ;
	GLfloat velRotX,velRotY,velRotZ;
	GLfloat escalaX,escalaY,escalaZ;
	GLfloat velEscalaX,velEscalaY,velEscalaZ;	
	GLfloat pivotX,pivotY,pivotZ;
	GLuint  displayList;
	unsigned long loopFrames;
	Escena *escenaActual;

	Objeto();
    ~Objeto();
	virtual void actualiza();
	virtual void forma() {};
	virtual void dibuja();
};

class Esfera : Objeto
{
  public:
	GLfloat radio,meridianos,paralelos;
	Esfera(GLfloat radio,GLfloat meridianos,GLfloat paralelos,GLfloat r,GLfloat g,GLfloat b);
    ~Esfera();
	void forma();
};

class Cubo : Objeto
{
  public:
	GLfloat lado;
	Cubo(GLfloat lado,GLfloat r,GLfloat g,GLfloat b);
    ~Cubo();
	void forma();
};

class Tetera : Objeto
{
  public:
	GLfloat tam;
	Tetera(GLfloat tam,GLfloat r,GLfloat g,GLfloat b);
    ~Tetera();
	void forma();
};


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


class Luz : Objeto
{
   public:
	 char tipo;
	 GLfloat posicion[4];
	 GLfloat color[4];
	 GLfloat direccion[4];
	 GLfloat angulo;
	 bool activa;
	 GLenum glLight;
	 
	 Luz(char tipo);
	 ~Luz();
	 void forma();
};


class Escena
{
    public:
        map <string, Objeto *> objetos;
		unsigned long currentFrame;
		bool muestraLuces;
		
		Escena();
		~Escena();
		void agregaObjeto(string nombre,Objeto *nuevoObjeto);		
		void actualizaEscena();		
		void dibujaEscena();
		void cuentaframe();
		void defineLuz(char *nombre,char tipo,GLfloat r,GLfloat g,GLfloat b);
		void posicionLuz(char *nombre,GLfloat x,GLfloat y,GLfloat z);
	    void direccionLuz(char *nombre,GLfloat x,GLfloat y,GLfloat z);
		void anguloLuz(char *nombre,GLfloat angulo);
		void toggleLuz(char *nombre);
		void ilumina();
		Luz *luz(int numero);
};

class Camara
{
   public:
        GLfloat xview;
        GLfloat yview;
        GLfloat zview;
        GLfloat xrot;
        GLfloat yrot;
        GLfloat zrot;
        GLfloat far;
        GLfloat near;
        GLfloat fovy;
        Camara(GLfloat xview,GLfloat yview,GLfloat zview,
               GLfloat xrot,GLfloat yrot,GLfloat zrot,
               GLfloat far,GLfloat near,GLfloat fovy);

};

// Funciones para manejar la aleatoriedad
float rfloat(float min,float max);
float rfloat(float max);
float rcolor();
int rint(int min,int max);
int rint(int max);


