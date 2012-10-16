#include "Escena.h"
#include <iostream>


//Metodos de Objeto

// Constructor
Objeto::Objeto()
{
	colorR=1.0;
	colorG=1.0;
	colorB=1.0;
	posX=0.0;
	posY=0.0;
	posZ=0.0;
	velX=0.0;
	velY=0.0;
	velZ=0.0;
	rotX=0.0;
	rotY=0.0;
	rotZ=0.0;
	velRotX=0.0;
	velRotY=0.0;
	velRotZ=0.0;
	escalaX=1.0;
	escalaY=1.0;
	escalaZ=1.0;
	velEscalaX=0.0;
	velEscalaY=0.0;
	velEscalaZ=0.0;
	displayList=0;
	loopFrames=0;
	pivotX=0.0;
    pivotY=0.0;
	pivotZ=0.0;
}

// Destructor (vacio)
Objeto::~Objeto()
{
  delete this;
}

// Actualiza las transformaciones del objeto
void Objeto::actualiza()
{
	if(loopFrames)
		if((escenaActual->currentFrame % loopFrames)==0)
		// Invierte el sentido de las transformaciones cada loopFrames
		{
			velX= -1.0*velX;
			velY= -1.0*velY;
			velZ= -1.0*velZ;
			velRotX= -1.0*velRotX;
			velRotY= -1.0*velRotY;
			velRotZ= -1.0*velRotZ;
			velEscalaX = -1.0*velEscalaX;
			velEscalaY = -1.0*velEscalaY;
			velEscalaZ = -1.0*velEscalaZ;
		}
	posX+=velX;
	posY+=velY;
	posZ+=velZ;
	rotX+=velRotX;
	rotY+=velRotY;
	rotZ+=velRotZ;
	escalaX+=velEscalaX;
	escalaY+=velEscalaY;
	escalaZ+=velEscalaZ;
	// Actualizar las transformaciones de los descendientes
	
	map<string, Objeto *>::const_iterator iter;   
	for (iter=descendientes.begin(); iter != descendientes.end(); ++iter) 
    {
	   Objeto *o=(Objeto *)iter->second;
	   o->actualiza();	  	   
    }
	
}


// Aplica las transformaciones y dibuja el objeto transformado
void Objeto::dibuja()
{    
    glEnable(GL_COLOR_MATERIAL);
	glPushMatrix();
	glTranslatef(posX,posY,posZ);
	glScalef(escalaX,escalaY,escalaZ);
	glRotatef(rotX,1.0+pivotX,0.0+pivotY,0.0+pivotZ);
	glRotatef(rotY,0.0+pivotX,1.0+pivotY,0.0+pivotZ);
	glRotatef(rotZ,0.0+pivotX,0.0+pivotY,1.0+pivotZ);
	glColor3f(colorR,colorG,colorB);
    forma();
	// Dibujar los descendientes
	
	map<string, Objeto *>::const_iterator iter;   
    for (iter=descendientes.begin(); iter != descendientes.end(); ++iter) 
    {
	   Objeto *o=(Objeto *)iter->second;
	   o->dibuja();	  	   
    }
	
	glPopMatrix();
	glColor3f(1.0,1.0,1.0);
}

// Agregar descendientes

void Objeto::agregaDescendiente(string nombre,Objeto *nuevoObjeto)
{
	descendientes[nombre]=nuevoObjeto;	
	descendientes[nombre]->escenaActual=this->escenaActual;
}



//Metodos del cubo

// Constructor
Cubo::Cubo(GLfloat lado,GLfloat r,GLfloat g,GLfloat b):Objeto()
{
	this->lado = lado;
	this->colorR = r;
	this->colorG = g;
	this->colorB = b;
}

// Forma de cubo
void Cubo::forma()
{
   glutSolidCube(lado);
}


//Metodos de la tetera

// Constructor
Tetera::Tetera(GLfloat tam,GLfloat r,GLfloat g,GLfloat b):Objeto()
{
	this->tam = tam;
	this->colorR = r;
	this->colorG = g;
	this->colorB = b;
}

