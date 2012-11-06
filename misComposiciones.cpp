#include "misComposiciones.h"

// Variables para la CASA
#define ALTOCASA	2.5
#define ANCHOPARED	0.25

void defineLuces()
{
    //escena->defineLuz("light0",'A', 0.084, 0.084, 0.084);
	escena->defineLuz("light0",'A', 0.2, 0.2, 0.2);
	escena->posicionLuz("light0", 0.25, 1.0, -2.0);

	//escena->defineLuz("light1",'D', 0.916, 0.916, 0.916);
	escena->defineLuz("light1",'D', 0.08, 0.08, 0.08);
	escena->posicionLuz("light1", 0.5, 1.0, -2.0);

	escena->defineLuz("light2",'E', 0.0, 0.1, 0.0);
	escena->posicionLuz("light2", 0.75, 1, -2.0);

    /*escena->defineLuz("light1",'E', 0.0, 1.0, 0.0);
	escena->posicionLuz("light1", 5.0, 0.0, 5.0);
	
	escena->defineLuz("light2",'D', 0.916, 0.916, 0.916);
	escena->posicionLuz("light2", 0.25, 1, -2.0);*/
	//escena->direccionLuz("light2", 0.0, 1.0, 0.0);
	//escena->anguloLuz("light2", 30.0);
	escena->muestraLuces = false;
}

void demuestraModelo()
{
  escena->agregaObjeto("ejemplo", (Objeto *) new Modelo("al"));
  escena->objetos["ejemplo"]->escalaUniforme(3.0);
}


void demuestraMateriales()
{ 

    //Esfera que sirve como Sky Dome. IMPORTANTE: lighting, el ultimo parametro de defineMaterial, es false 
    escena->agregaObjeto("skydome",(Objeto *) new Esfera(40.0,30,30,1.0,1.0,1.0));
    escena->objetos["skydome"]->velRotX=0.1;
	escena->objetos["skydome"]->defineMaterial(1.0,1.0,1.0,
										 1.0,1.0,1.0,
										 0.0,0.0,0.0,
										 0.0,0.0,0.0,
										 "agua.tga",GL_REPEAT,0.5,0.0,0.0,0.0,0.0,1.0,GL_SPHERE_MAP,false);


    //Modelo Texturizado
	escena->agregaObjeto("f-16", (Objeto *) new Modelo("f-16",TEX_SPHERE));
	escena->objetos["f-16"]->escalaUniforme(2.0);
	//escena->objetos["f-16"]->velRotX=1.0;
	escena->modificaMaterial("f-16", "blue", "chrome.tga", GL_REPEAT, 1.0,1.0,0.0,0.0);
    escena->modificaMaterial("f-16", "glass", "agua.tga", GL_REPEAT, 0.5);
	
	
	//Tres objetos iguales que copian el material del modelo con los diferentes modos de mapeo de texturas
	escena->agregaObjeto("tetera1",(Objeto *) new Tetera(1.0,1.0,0.0,1.0));
    escena->objetos["tetera1"]->velRotX=-1.0;
	escena->objetos["tetera1"]->posX=-5.0;
	escena->objetos["tetera1"]->posY=3.0;
	escena->objetos["tetera1"]->loopFrames=200;
	escena->objetos["tetera1"]->copiaMaterial("f-16","blue",GL_OBJECT_LINEAR);
	
	escena->agregaObjeto("tetera2",(Objeto *) new Tetera(1.0,1.0,0.0,1.0));
    escena->objetos["tetera2"]->velRotX=-1.0;
	escena->objetos["tetera2"]->posY=3.0;
	escena->objetos["tetera2"]->loopFrames=200;
	escena->objetos["tetera2"]->copiaMaterial("f-16","blue",GL_EYE_LINEAR);
	
	escena->agregaObjeto("tetera3",(Objeto *) new Tetera(1.0,1.0,0.0,1.0));
    escena->objetos["tetera3"]->velRotX=-1.0;
	escena->objetos["tetera3"]->posX=5.0;
	escena->objetos["tetera3"]->posY=3.0;
	escena->objetos["tetera3"]->loopFrames=200;
	escena->objetos["tetera3"]->copiaMaterial("f-16","blue",GL_SPHERE_MAP);
	
}

