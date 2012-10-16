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
Camara *camaraZenital = new Camara(0.0,0.0,-20.0,90.0,0.0,0.0,100.0,1.0,45.0);
Camara *activa=camaraFrontal;
int currWidth,currHeight;
GLfloat dtran=0.1;
GLfloat drot=0.5;
bool leftMouse;       //Boton izquierdo oprimido
bool rightMouse;      //Boton derecho oprimido
bool middleMouse;     //Boton central oprimido
int lastMouseX;       //Posicion previa de mouse en X
int lastMouseY;       //Posicion previa de mouse en Y

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
    // Agregamos luz tipo Diffuse con color (rosa), posicionamos y movemos
	escena->defineLuz("light0",'E', 1.0, 1.0, 1.0);
	escena->posicionLuz("light0", -3.0, 20.0, -1.0);	
	escena->defineLuz("light1",'E', 1.0, 1.0, 1.0);
	escena->posicionLuz("light1", 3.0, 20.0, 1.0);	
	//Muestra esferas en las posiciones de las luces
	escena->muestraLuces=false;
}

void sol(){
	escena->agregaObjeto("sol",(Objeto *) new Esfera(3.0,40,40,1.0,1.0,0.0));
	escena->objetos["sol"]->rotX=90.0;
	escena->objetos["sol"]->velRotZ=0.4;
}

void mercurio(){
	escena->objetos["sol"]->agregaDescendiente("mercurio", (Objeto *) new Esfera(0.5, 30,30, 0.21, 0.35, 0.42) );
	escena->objetos["sol"]->descendientes["mercurio"]->posX=5.0;
}

void venus(){
	escena->objetos["sol"]->agregaDescendiente("venus", (Objeto *) new Esfera(0.7, 30,30, 0.89, 0.47, 0.20));
	escena->objetos["sol"]->descendientes["venus"]->posX=-7.0;
	escena->objetos["sol"]->descendientes["venus"]->posY=-5.0;
}

void tierra(){
	escena->objetos["sol"]->agregaDescendiente("tierra",(Objeto *) new Esfera(0.5,40,40,0.0,0.0,1.0));
	escena->objetos["sol"]->descendientes["tierra"]->posX=7.5;
	escena->objetos["sol"]->descendientes["tierra"]->posY=7.0;
	escena->objetos["sol"]->descendientes["tierra"]->velRotZ=5.0;
   
	escena->objetos["sol"]->descendientes["tierra"]->agregaDescendiente("luna",(Objeto *) new Esfera(0.1,20,20,1.0,1.0,1.0));
	escena->objetos["sol"]->descendientes["tierra"]->descendientes["luna"]->posX=1.0;
    
}

void marte(){
	escena->objetos["sol"]->agregaDescendiente("marte", (Objeto *) new Esfera (0.35, 30, 30, 0.83, 0.1, 0.12));
	escena->objetos["sol"]->descendientes["marte"]->posX=-11.5;
}

void jupiter(){
	escena->objetos["sol"]->agregaDescendiente("jupiter", (Objeto *) new Esfera (1.5, 30, 30, 0.8, 0.8, 1.0));
	escena->objetos["sol"]->descendientes["jupiter"]->posX=7.0;
	escena->objetos["sol"]->descendientes["jupiter"]->posY=-11.0;
}

void saturno(){
	escena->objetos["sol"]->agregaDescendiente("saturno", (Objeto *) new Esfera (0.7, 30, 30, 0.82, 0.89, 0.19));
	escena->objetos["sol"]->descendientes["saturno"]->posX=-7.0;
	escena->objetos["sol"]->descendientes["saturno"]->posY=11.0;
}

void urano(){
	escena->objetos["sol"]->agregaDescendiente("urano", (Objeto *) new Esfera (0.7, 30, 30, 0.83, 0.83, 0.83));
	escena->objetos["sol"]->descendientes["urano"]->posX=21.0;
}

void neptuno(){
	escena->objetos["sol"]->agregaDescendiente("neptuno", (Objeto *) new Esfera (0.5, 30, 30, 0.41, 0.35, 0.80));
	escena->objetos["sol"]->descendientes["neptuno"]->posX=21.0;
	escena->objetos["sol"]->descendientes["neptuno"]->posY=-9.0;

}

void pluton(){
	escena->objetos["sol"]->agregaDescendiente("pluton", (Objeto *) new Esfera (0.25, 30, 30, 0.42, 0.42, 0.42));
	escena->objetos["sol"]->descendientes["pluton"]->posX=-15.0;
	escena->objetos["sol"]->descendientes["pluton"]->posY=9.0;
}

void solar()
{
   sol();
   // TO DO: Agregar otros planetas
   
   //Agregar tierra y luna
   
   mercurio();
   venus();
   tierra();
   marte();
   jupiter();
   saturno();
   urano();
   neptuno();
   pluton();
}

void creaEscena()
{ 
    escena->shadeModel=GL_FLAT;
    solar();
}



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


void mouseClick(int button, int state, int x, int y)
{
	switch (button) {
		case GLUT_LEFT_BUTTON:   leftMouse = (state==GLUT_DOWN);
								 break;
								 
		case GLUT_MIDDLE_BUTTON: middleMouse = (state==GLUT_DOWN);
							     break;
								 
		case GLUT_RIGHT_BUTTON:  rightMouse = (state==GLUT_DOWN);
							     break;

	}
	if (state==GLUT_UP) 
	{
	      //Reinicia las posiciones previas para permitir movimientos acumulativos
		  lastMouseX=0;
          lastMouseY=0;
	}
}

void mouseDrag(int x, int y)
{
  GLfloat deltaX=(lastMouseX == 0) ? MOUSE_DELTA_MIN : (GLfloat)(x-lastMouseX)/currWidth;
  GLfloat deltaY=(lastMouseY == 0) ? MOUSE_DELTA_MIN : (GLfloat)(lastMouseY-y)/currHeight;
  
   if (leftMouse) //Desplazamiento horizontal/vertical
	{
		activa->xview+=MOUSE_MUL_TX * deltaX;
		activa->yview+=MOUSE_MUL_TY * deltaY;
		redimensiona(currWidth, currHeight);
	}
    if (middleMouse) //Zoom in/Zoom out
	{
		activa->zview+=MOUSE_MUL_TZ * deltaY;
		redimensiona(currWidth, currHeight);
	}
	if (rightMouse) //Movimiento horizontal, rotacion respecto a eje Y; Movimiento vertical, rotacion respecto a eje X
	{
	   activa->yrot+=MOUSE_MUL_RY * deltaX;
	   activa->xrot+=MOUSE_MUL_RX * deltaY;
	   redimensiona(currWidth, currHeight);
	}
  lastMouseX=x;
  lastMouseY=y;
}


int main( int argc, char **argv) {
    // Version
	glutInit(&argc,argv);	
	init(100,100,800,400,"Framework Hierarchy");
	glutDisplayFunc(render);
	glutIdleFunc(idle);
	glutReshapeFunc(redimensiona);
    glutSpecialFunc(keyboardSpec);
	glutKeyboardFunc(keyboard);
	// Funciones para interactuar con mouse
	glutMouseFunc(mouseClick);
    glutMotionFunc(mouseDrag);
	defineLuces();
    creaEscena();
	glutMainLoop();
	return 0;
}