// Forma de cubo
void Tetera::forma()
{
   glutSolidTeapot(tam);
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

//Metodos de Esfera

// Constructor
Esfera::Esfera(GLfloat radio,GLfloat meridianos,GLfloat paralelos,GLfloat r,GLfloat g,GLfloat b):Objeto()
{
	this->radio = radio;
	this->meridianos = meridianos;
	this->paralelos = paralelos;
	this->colorR = r;
	this->colorG = g;
	this->colorB = b;
}


// Forma de esfera
void Esfera::forma()
{
   glutSolidSphere(radio,meridianos,paralelos);
}


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
	    // TODO: Agregar normal
		M3DVector3f normal;
		m3dFindNormal(normal, avion[i][0], avion[i][1],avion[i][2]);
		glNormal3fv(normal);
		glVertex3fv(avion[i][0]);
		glVertex3fv(avion[i][1]);
		glVertex3fv(avion[i][2]);
	}
    glEnd();
}


//Metodos de Luz
Luz::Luz(char tipo):Objeto()
{
	this->tipo=tipo;
	this->activa=false;
	this->posicion[0]=0.0;
	this->posicion[1]=0.0;
	this->posicion[2]=0.0;
	this->posicion[3]=0.0;
	this->direccion[0]=0.0;
	this->direccion[1]=0.0;
	this->direccion[2]=0.0;
	this->direccion[3]=0.0;
	this->color[0]=1.0;
	this->color[1]=1.0;
	this->color[2]=1.0;
	this->color[3]=1.0;
	this->angulo=0.0;
	this->glLight=0;
}

void Luz::forma()
{
  if (this->escenaActual->muestraLuces && this->activa)
  {
	glColor3fv(this->color);
	glutWireSphere(0.3, 10, 10);
  }
}


//Metodos de Escena


// Constructor
Escena::Escena()
{
  currentFrame=0;
  muestraLuces=false;
  shadeModel=GL_SMOOTH;
  char nombre[MAX_NOMBRE];
  for (int i=0; i<MAX_LUCES; i++) 
  {
     sprintf(nombre,"light%d",i);
	 objetos[nombre]=(Objeto *) new Luz('I');	
	 objetos[nombre]->escenaActual=this;  
	 Luz *l=(Luz *) objetos[nombre];
	 l->activa=false;
	 l->glLight=GL_LIGHT0+i;	  
  }
}


// Destructor
Escena::~Escena()
{
   map<string, Objeto *>::const_iterator iter;   
   for (iter=objetos.begin(); iter != objetos.end(); ++iter) 
   {
	   Objeto *o=(Objeto *)iter->second;
	   delete o;	  	   
   }
}

void Escena::actualizaEscena()
{
   map<string, Objeto *>::const_iterator iter;   
   for (iter=objetos.begin(); iter != objetos.end(); ++iter) 
   {
	   Objeto *o=(Objeto *)iter->second;
	   o->actualiza();
   } 
   for (int i=0; i<MAX_LUCES; i++) 
   {
	 Luz *l=luz(i);
	 Objeto *o=(Objeto *) l;
	 l->posicion[0]=o->posX;
	 l->posicion[1]=o->posY;
	 l->posicion[2]=o->posZ;
	 l->posicion[3]=0.0;
	 l->color[0]=o->colorR;
	 l->color[1]=o->colorG;
	 l->color[2]=o->colorB;
	 l->color[3]=1.0;
   }
}

void Escena::agregaObjeto(string nombre,Objeto *nuevoObjeto)
{
	objetos[nombre]=nuevoObjeto;	
	objetos[nombre]->escenaActual=this;

}


void Escena::dibujaEscena()
{
   map<string, Objeto *>::const_iterator iter;   
   for (iter=objetos.begin(); iter != objetos.end(); ++iter) 
   {
	   Objeto *o=(Objeto *)iter->second;
	   o->dibuja();	  	   
   } 
}


void Escena::cuentaframe()
{	  
	  currentFrame++; 
}

Luz *Escena::luz(int numero)
{
  char nombre[MAX_NOMBRE];
  sprintf(nombre,"light%d",numero);
  return (Luz *) objetos[nombre];
}


void Escena::defineLuz(char *nombre,char tipo,GLfloat r,GLfloat g,GLfloat b)
{
	Luz *l=(Luz *) objetos[nombre];
	Objeto *o=(Objeto *) l;
	l->tipo=tipo;
	o->colorR=r;
	o->colorG=g;
	o->colorB=b;
	l->color[0]=o->colorR;
	l->color[1]=o->colorG;
	l->color[2]=o->colorB;
	l->color[3]=1.0;
	l->activa=true;
}

