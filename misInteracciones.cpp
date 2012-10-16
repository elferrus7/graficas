#include "misInteracciones.h"

//Interacciones particulares con teclado y mouse

void miTeclado(unsigned char key,int x,int y)
{
   //Definir comportamientos particulares para teclas simples
   switch (key) 
   {
		            
   }
   //Para desactivar comportamiento por default, hacer tecladoDefault=false 
}


void miTecladoEspecial(int key,int x,int y)
{
  //Definir comportamientos particulares para teclas especiales
  switch (key) 
  {

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








