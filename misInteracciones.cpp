#include "misInteracciones.h"

//Interacciones particulares con teclado y mouse

void miTeclado(unsigned char key,int x,int y)
{
   //Definir comportamientos particulares para teclas simples
   switch (key) 
   {
			/*case '+': activa->zview+=dtran;
					redimensiona(currWidth,currHeight);		                       
					break;

			case '-': activa->zview-=dtran;
					redimensiona(currWidth,currHeight);
					break;*/
			case '1': activa = camaraDefault;

			case '2': activa = camaraZenital;

			case 'd': activa->yrot+=drot;
					redimensiona(currWidth,currHeight);
					break;
			/*case 'w': activa->zrot+=drot;
					redimensiona(currWidth,currHeight);
					break;*/
			/*case 'z': activa->zrot+=drot;		  
					redimensiona(currWidth,currHeight);
					break;*/
					
			case 'a': activa->yrot-=drot;
					redimensiona(currWidth,currHeight);
					break;

			/*case 's': activa->zrot-=drot;
					redimensiona(currWidth,currHeight);
					break;*/

			/*case 'Z': activa->zrot-=drot;
					redimensiona(currWidth,currHeight);
					break;*/
						

		case ESCAPE: exit(0);
						break;
   }
   //Para desactivar comportamiento por default, hacer tecladoDefault=false 
}


void miTecladoEspecial(int key,int x,int y)
{
  //Definir comportamientos particulares para teclas especiales
  switch (key) 
  {
	  case GLUT_KEY_UP:        activa->zview+=dtran;
								   redimensiona(currWidth,currHeight);
								   break;

		case GLUT_KEY_DOWN:      activa->zview-=dtran;
								   redimensiona(currWidth,currHeight);
								   break;
		case GLUT_KEY_LEFT:      activa->xview-=dtran;
								   redimensiona(currWidth,currHeight);
								   break;

		case GLUT_KEY_RIGHT:     activa->xview+=dtran;
								   redimensiona(currWidth,currHeight);
								   break;
  }
  //Para desactivar comportamiento por default, hacer tecladoDefault=false 
}


void miMouseClick(int button, int state, int x, int y)
{
  //Definir comportamientos particulares para mouse click
 
  //Para desactivar comportamiento por default, hacer mouseDefault=false   
}

void miMouseDrag(int x, int y,GLfloat deltaX,GLfloat deltaY)
{
  //Definir comportamientos particulares para mouse drag
  
  //Para desactivar comportamiento por default, hacer mouseDefault=false 
}


void miIdle()
{
  //Definir acciones especiales que deben ejecutarse en el idle del ciclo de GLUT
  
}