/* ---------------------------------------------------------------- */
/* ---------- Definición de métodos para cargar la casa ----------- */
/* ---------------------------------------------------------------- */
void exteriorCasa(){
	//escena->agregaObjeto("ParedSala-1", (Objeto *) new Paralelepipedo(5.0, ALTOCASA, ANCHOPARED));

	//escena->agregaObjeto("ParedBanio-Bodega", (Objeto *) new Paralelepipedo(6.0, ALTOCASA, ANCHOPARED));
	//escena->objetos["ParedBanio-Bodega"]->posX = 6.0;

	//escena->agregaObjeto("PV1", (Objeto *) new Paralelepipedo(5.5, ALTOCASA, ANCHOPARED));
	//escena->objetos["PV1"]->rotY = 90.0;

	escena->agregaObjeto("PV1", (Objeto *) new Cubo(1.0, 0.3, 0.3, 0.3));
	escena->objetos["PV1"]->escalaX = ANCHOPARED;
	escena->objetos["PV1"]->escalaY = ALTOCASA;
	escena->objetos["PV1"]->escalaZ = 5.5;
	
	//escena->agregaObjeto("PV2", (Objeto *) new Paralelepipedo(3.5, ALTOCASA, ANCHOPARED));
	//escena->objetos["PV2"]->rotY = 90.0;
	//escena->objetos["PV2"]->posZ = -5.5;
	escena->agregaObjeto("PV2", (Objeto *) new Cubo(1.0, 0.3, 0.3, 0.3));
	escena->objetos["PV2"]->escalaX = ANCHOPARED;
	escena->objetos["PV2"]->escalaY = ALTOCASA;
	escena->objetos["PV2"]->escalaZ = 3.5;
	escena->objetos["PV2"]->posZ = -5.5;
	
	//escena->agregaObjeto("PV3", (Objeto *) new Paralelepipedo(17.25, ALTOCASA, ANCHOPARED));
	//escena->objetos["PV3"]->posX = 13;
	//escena->objetos["PV3"]->rotY = 90.0;
	escena->agregaObjeto("PV3", (Objeto *) new Cubo(1.0, 0.3, 0.3, 0.3));
	escena->objetos["PV3"]->escalaX = ANCHOPARED;
	escena->objetos["PV3"]->escalaY = ALTOCASA;
	escena->objetos["PV3"]->escalaZ = 17.25;
	escena->objetos["PV3"]->posX = 13;

	//escena->agregaObjeto("PV4", (Objeto *) new Paralelepipedo(4.5, ALTOCASA, ANCHOPARED));
	//escena->objetos["PV4"]->posX = 5.25;
	//escena->objetos["PV4"]->rotY = 90.0;
	escena->agregaObjeto("PV4", (Objeto *) new Cubo(1.0, 0.3, 0.3, 0.3));
	escena->objetos["PV4"]->escalaX = ANCHOPARED;
	escena->objetos["PV4"]->escalaY = ALTOCASA;
	escena->objetos["PV4"]->escalaZ = 4.25;
	escena->objetos["PV4"]->posX = 5.25;

	//escena->agregaObjeto("PV5", (Objeto *) new Paralelepipedo(3, ALTOCASA, ANCHOPARED));
	//escena->objetos["PV5"]->posX = 6.5;
	//escena->objetos["PV5"]->posZ = -0.25;
	//escena->objetos["PV5"]->rotY = 90.0;
	escena->agregaObjeto("PV5", (Objeto *) new Cubo(1.0, 0.3, 0.3, 0.3));
	escena->objetos["PV5"]->escalaX = ANCHOPARED;
	escena->objetos["PV5"]->escalaY = ALTOCASA;
	escena->objetos["PV5"]->escalaZ = 3;
	escena->objetos["PV5"]->posX = 6.5;
	escena->objetos["PV5"]->posZ = -0.25;

	//escena->agregaObjeto("PV6", (Objeto *) new Paralelepipedo(3, ALTOCASA, ANCHOPARED));
	//escena->objetos["PV6"]->posX = 8.25;
	//escena->objetos["PV6"]->posZ = -0.25;
	//escena->objetos["PV6"]->rotY = 90.0;
	escena->agregaObjeto("PV6", (Objeto *) new Cubo(1.0, 0.3, 0.3, 0.3));
	escena->objetos["PV6"]->escalaX = ANCHOPARED;
	escena->objetos["PV6"]->escalaY = ALTOCASA;
	escena->objetos["PV6"]->escalaZ = 3;
	escena->objetos["PV6"]->posX = 8.25;
	escena->objetos["PV6"]->posZ = -0.25;

	//escena->agregaObjeto("PV7", (Objeto *) new Paralelepipedo(3, ALTOCASA, ANCHOPARED));
	//escena->objetos["PV7"]->posX = 6.5;
	//escena->objetos["PV7"]->posZ = -4.5;
	//escena->objetos["PV7"]->rotY = 90.0;
	escena->agregaObjeto("PV7", (Objeto *) new Cubo(1.0, 0.3, 0.3, 0.3));
	escena->objetos["PV7"]->escalaX = ANCHOPARED;
	escena->objetos["PV7"]->escalaY = ALTOCASA;
	escena->objetos["PV7"]->escalaZ = 3;
	escena->objetos["PV7"]->posX = 6.5;
	escena->objetos["PV7"]->posZ = -4.5;

	//escena->agregaObjeto("PV8", (Objeto *) new Paralelepipedo(3, ALTOCASA, ANCHOPARED));
	//escena->objetos["PV8"]->posX = 11.5;
	//escena->objetos["PV8"]->posZ = -4.5;
	//escena->objetos["PV8"]->rotY = 90.0;
	escena->agregaObjeto("PV8", (Objeto *) new Cubo(1.0, 0.3, 0.3, 0.3));
	escena->objetos["PV8"]->escalaX = ANCHOPARED;
	escena->objetos["PV8"]->escalaY = ALTOCASA;
	escena->objetos["PV8"]->escalaZ = 3;
	escena->objetos["PV8"]->posX = 11.5;
	escena->objetos["PV8"]->posZ = -4.5;

	//escena->agregaObjeto("PV9", (Objeto *) new Paralelepipedo(1, ALTOCASA, ANCHOPARED));
	//escena->objetos["PV9"]->posX = 3.5;
	//escena->objetos["PV9"]->posZ = -5.75;
	//escena->objetos["PV9"]->rotY = 90.0;
	escena->agregaObjeto("PV9", (Objeto *) new Cubo(1.0, 0.3, 0.3, 0.3));
	escena->objetos["PV9"]->escalaX = ANCHOPARED;
	escena->objetos["PV9"]->escalaY = ALTOCASA;
	escena->objetos["PV9"]->posX = 3.5;
	escena->objetos["PV9"]->posZ = -5.75;


	//escena->agregaObjeto("PV10", (Objeto *) new Paralelepipedo(1.25, ALTOCASA, ANCHOPARED));
	//escena->objetos["PV10"]->posX = 3.5;
	//escena->objetos["PV10"]->posZ = -7.5;
	//escena->objetos["PV10"]->rotY = 90.0;
	escena->agregaObjeto("PV10", (Objeto *) new Cubo(1.0, 0.3, 0.3, 0.3));
	escena->objetos["PV10"]->escalaX = ANCHOPARED;
	escena->objetos["PV10"]->escalaY = ALTOCASA;
	escena->objetos["PV10"]->escalaZ = 1.25;
	escena->objetos["PV10"]->posX = 3.5;
	escena->objetos["PV10"]->posZ = -7.5;

	//escena->agregaObjeto("PV11", (Objeto *) new Paralelepipedo(2, ALTOCASA, ANCHOPARED));
	//escena->objetos["PV11"]->posX = 5.25;
	//escena->objetos["PV11"]->posZ = -5.75;
	//escena->objetos["PV11"]->rotY = 90.0;
	escena->agregaObjeto("PV11", (Objeto *) new Cubo(1.0, 0.3, 0.3, 0.3));
	escena->objetos["PV11"]->escalaX = ANCHOPARED;
	escena->objetos["PV11"]->escalaY = ALTOCASA;
	escena->objetos["PV11"]->escalaZ = 1.25;
	escena->objetos["PV11"]->posX = 3.5;
	escena->objetos["PV11"]->posZ = -7.5;

	//escena->agregaObjeto("PV12", (Objeto *) new Paralelepipedo(2.25, ALTOCASA, ANCHOPARED));
	//escena->objetos["PV12"]->posX = 5.25;
	//escena->objetos["PV12"]->posZ = -7.5;
	//escena->objetos["PV12"]->rotY = 90.0;

	//escena->agregaObjeto("PV13", (Objeto *) new Paralelepipedo(1.25, ALTOCASA, ANCHOPARED));
	//escena->objetos["PV13"]->posX = 1.25;
	//escena->objetos["PV13"]->posZ = -5.5;
	//escena->objetos["PV13"]->rotY = 90.0;

	//escena->agregaObjeto("PV14", (Objeto *) new Paralelepipedo(3, ALTOCASA, ANCHOPARED));
	//escena->objetos["PV14"]->posX = 2.25;
	//escena->objetos["PV14"]->posZ = -9;
	//escena->objetos["PV14"]->rotY = 90.0;

	//escena->agregaObjeto("PV15", (Objeto *) new Paralelepipedo(1, ALTOCASA, ANCHOPARED));
	//escena->objetos["PV15"]->posX = 5.25;
	//escena->objetos["PV15"]->posZ = -10.75;
	//escena->objetos["PV15"]->rotY = 90.0;

	//escena->agregaObjeto("PV16", (Objeto *) new Paralelepipedo(0.75, ALTOCASA, ANCHOPARED));
	//escena->objetos["PV16"]->posX = 6.5;
	//escena->objetos["PV16"]->posZ = -9;
	//escena->objetos["PV16"]->rotY = 90.0;

	//escena->agregaObjeto("PV17", (Objeto *) new Paralelepipedo(0.75, ALTOCASA, ANCHOPARED));
	//escena->objetos["PV17"]->posX = 6.5;
	//escena->objetos["PV17"]->posZ = -10.75;
	//escena->objetos["PV17"]->rotY = 90.0;

	//escena->agregaObjeto("PV18", (Objeto *) new Paralelepipedo(0.75, ALTOCASA, ANCHOPARED));
	//escena->objetos["PV18"]->posX = 8;
	//escena->objetos["PV18"]->posZ = -7;
	//escena->objetos["PV18"]->rotY = 90.0;

	//escena->agregaObjeto("PV19", (Objeto *) new Paralelepipedo(7.75, ALTOCASA, ANCHOPARED));
	//escena->objetos["PV19"]->posX = 8;
	//escena->objetos["PV19"]->posZ = -9.25;
	//escena->objetos["PV19"]->rotY = 90.0;

	//escena->agregaObjeto("PV20", (Objeto *) new Paralelepipedo(2.25, ALTOCASA, ANCHOPARED));
	//escena->objetos["PV20"]->posX = 9.25;
	//escena->objetos["PV20"]->posZ = -7;
	//escena->objetos["PV20"]->rotY = 90.0;

	//escena->agregaObjeto("PV21", (Objeto *) new Paralelepipedo(0.75, ALTOCASA, ANCHOPARED));
	//escena->objetos["PV21"]->posX = 9.5;
	//escena->objetos["PV21"]->posZ = -9.25;
	//escena->objetos["PV21"]->rotY = 90.0;

	//escena->agregaObjeto("PV22", (Objeto *) new Paralelepipedo(2.5, ALTOCASA, ANCHOPARED));
	//escena->objetos["PV22"]->posX = 11.5;
	//escena->objetos["PV22"]->posZ = -9;
	//escena->objetos["PV22"]->rotY = 90.0;

	//escena->agregaObjeto("PH1", (Objeto *) new Paralelepipedo(5, ALTOCASA, ANCHOPARED));
	//escena->objetos["PH1"]->posX = 0.25;
	//escena->objetos["PH1"]->posZ = -0.25;

	//escena->agregaObjeto("PH2", (Objeto *) new Paralelepipedo(6.5, ALTOCASA, ANCHOPARED));
	//escena->objetos["PH2"]->posX = 6.5;
	//escena->objetos["PH2"]->posZ = -0.25;

	//escena->agregaObjeto("PH3", (Objeto *) new Paralelepipedo(1.25, ALTOCASA, ANCHOPARED));
	//escena->objetos["PH3"]->posX = 0.25;
	//escena->objetos["PH3"]->posZ = -4.5;

	//escena->agregaObjeto("PH4", (Objeto *) new Paralelepipedo(2.25, ALTOCASA, ANCHOPARED));
	//escena->objetos["PH4"]->posX = 3;
	//escena->objetos["PH4"]->posZ = -4.5;

	//escena->agregaObjeto("PH5", (Objeto *) new Paralelepipedo(0.75, ALTOCASA, ANCHOPARED));
	//escena->objetos["PH5"]->posX = 6.5;
	//escena->objetos["PH5"]->posZ = -3.5;

	//escena->agregaObjeto("PH6", (Objeto *) new Paralelepipedo(3.75, ALTOCASA, ANCHOPARED));
	//escena->objetos["PH6"]->posX = 8;
	//escena->objetos["PH6"]->posZ = -3.5;

	//escena->agregaObjeto("PH7", (Objeto *) new Paralelepipedo(4.75, ALTOCASA, ANCHOPARED));
	//escena->objetos["PH7"]->posX = 6.75;
	//escena->objetos["PH7"]->posZ = -4.75;

	//escena->agregaObjeto("PH8", (Objeto *) new Paralelepipedo(3, ALTOCASA, ANCHOPARED));
	//escena->objetos["PH8"]->posX = 2.5;
	//escena->objetos["PH8"]->posZ = -5.75;

	//escena->agregaObjeto("PH9", (Objeto *) new Paralelepipedo(1, ALTOCASA, ANCHOPARED));
	//escena->objetos["PH9"]->posX = 0.25;
	//escena->objetos["PH9"]->posZ = -6.75;

	//escena->agregaObjeto("PH10", (Objeto *) new Paralelepipedo(5, ALTOCASA, ANCHOPARED));
	//escena->objetos["PH10"]->posX = 0.25;
	//escena->objetos["PH10"]->posZ = -9;

	//escena->agregaObjeto("PH11", (Objeto *) new Paralelepipedo(3, ALTOCASA, ANCHOPARED));
	//escena->objetos["PH11"]->posX = 2.5;
	//escena->objetos["PH11"]->posZ = -12;

	//escena->agregaObjeto("PH12", (Objeto *) new Paralelepipedo(1.5, ALTOCASA, ANCHOPARED));
	//escena->objetos["PH12"]->posX = 6.5;
	//escena->objetos["PH12"]->posZ = -7.75;

	//escena->agregaObjeto("PH13", (Objeto *) new Paralelepipedo(2, ALTOCASA, ANCHOPARED));
	//escena->objetos["PH13"]->posX = 9.5;
	//escena->objetos["PH13"]->posZ = -9.25;

	//escena->agregaObjeto("PH14", (Objeto *) new Paralelepipedo(1.5, ALTOCASA, ANCHOPARED));
	//escena->objetos["PH14"]->posX = 6.75;
	//escena->objetos["PH14"]->posZ = -9.25;

	//escena->agregaObjeto("PH15", (Objeto *) new Paralelepipedo(0.25, ALTOCASA, ANCHOPARED));
	//escena->objetos["PH15"]->posX = 9.25;
	//escena->objetos["PH15"]->posZ = -10;

	//escena->agregaObjeto("PH16", (Objeto *) new Paralelepipedo(2.25, ALTOCASA, ANCHOPARED));
	//escena->objetos["PH16"]->posX = 9.25;
	//escena->objetos["PH16"]->posZ = -11.5;

	//escena->agregaObjeto("PH17", (Objeto *) new Paralelepipedo(1.25, ALTOCASA, ANCHOPARED));
	//escena->objetos["PH17"]->posX = 6.75;
	//escena->objetos["PH17"]->posZ = -11.5;

	//escena->agregaObjeto("PH18", (Objeto *) new Paralelepipedo(3.75, ALTOCASA, ANCHOPARED));
	//escena->objetos["PH18"]->posX = 9.25;
	//escena->objetos["PH18"]->posZ = -12.5;

	//escena->agregaObjeto("PH19", (Objeto *) new Paralelepipedo(5, ALTOCASA, ANCHOPARED));
	//escena->objetos["PH19"]->posX = 8;
	//escena->objetos["PH19"]->posZ = -17.25;

	//escena->agregaObjeto("Piso", (Objeto *) new Paralelepipedo(13.25, 9.0, 0.1));
	//escena->objetos["Piso"]->rotX=90;
	//escena->objetos["Piso"]->posZ=-9.0;

	//escena->agregaObjeto("Piso2", (Objeto *) new Paralelepipedo(11.0, 3.0, 0.1));
	//escena->objetos["Piso2"]->rotX=90;
	//escena->objetos["Piso2"]->posX=2.25;
	//escena->objetos["Piso2"]->posZ=-12.0;

	//escena->agregaObjeto("Piso3", (Objeto *) new Paralelepipedo(5.0, 5.25, 0.1));
	//escena->objetos["Piso3"]->rotX=90;
	//escena->objetos["Piso3"]->posX=8.25;
	//escena->objetos["Piso3"]->posZ=-17.0;

	//escena->agregaObjeto("Pasto1", (Objeto *) new Paralelepipedo(2.25, 8.0, 0.1));
	//escena->objetos["Pasto1"]->rotX=90;
	//escena->objetos["Pasto1"]->posZ=-16.75;

	//escena->agregaObjeto("Pasto2", (Objeto *) new Paralelepipedo(6.5, 4.75, 0.1));
	//escena->objetos["Pasto2"]->rotX=90;
	//escena->objetos["Pasto2"]->posX=2.25;
	//escena->objetos["Pasto2"]->posZ=-16.75;
}