void Escena::posicionLuz(char *nombre,GLfloat x,GLfloat y,GLfloat z)
{
	Luz *l=(Luz *) objetos[nombre];
	Objeto *o=(Objeto *) l;
    o->posX=x;
	o->posY=y;
	o->posZ=z;
	l->posicion[0]=o->posX;
	l->posicion[1]=o->posY;
	l->posicion[2]=o->posZ;
	l->posicion[3]=0.0;
}

void Escena::direccionLuz(char *nombre,GLfloat x,GLfloat y,GLfloat z)
{
	Luz *l=(Luz *) objetos[nombre];
	l->direccion[0]=x;
	l->direccion[1]=y;
	l->direccion[2]=z;
	l->direccion[3]=0.0;
}

void Escena::anguloLuz(char *nombre,GLfloat angulo)
{
	Luz *l=(Luz *) objetos[nombre];
	l->angulo=angulo;
}

void Escena::toggleLuz(char *nombre)
{
	Luz *l=(Luz *) objetos[nombre];
	if(l->tipo=='I')
	  // Si la luz es Indefinida, siempre se desactiva
	  l->activa=false;
	else
	  // Si la luz es de otro tipo, se invierte el estado de activa
	  l->activa=!(l->activa);
}

void Escena::ilumina()
{  
  glEnable(GL_LIGHTING);
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_NORMALIZE);
  glEnable(GL_COLOR_MATERIAL);
  glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER,GL_TRUE);
  glShadeModel(shadeModel);
  for (int i=0; i<MAX_LUCES; i++) 
  {
	 Luz *l=luz(i);
	 if (l->activa && l->tipo!='I') 
	   {
		 switch (l->tipo) {
			 case 'A': // Luz Ambiente
					   glLightfv(l->glLight,GL_AMBIENT,l->color);
				       break;
					   
			 case 'D': // Luz Difusa
					   glColorMaterial(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE);
					   glLightfv(l->glLight,GL_DIFFUSE,l->color);
					   glLightfv(l->glLight,GL_POSITION,l->posicion);
				       break;
					   
			 case 'E': // Luz Especular
					   glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, l->color);
					   glMaterialf(GL_FRONT_AND_BACK,GL_SHININESS,SPECULAR_SHININESS);
					   glLightfv(l->glLight,GL_SPECULAR,l->color);
					   glLightfv(l->glLight,GL_POSITION,l->posicion);
				       break;  
					    
			 case 'S': // Spot Light
					   glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, l->color);
					   glMaterialf(GL_FRONT_AND_BACK,GL_SHININESS,SPECULAR_SHININESS);
					   glLightfv(l->glLight,GL_SPECULAR,l->color);
					   glLightfv(l->glLight,GL_POSITION,l->posicion);
					   glLightfv(l->glLight, GL_SPOT_DIRECTION, l->direccion);
					   glLightf(l->glLight, GL_SPOT_CUTOFF, l->angulo);
					   
				       break; 
					   
		 }
		 glEnable(l->glLight);
	   }
	 else 
	   {
	     // Luz indefinida o inactiva
		 glDisable(l->glLight);
	   }

  }
}



// Metodos de Camara


Camara::Camara(GLfloat xview,GLfloat yview,GLfloat zview,
               GLfloat xrot,GLfloat yrot,GLfloat zrot,
               GLfloat far,GLfloat near,GLfloat fovy)
{
  this->xview=xview;
  this->yview=yview;
  this->zview=zview;
  this->xrot=xrot;
  this->yrot=yrot;
  this->zrot=zrot;
  this->far=far;
  this->near=near;
  this->fovy=fovy;
}

float rfloat(float min,float max)
{
   min*=1000;
   max*=1000;
   return (min+(rand() % (long)(max-min)))/1000;
}

float rfloat(float max)
{
   return rfloat(0.0,max);
}

float rcolor()
{
  return rfloat(1.0);
}

int rint(int min,int max)
{
   return min+rand() % (max-min);
}

int rint(int max)
{
   return rand() % max;
}


