#include <stdio.h>
#define _USE_MATH_DEFINES
#include <math.h>
#include <string.h>
#include <stdlib.h>
#include "Escena.h"
#include "Interaccion.h"
#include "misComposiciones.h"
#include "misCamaras.h"

//Deshabilita la consola  (exclusivo para Windows - Visual Studio)
#pragma comment(linker, "/subsystem:\"windows\" /entry:\"mainCRTStartup\"")

//Variables globales
Escena *escena = new Escena();  //Escena actual
int currWidth,currHeight;       //Ancho y alto de la ventana grafica
GLfloat dtran=DELTA_TRAN;       //Delta de traslacion interactiva
GLfloat drot=DELTA_ROT;         //Delta de rotacion interactiva
bool leftMouse=false;           //Boton izquierdo oprimido
bool rightMouse=false;          //Boton derecho oprimido
bool middleMouse=false;         //Boton central oprimido
int lastMouseX=0;		        //Posicion previa de mouse en X
int lastMouseY=0;               //Posicion previa de mouse en Y
bool tecladoDefault=true;       //Determina si debe ejecutarse la interaccion default para teclado
bool mouseDefault=true;        //Determina si debe ejecutarse la interaccion default para mouse

void idle()
{
  static unsigned long time=glutGet(GLUT_ELAPSED_TIME);
  static unsigned long frametime=1000/30;
  
  if((glutGet(GLUT_ELAPSED_TIME)-time) > frametime)
  {      
	  escena->cuentaframe();
	  time=glutGet(GLUT_ELAPSED_TIME);
	  escena->actualizaEscena();
	  miIdle();	
	  glutPostRedisplay();
  }   
}

void render()
{		
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	 
	escena->ilumina();
	escena->dibujaEscena();
	glutSwapBuffers();	
}


void init(int left,int top,int width,int height,string title) {
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(left,top);
	glutInitWindowSize(width,height);
	glutCreateWindow(title.c_str());
	glClearColor(0.0,0.0,0.0,0.0);			
}

void redimensiona(int width,int height) {
  currWidth=width;
  currHeight=height;
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();    
  gluPerspective(activa->fovy,(GLdouble)width/(GLdouble)height,activa->near,activa->far);
  glTranslatef(activa->xview,activa->yview,activa->zview); 
  glRotatef(activa->xrot,1.0,0.0,0.0);
  glRotatef(activa->yrot,0.0,1.0,0.0);
  glRotatef(activa->zrot,0.0,0.0,1.0);
  glViewport(0,0,width,height);
  glMatrixMode(GL_MODELVIEW);
}

int main( int argc, char **argv) {
	glutInit(&argc,argv);	
	init(WIN_POSX,WIN_POSY,WIN_WIDTH,WIN_HEIGHT,"Framework Texture");
	glutDisplayFunc(render);
	glutIdleFunc(idle);
	glutReshapeFunc(redimensiona);
    glutSpecialFunc(keyboardSpec);
	glutKeyboardFunc(keyboard);
	glutMouseFunc(mouseClick);
    glutMotionFunc(mouseDrag);
	defineLuces();
	defineCamaras();
    creaEscena();
	glutMainLoop();
	return 0;
}