void salaCasa(){
	escena->agregaObjeto("ParedSala-2", (Objeto *) new Paralelepipedo(4.0, ALTOCASA, ANCHOPARED));
	escena->objetos["ParedSala-2"]->posX = 4.75;
	escena->objetos["ParedSala-2"]->rotY = 90.0;

	escena->agregaObjeto("ParedSala-3", (Objeto *) new Paralelepipedo(2.0, ALTOCASA, ANCHOPARED));
	escena->objetos["ParedSala-3"]->posZ = -4;

	escena->agregaObjeto("ParedSala-4", (Objeto *) new Paralelepipedo(2.0, ALTOCASA, ANCHOPARED));
	escena->objetos["ParedSala-4"]->posX = 3;
	escena->objetos["ParedSala-4"]->posZ = -4;
}

void banio1(){
	escena->agregaObjeto("ParedBanio1-1", (Objeto *) new Paralelepipedo(3.0, ALTOCASA, ANCHOPARED));
	escena->objetos["ParedBanio1-1"]->posX = 6;
	escena->objetos["ParedBanio1-1"]->rotY = 90.0;

	escena->agregaObjeto("ParedBanio1-2", (Objeto *) new Paralelepipedo(0.5, ALTOCASA, ANCHOPARED));
	escena->objetos["ParedBanio1-2"]->posX = 6;
	escena->objetos["ParedBanio1-2"]->posZ = -3;
}

void jeff(){
	escena->agregaObjeto("jeff", (Objeto *) new Cubo(0.25, 1.0, 0.0, 0.0));
	escena->objetos["jeff"]->posX = 2.0;
	escena->objetos["jeff"]->posY = 0.5;
	escena->objetos["jeff"]->posZ = -16.0;
}

void creaCasa(){
	exteriorCasa();
	jeff();
	//salaCasa();	
	//banio1();
}


void creaEscena()
{
  //demuestraModelo();
	creaCasa();
    
    escena->agregaObjeto("cubo1", (Objeto*) new Cubo(1.0, 0.0, 0.0, 1.0));
    escena->objetos["cubo1"]->posX = -3.0;
    escena->objetos["cubo1"]->posY = 1.0;
}

