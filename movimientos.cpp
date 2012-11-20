#include "movimientos.h"

void redimensiona();

double degToRad(double deg)
{
	return deg * M_PI /180;
}

void moverAdelante(){

		Objeto *aux=escena->objetos["cuboAvatar"];
		//if(!collision(aux->rotY)){
			double rotYRad= degToRad(aux->rotY);
			aux->posZ-= dtran * (cos(rotYRad));
			aux->posX-=  dtran * (sin(rotYRad));
			camaraFP->xview=aux->posX+sin(degToRad(aux->rotY));
			camaraFP->zview=aux->posZ+cos(degToRad(aux->rotY));
		
		redimensiona(currWidth,currHeight);
	//}
}

void girarIzquierda(){
	Objeto *aux=escena->objetos["cuboAvatar"];
	//rota al avatar hacia izquierda
	//aux->rotY+=MOUSE_MUL_RY * drot;
	aux->rotY+=12.5 * drot;
	//rota la camara hacia izquierda
	//camaraPrimeraPersona->yrot-=MOUSE_MUL_RY * drot;

	//traslada camara
	camaraFP->xview=aux->posX+sin(degToRad(aux->rotY));
	camaraFP->zview=aux->posZ+cos(degToRad(aux->rotY));

	redimensiona(currWidth, currHeight);
}

void girarDerecha(){
	Objeto *aux=escena->objetos["cuboAvatar"];
	//rota al avatar hacia derecha	
	//aux->rotY-=MOUSE_MUL_RY * drot;
	aux->rotY-=12.5 * drot;
	//traslada camara
	camaraFP->xview=aux->posX+sin(degToRad(aux->rotY));
	camaraFP->zview=aux->posZ+cos(degToRad(aux->rotY));
	//rota la camara hacia derecha
	//camaraPrimeraPersona->yrot+=MOUSE_MUL_RY * drot;
	//camaraPrimeraPersona->xview+=20;	

	redimensiona(currWidth, currHeight);
}