#include "misComposiciones.h"

// Variables para la CASA
#define ALTOCASA	2.5
#define ANCHOPARED	0.25

void defineLuces()
{
    escena->defineLuz("light0",'D', 1.0, 1.0, 1.0);
	escena->posicionLuz("light0", 0.0, 3.0, 1.0);
	
    escena->defineLuz("light1",'E', 1.0, 1.0, 1.0);
	escena->posicionLuz("light1", 1.0, -2.0, 1.0);
	
	escena->defineLuz("light2",'S', 1.0, 1.0, 1.0);
	escena->posicionLuz("light2", 0.0, 8.0, 0.0);
	escena->direccionLuz("light2", 0.0, -1.0, 0.0);
	escena->anguloLuz("light2", 30.0);
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

void particulasAlpha()
{
    char nombre[20];
    for(int i=0; i<200; i++){
        sprintf(nombre, "hoja%d",i);
        escena->agregaObjeto(nombre, (Objeto *) new AlphaQuad(escena,"hoja.tga",GL_REPEAT,1.0,5,5,0,0,1.0,0,0));
        escena->objetos[nombre]->velRotX = rfloat(-2.0, 2.0);
        escena->objetos[nombre]->velRotY = rfloat(-2.0, 2.0);
        escena->objetos[nombre]->velRotZ = rfloat(-2.0, 2.0);
        escena->objetos[nombre]->loopFrames = 60;
    }
    
}

void muestraAlphaQuad()
{
    escena->agregaObjeto("hojas", (Objeto *) new AlphaQuad(escena,"agua.tga",GL_REPEAT,0.8,5,5,0.01,0.01,0.5,0,0));
    //escena->agregaObjeto("ejemplo", (Objeto *) new Modelo("al"));
}

void pruebaKeyFrames()
{
    escena->agregaObjeto("cubo", (Objeto *) new Cubo(1.0,0.0,0.0,1.0));
    escena->objetos["cubo"]->agregaKeyFrame(0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0, 1.0, 1.0);
    escena->objetos["cubo"]->agregaKeyFrame(30.0, 7.0, 0.0, 0.0, 0.0, 0.0, 40.0, 1.0, 1.0, 1.0);
    escena->objetos["cubo"]->agregaKeyFrame(100.0, -10.0, -10.0, 0.0, 0.0, 180.0, 0.0, 1.0, 1.0, 1.0);
    escena->objetos["cubo"]->agregaKeyFrame(200.0, 0.0, 0.0, 0.0, 0.0, 0.0, 360.0, 1.0, 1.0, 1.0);
}

void cargaPoses(){
    char nombre[10];
    GLfloat x = -10;
    for (int i=0; i<= 5; i++) {
        sprintf(nombre, "pose%d",i);
        escena->agregaObjeto(nombre, (Objeto *) new Modelo(nombre));
        escena->objetos[nombre]->posX = x;
        x += 2.0;
    }
}

void pruebaPoses(){
    escena->agregaObjeto("poses", (Objeto *) new Poses("pose%d",5,1));
    escena->objetos["poses"]->agregaKeyFrame(0,   0.0,0.0,0.0, 0.0,0.0,0.0, 1.0,1.0,1.0);
    escena->objetos["poses"]->agregaKeyFrame(50,  10.0,0.0,0.0, 0.0,90.0,0.0, 1.0,1.0,1.0);
    escena->objetos["poses"]->agregaKeyFrame(200, -10.0,0.0,0.0, 0.0,360.0,0.0, 1.0,1.0,1.0);
    escena->objetos["poses"]->agregaKeyFrame(300, 0.0,0.0,0.0, 0.0,0.0,0.0, 1.0,1.0,1.0);
}

void pruebaPicking(){
    char nom[10];
    for(int i=0; i<20; i++){
        sprintf(nom, "cubo%d",i);
        escena->agregaObjeto(nom, (Objeto *) new Cubo(1.0, rcolor(), rcolor(), rcolor()));
        escena->objetos[nom]->posX = rfloat(-10.0, 10.0);
        escena->objetos[nom]->posY = rfloat(-10.0, 10.0);
        escena->objetos[nom]->posZ = rfloat(-10.0, 10.0);
    }
}

/* ---------------------------------------------------------------- */
/* ---------- Definición de métodos para cargar la casa ----------- */
/* ---------------------------------------------------------------- */

void pared(string nombre, GLfloat largo, GLfloat posX, GLfloat posZ, bool rot){
    escena->agregaObjeto(nombre, (Objeto *) new Cubo(1.0, 0.3, 0.3, 0.3));
    escena->objetos[nombre]->escalaY = ALTOCASA;
    if ( !rot ){
        escena->objetos[nombre]->escalaX = ANCHOPARED;
        escena->objetos[nombre]->escalaZ = largo;
    } else {
        escena->objetos[nombre]->escalaX = largo;
        escena->objetos[nombre]->escalaZ = ANCHOPARED;
    }
    escena->objetos[nombre]->posX = posX + escena->objetos[nombre]->escalaX / 2;
    escena->objetos[nombre]->posZ = posZ - escena->objetos[nombre]->escalaZ / 2;
}

void paredesCasa(){
    
    pared("E1", 18.0, 0.0, 0.0, false);
    pared("E2", 10.0, 0.0, 0.0, true);
    pared("E3", 2.0, 10.0, 0.0, false);
    pared("E4", 4.0, 10.0, -4.0, false);
    pared("E5", 6.0, 4.0, -8.0, true);
    pared("E6", 2.0, 0.0, -8.0, true);
    pared("E7", 2.0, 0.0, -12.0, true);
    pared("E8", 2.0, 2.0, -10.0, false);
    pared("E9", 6.0, 4.0, -10.0, true);
    pared("E10", 4.0, 6.0, -10.0, false);
    pared("E11", 8.0, 10.0, -10.0, false);
    pared("E12", 2.0, 0.0, -8.0, true);
    pared("E13", 10.0, 0.0, -18.0, true);
    pared("E14", 6.0, 2.0, -18.0, false);
    pared("E15", 14.0, 2.0, -24.0, true);
    pared("E16", 2.0, 10.0, -22.0, false);
    pared("E17", 2.0, 10.0, -18.0, false);
    pared("E18", 14.0, 0.0, -20.0, false);
    pared("E19", 24.0, 0.0, -34.0, true);
    pared("E20", 34.0, 24.0, 0.0, false);
    pared("E21", 8.0, 16.0, -26.0, false);
    pared("E22", 6.0, 18.0, -26.0, true);
    pared("E23", 2.0, 12.0, -22.0, false);
    pared("E24", 6.0, 16.0, -18.0, false);
    pared("E25", 4.0, 12.0, -18.0, true);
    pared("E26", 2.0, 12.0, -18.0, false);
    pared("E27", 8.0, 18.0, -14.0, false);
    pared("E28", 4.0, 18.0, -20.0, true);
    pared("E29", 4.0, 18.0, -24.0, true);
    pared("E30", 4.0, 22.0, -20.0, false);
    pared("E31", 10.0, 22.0, -8.0, false);
    pared("E32", 10.0, 12.0, -8.0, true);
    pared("E33", 8.0, 12.0, -8.0, false);
    pared("E34", 4.0, 12.0, -16.0, true);
    pared("E35", 6.0, 16.0, -6.0, true);
    pared("E36", 2.0, 16.0, -14.0, false);
    pared("E37", 12.0, 12.0, 0.0, true);
    pared("E38", 6.0, 16.0, -0.0, false);
    pared("E39", 6.0, 12.0, -0.0, false);
    pared("E40", 2.0, 12.0, -6.0, true);
}

void jeff(){
	escena->agregaObjeto("jeff", (Objeto *) new Cubo(0.25, 1.0, 0.0, 0.0));
	escena->objetos["jeff"]->posX = 2.0;
	escena->objetos["jeff"]->posY = 0.5;
	escena->objetos["jeff"]->posZ = -16.0;
}

void creaCasa(){
	paredesCasa();
	jeff();
}

void creaEscena()
{
	creaCasa();
    
    escena->agregaObjeto("cubo1", (Objeto*) new Cubo(1.0, 0.0, 0.0, 1.0));
    escena->objetos["cubo1"]->posX = -3.0;
    escena->objetos["cubo1"]->posY = 1.0;
}

