#pragma once

#include <map>
#include <math.h>
#include <string>
// Para Windows:
#include <gl/glut.h>
// Para Mac OS:
//#include <GLUT/glut.h>
#define _USE_MATH_DEFINES
#include "math3d.h"
#include "glm.h"

#define ESCAPE 27 //Tecla para terminar la ejecucion

#define MAX_NOMBRE 512 //Maxima longitud para el nombre de un archivo de textura o modelo
#define MAX_LUCES  8   //Maximo de luces estandar de Open GL
#define SPECULAR_SHININESS 120.0 //Constante para el brillo especular

//Posicion y dimensiones iniciales de ventana
#define WIN_POSX   100
#define WIN_POSY   100
#define WIN_WIDTH  1024
#define WIN_HEIGHT 640

// Filtro por default para carga de texturas
#define TEX_FILTER  GL_LINEAR_MIPMAP_LINEAR

// Modos de mapeo de texturas para modelos
#define TEX_LINEAR 0 //Mapeo lineal (Default)
#define TEX_SPHERE 1 //Mapeo esferico

//Macros para componentes de materiales
#define definido(color) ((color[0]+color[1]+color[2])!=0.0)
#define limpia(color) for(int i=0; i<3; i++) color[i]=0.0; color[3]=1.0
#define copia(color,r,g,b) color[0]=r,color[1]=g,color[2]=b

//Defaults para traslacion y rotacion interactiva
#define DELTA_TRAN 0.25
#define DELTA_ROT  1.0

//Multiplicadores para interpretar desplazamientos de mouse
#define MOUSE_MUL_TX 7.0      //Multipicador para traslacion en X
#define MOUSE_MUL_TY 5.0      //Multipicador para traslacion en Y
#define MOUSE_MUL_TZ 30.0     //Multipicador para traslacion en Z
#define MOUSE_MUL_RX 50.0     //Multipicador para rotacion respecto a eje X
#define MOUSE_MUL_RY 50.0     //Multipicador para rotacion respecto a eje Y
#define MOUSE_DELTA_MIN 0.001 //Delta minima para inicializacion

//default para loopFrames en AlphaQuads
#define DEFAULT_LOOP_FRAMES 0xFFFFFFFF
 

// Estructura del encabezado del archivo de textura TGA
#pragma pack(1)
typedef struct
{
    GLbyte	identsize;              // Size of ID field that follows header (0)
    GLbyte	colorMapType;           // 0 = None, 1 = paletted
    GLbyte	imageType;              // 0 = none, 1 = indexed, 2 = rgb, 3 = grey, +8=rle
    unsigned short	colorMapStart;          // First colour map entry
    unsigned short	colorMapLength;         // Number of colors
    unsigned char 	colorMapBits;   // bits per palette entry
    unsigned short	xstart;                 // image x origin
    unsigned short	ystart;                 // image y origin
    unsigned short	width;                  // width in pixels
    unsigned short	height;                 // height in pixels
    GLbyte	bits;                   // bits per pixel (8 16, 24, 32)
    GLbyte	descriptor;             // image descriptor
} TGAHEADER;
#pragma pack(8)

using namespace std;

//Clases de objetos generales
class Objeto;
class Cubo;
class Esfera;
class Tetera;
class Modelo;
class AlphaQuad;

class Luz;
class Camara;
class Escena;




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
	bool usaMaterial;
	GLuint mappingMode;
	_GLMmaterial material;
	map <string, Objeto *> descendientes;

	Objeto();
    ~Objeto();
    void escalaUniforme(GLfloat escala);
	virtual void actualiza();
	virtual void forma() {};
	virtual void dibuja();
	void copiaMaterial(string nombreModelo,string nombreMaterial,GLuint	mappingMode);
	void defineMaterial(GLfloat aR,GLfloat aG,GLfloat aB,
						GLfloat dR,GLfloat dG,GLfloat dB,
						GLfloat sR,GLfloat sG,GLfloat sB,
						GLfloat eR,GLfloat eG,GLfloat eB,
						string  nombreTextura,
						GLuint  wrapmode,              
						GLfloat alpha,
						GLfloat stexdis,			   
						GLfloat ttexdis,			    
						GLfloat stexspeed,			
						GLfloat ttexspeed,			
						GLfloat scale,
						GLuint	mappingMode,
						bool lighting);
	void aplicaMaterial();
	void anulaMaterial();
	void agregaDescendiente(string nombre,Objeto *nuevoObjeto);
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

class Modelo : Objeto
{
  public:
	string nombreArchivo;
	GLMmodel *modelo;
	bool usaTexturas;
	bool desplazaTexturas;
	Modelo(string nombreArchivo);
    Modelo(string nombreArchivo,int modoTextura);
    ~Modelo();
	void forma();
};

class AlphaQuad : Objeto
{
public:
	GLfloat ancho;
	GLfloat alto;
	GLfloat texPosS;
	GLfloat texPosT;
	GLfloat texVelS;
	GLfloat texVelT;
	GLfloat texEscala;
	GLfloat texEscalaVel;
	GLfloat alpha;
	GLfloat alphaVel;
	GLuint  textura;
	GLuint  modoTextura;
	AlphaQuad(Escena *escenaActual,
			  string nombreTextura,
			  GLuint modoTextura,
			  GLfloat alpha,
			  GLfloat ancho,
			  GLfloat alto,
			  GLfloat texVelS,
			  GLfloat texVelT,
			  GLfloat texEscala,
			  GLfloat texEscalaVel,
			  GLfloat alphaVel);
	~AlphaQuad();
	void forma();
};


class Luz : Objeto
{
   public:
	 char tipo;
	 GLfloat posicion[4];
	 GLfloat color[4];
	 GLfloat direccion[3];
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
		map <string, GLuint> texturas;
		unsigned long currentFrame;
		bool muestraLuces;
		bool muestraNiebla;
		GLfloat densidadNiebla;
        GLfloat inicioNiebla;
		GLfloat finNiebla;
        GLfloat colorNiebla[4];
		
		Escena();
		~Escena();
		void agregaObjeto(string nombre,Objeto *nuevoObjeto);		
		void actualizaEscena();		
		void dibujaEscena();
		void cuentaframe();
		void defineLuz(string nombre,char tipo,GLfloat r,GLfloat g,GLfloat b);
		void posicionLuz(string nombre,GLfloat x,GLfloat y,GLfloat z);
	    void direccionLuz(string nombre,GLfloat x,GLfloat y,GLfloat z);
		void anguloLuz(string nombre,GLfloat angulo);
		void toggleLuz(string nombre);
		void ilumina();
		Luz *luz(int numero);
		void cargaTextura(string nombre,int type,int wrap,int filter);
		// Version corta, material con textura y alpha blend
		void modificaMaterial(string nombreModelo,string nombreMaterial,
				              string nombreTextura,GLuint wrap,GLfloat alpha);
		// Version extendida, material con textura y alpha blend + desplazamiento y escalamiento de textura
		void modificaMaterial(string nombreModelo,string nombreMaterial,string 
						      nombreTextura,GLuint wrap,GLfloat alpha,
							  GLfloat escalaTex,GLfloat velTexS,GLfloat velTexT);
        void defineNiebla(GLfloat inicio,GLfloat fin,GLfloat densidad,GLfloat r,GLfloat g,GLfloat b);
		void activaNiebla(bool activar);

     private:
	    GLbyte *gltLoadTGA(const char *szFileName, GLint *iWidth, GLint *iHeight, GLint *iComponents, GLenum *eFormat);		
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


