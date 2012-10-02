//#define GLUT_BUILDING_LIB
#include <stdio.h>
#define _USE_MATH_DEFINES
#include <math.h>
#include <string.h>
#include <stdlib.h>
#include "Escena.h"
#define ESCAPE 27

//Deshabilita la consola  (Windows - Visual Studio)
//#pragma comment(linker, "/subsystem:\"windows\" /entry:\"mainCRTStartup\"")

Escena *escena = new Escena();
Camara *camaraFrontal = new Camara(0.0,-3.0,-20.0,0.0,0.0,0.0,100.0,1.0,45.0);
Camara *camaraZenital = new Camara(0.0,0.0,-100.0,90.0,0.0,0.0,100.0,1.0,45.0);
Camara *activa=camaraFrontal;
int currWidth,currHeight;
GLfloat dtran=0.1;
GLfloat drot=0.5;

void idle()
{
  static unsigned long time=glutGet(GLUT_ELAPSED_TIME);
  static unsigned long frametime=1000/30;
  if((glutGet(GLUT_ELAPSED_TIME)-time) > frametime)
  {      

	  escena->cuentaframe();
	  time=glutGet(GLUT_ELAPSED_TIME);
	  escena->actualizaEscena();	
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

void defineLuces()
{
	//Agremamos luz tipo de Defese
	escena->defineLuz("light0",'E',1.0, 1.0, 1.0);
	escena->posicionLuz("light0",-3.0,20.0,-1.0);

	escena->defineLuz("light1",'E',1.0, 1.0, 1.0);
	escena->posicionLuz("light1",3.0,20.0,1.0);

    /*escena->defineLuz("light0",'E', 1.0, 0.5, 0.5);
	escena->posicionLuz("light0", 3.0, 3.0, 1.0);
	escena->objetos["light0"]->velX = 0.1;
	escena->objetos["light0"]->loopFrames = 100;
	//Agreamos otra luz tipo espcuclar 'E' con color wherever, posicionamos y giramos 
	escena->defineLuz("light1",'A', 0.5, 1.0, 0.5);
	escena->posicionLuz("light1", -3.0, 3.0, 1.0);
	escena->objetos["light1"]->velX = 0.1;
	escena->objetos["light1"]->loopFrames = 100;*/

	//Muesta esferas en las posiciones de las luces
	escena->muestraLuces=true;
}

void piramide(char *prefijo,int escalones, GLfloat tamano, GLfloat posX)
{
	char nombre[25];
	for (int i = 0; i < escalones; i++)
	{
		sprintf(nombre,prefijo,i);
		escena->agregaObjeto(nombre,(Objeto *) new Cubo(tamano,rcolor(),rcolor(),rcolor()));
		escena->objetos[nombre]->posY = i * tamano;
		escena->objetos[nombre]->posX = posX;
		escena->objetos[nombre]->velRotX = 1.0;
		escena->objetos[nombre]->velY = 0.1 * i;
		escena->objetos[nombre]->loopFrames = 100;
		escena->objetos[nombre]->escalaX = escalones-i;
		escena->objetos[nombre]->escalaZ = escalones-i;
	}
}

void creaEscena()
{
	piramide("uno%d",25,0.75,0.0);
	//piramide("dps%d",15,0.3,5.0);
}

/*void creaEscena()
{ 
	piramide(7,0.5);
    /*escena->agregaObjeto("avion",(Objeto *) new Avion(0.0,0.0,1.0));
    escena->objetos["avion"]->escalaX=0.07;
    escena->objetos["avion"]->escalaY=0.07;
    escena->objetos["avion"]->escalaZ=0.07;
	escena->objetos["avion"]->posX=-5.0;
    escena->objetos["avion"]->velRotX=1.0;
	
	escena->agregaObjeto("cilindro", (Objeto *) new Cilindro(1.0,2.0,20,1.0,0.5,0.0));
	escena->objetos["cilindro"]->velRotX=1.0;
	
	escena->agregaObjeto("tetera",(Objeto *) new Tetera(2.0,1.0,1.0,0.0));
	escena->objetos["tetera"]->posX=5.0;
    escena->objetos["tetera"]->velRotX=1.0;*/
/*	
}*/

void init(int left,int top,int width,int height,char* title) {
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(left,top);
	glutInitWindowSize(width,height);
	glutCreateWindow(title);
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

void keyboardSpec(int key,int x,int y)
{
	switch(key)
	{
	  case GLUT_KEY_UP:        activa->yview+=dtran;
		                       redimensiona(currWidth,currHeight);
		                       break;

	  case GLUT_KEY_DOWN:      activa->yview-=dtran;
		                       redimensiona(currWidth,currHeight);
		                       break;

	  case GLUT_KEY_PAGE_UP:   activa->zview+=dtran;
		                       redimensiona(currWidth,currHeight);
		                       break;

	  case GLUT_KEY_PAGE_DOWN: activa->zview-=dtran;
		                       redimensiona(currWidth,currHeight);
		                       break;

	  case GLUT_KEY_LEFT:      activa->xview-=dtran;
		                       redimensiona(currWidth,currHeight);
		                       break;

	  case GLUT_KEY_RIGHT:     activa->xview+=dtran;
		                       redimensiona(currWidth,currHeight);
		                       break;
							   
	  case GLUT_KEY_F1:        escena->toggleLuz("light0");
							   break;
							   
	  case GLUT_KEY_F2:        escena->toggleLuz("light1");
							   break;
							   
	  case GLUT_KEY_F3:        escena->toggleLuz("light2");
							   break;
							   
	  case GLUT_KEY_F4:        escena->toggleLuz("light3");
							   break;
							   
	  case GLUT_KEY_F5:        escena->toggleLuz("light4");
							   break;
							   
	  case GLUT_KEY_F6:        escena->toggleLuz("light5");
							   break;
							   
	  case GLUT_KEY_F7:        escena->toggleLuz("light6");
							   break;
							   
	  case GLUT_KEY_F8:        escena->toggleLuz("light7");
							   break;							   							   
	}
}

void keyboard(unsigned char key,int x,int y)
{	
	switch(key)
	{
	    case '+': activa->zview+=dtran;
		          redimensiona(currWidth,currHeight);		                       
			      break;



	    case '-': activa->zview-=dtran;
		          redimensiona(currWidth,currHeight);
		          break;

		  case 'x': activa->xrot+=drot;
					redimensiona(currWidth,currHeight);
					break;
		  case 'y': activa->yrot+=drot;
					redimensiona(currWidth,currHeight);
					break;
		  case 'z': activa->zrot+=drot;		  
					redimensiona(currWidth,currHeight);
					break;

		  case 'X': activa->xrot-=drot;
					redimensiona(currWidth,currHeight);
					break;

		  case 'Y': activa->yrot-=drot;
					redimensiona(currWidth,currHeight);
					break;

		  case 'Z': activa->zrot-=drot;
					redimensiona(currWidth,currHeight);
					break;
					
		  case '1': activa=camaraFrontal;
		            redimensiona(currWidth,currHeight);
		            break;
		            
		  case '2': activa=camaraZenital;
		            redimensiona(currWidth,currHeight);
		            break;
		            



		case ESCAPE: exit(0);
			         break;
	}
}


int main( int argc, char **argv) {
    // Version
	glutInit(&argc,argv);	
	init(100,100,800,400,"Framework Lighting");
	glutDisplayFunc(render);
	glutIdleFunc(idle);
	glutReshapeFunc(redimensiona);
    glutSpecialFunc(keyboardSpec);
	glutKeyboardFunc(keyboard);
	defineLuces();
    creaEscena();
	glutMainLoop();
	return 0;
}














