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
			case '1' : activa = camaraDefault; break;

			case '2' : activa = camaraZenital; break;

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

int rumbo=0;
int itr = 0;

void miIdle()
{
  //Definir acciones especiales que deben ejecutarse en el idle del ciclo de GLUT

	if(itr < 400){
		rumbo = 1;
	}else if( itr < 600){
		rumbo = 2;
	}else if( itr < 800){
		rumbo = 3;
	}else{
		rumbo = 4;
	}


	switch(rumbo){
	case 1: 
		escena->objetos["jeff"]->posX += 0.01;
		if(escena->objetos["jeff"]->posX == 10){
			escena->objetos["jeff"]->posX *= -1;
		}
		break;
	case 2: 
		escena->objetos["jeff"]->posX -= 0.01;
		if(escena->objetos["jeff"]->posX == 0){
			escena->objetos["jeff"]->posX *= -1;
		}
		break;
	case 3: 
		escena->objetos["jeff"]->posZ += 0.01;
		if(escena->objetos["jeff"]->posZ == 0){
			escena->objetos["jeff"]->posZ *= -1;
		}
		break;
	case 4: 
		escena->objetos["jeff"]->posZ -= 0.01;
		if(escena->objetos["jeff"]->posZ == -17){
			escena->objetos["jeff"]->posZ *= -1;
		}
		break;
	default: 
		escena->objetos["jeff"]->posX += 0.01;
		break;
	}

	itr++;

	if(itr > 800){
		itr = 0;
	}
}








