#include "misComposiciones.h"
#include <iostream>

// Variables para la CASA
#define ALTOCASA	2.0
#define ANCHOPARED	0.15

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
    escena->agregaObjeto("hojas", (Objeto *) new AlphaQuad(escena,"AZULEJO.tga",GL_REPEAT,0.8,5,5,0,0,0.5,0,0));
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

void pared2(string snombre, GLfloat largo, GLfloat posX, GLfloat posZ, bool rot, string textura1, string textura2, GLfloat scale1, GLfloat scale2){
    const char* nombre = snombre.c_str();
    escena->agregaObjeto(nombre, (Objeto *) new Cubo(1.0, 1.0, 1.0, 1.0));
    escena->objetos[nombre]->escalaY = ALTOCASA;
    
    char nombreTapiz1[20];
    char nombreTapiz2[20];
    int nTapiz = largo/ALTOCASA;
    for(int i=0; i<nTapiz; i++){
        sprintf(nombreTapiz1, "%st%dA", nombre, i);
        escena->agregaObjeto(nombreTapiz1, (Objeto *) new AlphaQuad(escena, textura1, GL_REPEAT, 0.8, ALTOCASA, ALTOCASA, 0, 0, scale1, 0, 0));

        sprintf(nombreTapiz2, "%st%dB", nombre, i);
        escena->agregaObjeto(nombreTapiz2, (Objeto *) new AlphaQuad(escena, textura2, GL_REPEAT, 0.8, ALTOCASA, ALTOCASA, 0, 0, scale2, 0, 0));
        
        if( !rot ){
            escena->objetos[nombreTapiz1]->rotY = 90;
            escena->objetos[nombreTapiz1]->posZ = posZ - ALTOCASA/2 - i*ALTOCASA;
            escena->objetos[nombreTapiz1]->posX = posX - 0.01;
            escena->objetos[nombreTapiz2]->rotY = 90;
            escena->objetos[nombreTapiz2]->posZ = posZ - ALTOCASA/2 - i*ALTOCASA;
            escena->objetos[nombreTapiz2]->posX = posX + ANCHOPARED + 0.01;
        } else {
            escena->objetos[nombreTapiz1]->posX = posX + ALTOCASA/2 + i*ALTOCASA;
            escena->objetos[nombreTapiz1]->posZ = posZ + 0.01;
            escena->objetos[nombreTapiz2]->posX = posX + ALTOCASA/2 + i*ALTOCASA;
            escena->objetos[nombreTapiz2]->posZ = posZ - ANCHOPARED - 0.01;
        }
        
    }
    
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

void pared(string nombre, GLfloat largo, GLfloat posX, GLfloat posZ, bool rot, string textura){
    string cubo1 = nombre + "c1";
    string cubo2 = nombre + "c2";
    escena->agregaObjeto(cubo1, (Objeto *) new Cubo(1.0, 0.0, 0.0, 1.0));
    escena->agregaObjeto(cubo2, (Objeto *) new Cubo(1.0, 0.0, 0.0, 1.0));
    escena->objetos[cubo1]->defineMaterial(1.0,1.0,1.0,
                                           1.0,1.0,1.0,
                                           0.0,0.0,0.0,
                                           0.0,0.0,0.0,
                                           textura,GL_REPEAT,1.0,0.0,0.0,0.0,0.0,1.0,GL_EYE_LINEAR,false);
    escena->objetos[cubo2]->defineMaterial(1.0,1.0,1.0,
                                           1.0,1.0,1.0,
                                           0.0,0.0,0.0,
                                           0.0,0.0,0.0,
                                           textura,GL_REPEAT,1.0,0.0,0.0,0.0,0.0,1.0,GL_OBJECT_LINEAR,false);
    escena->objetos[cubo2]->rotY = 90.0;
    escena->objetos[cubo1]->escalaY = ALTOCASA;
    escena->objetos[cubo2]->escalaY = ALTOCASA;
    if ( !rot ){
        escena->objetos[cubo1]->escalaX = ANCHOPARED - 0.01;
        escena->objetos[cubo1]->escalaZ = largo;
        escena->objetos[cubo2]->escalaX = ANCHOPARED;
        escena->objetos[cubo2]->escalaZ = largo - 0.01;
    } else {
        escena->objetos[cubo1]->escalaX = largo - 0.01;
        escena->objetos[cubo1]->escalaZ = ANCHOPARED;
        escena->objetos[cubo2]->escalaX = largo;
        escena->objetos[cubo2]->escalaZ = ANCHOPARED - 0.01;
    }
    escena->objetos[cubo1]->posX = posX + 0.005 + escena->objetos[cubo1]->escalaX / 2;
    escena->objetos[cubo1]->posZ = posZ - escena->objetos[cubo1]->escalaZ / 2;
    escena->objetos[cubo2]->posX = posX + escena->objetos[cubo2]->escalaX / 2;
    escena->objetos[cubo2]->posZ = posZ - 0.005 - escena->objetos[cubo2]->escalaZ / 2;
}

void superficie(string nombre, GLfloat ancho, GLfloat largo, GLfloat posX, GLfloat posZ, string textura, GLfloat scale, bool techo){
    escena->agregaObjeto(nombre, (Objeto *) new AlphaQuad(escena, textura, GL_REPEAT, 1.0, ancho, largo, 0, 0, scale, 0, 0));
    escena->objetos[nombre]->rotX = 90;
    escena->objetos[nombre]->posX = posX + ancho/2;
    if(techo){
        escena->objetos[nombre]->posY = 0 + ALTOCASA/2 + 0.01;
    } else {
        escena->objetos[nombre]->posY = 0 - ALTOCASA/2 - 0.01;
    }
    escena->objetos[nombre]->posZ = posZ - largo/2;
}

void pisosCasa(){
    superficie("pprincipal", 22, 24, 2, 0, "floor2.tga", 0.05, false);
    superficie("pintIzquierdo", 2, 18, 0, 0, "floor2.tga", 0.5, false);
    superficie("pintComedor", 8, 10, 16, -24, "floor2.tga", 0.15, false);
    superficie("patioPrincipal", 16, 10, 0, -24, "plaster.tga", 0.2, false);
    superficie("patioPasillo", 2, 6, 0, -18, "plaster.tga", 0.6, false);
}

void techosCasa(){
    superficie("tprincipal", 22, 24, 2, 0, "plaster.tga", 0.05, true);
    superficie("tintIzquierdo", 2, 18, 0, 0, "plaster.tga", 0.5, true);
    superficie("tintComedor", 8, 10, 16, -24, "plaster.tga", 0.15, true);
}

void paredesCasa(){
    pared2("E1", 8.0, 0.0, 0.0, false, "metal_scratches.tga", "pared2.tga", 1.0, 1.0);
    pared2("E2", 10.0, 0.0, 0.0, true, "plaster2.tga", "pared2.tga", 1.0, 1.0);
    pared2("E3", 2.0, 10.0, 0.0, false, "pared2.tga", "metal_scratches.tga", 1.0, 1.0);
    pared2("E4", 4.0, 10.0, -4.0, false, "pared2.tga", "metal_scratches.tga", 1.0, 1.0);
    pared2("E5", 6.0, 4.0, -8.0, true, "pared2.tga", "metal_scratches.tga", 1.0, 1.0);
    pared2("E6", 2.0, 0.0, -8.0, true, "pared2.tga", "metal_scratches.tga", 1.0, 1.0);
    pared2("E7", 2.0, 0.0, -12.0, true, "metal_scratches.tga", "metal_scratches.tga", 1.0, 1.0);
    pared2("E8", 2.0, 2.0, -10.0, false, "metal_scratches.tga", "metal_scratches.tga", 1.0, 1.0);
    pared2("E9", 2.0, 4.0, -10.0, true, "metal_scratches.tga", "metal_scratches.tga", 1.0, 1.0);
    pared2("E10", 4.0, 6.0, -10.0, false, "metal_scratches.tga", "azulejo.tga", 1.0, 0.3);
    pared2("E11", 8.0, 10.0, -10.0, false, "azulejo.tga", "metal_scratches.tga", 0.3, 1.0);
    pared2("E12", 2.0, 6.0, -16.0, false, "metal_scratches.tga", "azulejo.tga", 1.0, 0.3);
    pared2("E13", 6.0, 0.0, -18.0, true, "metal_scratches.tga", "metal_scratches.tga", 1.0, 1.0);
    pared2("E14", 6.0, 2.0, -18.0, false, "metal_scratches.tga", "metal_scratches.tga", 1.0, 1.0);
    pared2("E15", 14.0, 2.0, -24.0, true, "metal_scratches.tga", "metal_scratches.tga", 1.0, 1.0);
    pared2("E16", 2.0, 10.0, -22.0, false, "metal_scratches.tga", "metal_scratches.tga", 1.0, 1.0);
    pared2("E17", 2.0, 10.0, -18.0, false, "metal_scratches.tga", "metal_scratches.tga", 1.0, 1.0);
    pared2("E18", 14.0, 0.0, -20.0, false, "metal_scratches.tga", "metal_scratches.tga", 1.0, 1.0);
    pared2("E19", 24.0, 0.0, -34.0, true, "metal_scratches.tga", "metal_scratches.tga", 1.0, 1.0);
    pared2("E20", 34.0, 24.0, 0.0, false, "metal_scratches.tga", "metal_scratches.tga", 1.0, 1.0);
    pared2("E21", 8.0, 16.0, -26.0, false, "metal_scratches.tga", "metal_scratches.tga", 1.0, 1.0);
    pared2("E22", 6.0, 18.0, -26.0, true, "metal_scratches.tga", "metal_scratches.tga", 1.0, 1.0);
    pared2("E23", 2.0, 12.0, -22.0, false, "metal_scratches.tga", "metal_scratches.tga", 1.0, 1.0);
    pared2("E24", 6.0, 16.0, -18.0, false, "metal_scratches.tga", "metal_scratches.tga", 1.0, 1.0);
    pared2("E25", 4.0, 12.0, -18.0, true, "metal_scratches.tga", "metal_scratches.tga", 1.0, 1.0);
    pared2("E26", 2.0, 12.0, -18.0, false, "metal_scratches.tga", "metal_scratches.tga", 1.0, 1.0);
    pared2("E27", 2.0, 18.0, -20.0, false, "metal_scratches.tga", "azulejo.tga", 1.0, 1.0);
    pared2("E28", 4.0, 18.0, -20.0, true, "rust.tga", "azulejo.tga", 1.0, 0.3);
    pared2("E29", 4.0, 18.0, -24.0, true, "azulejo.tga", "metal_scratches.tga", 0.3, 1.0);
    pared2("E30", 4.0, 22.0, -20.0, false, "azulejo.tga", "metal_scratches.tga", 0.3, 1.0);
    pared2("E31", 10.0, 22.0, -8.0, false, "rust.tga", "metal_scratches.tga", 1.0, 1.0);
    pared2("E32", 10.0, 12.0, -8.0, true, "metal_scratches.tga", "rust.tga", 1.0, 1.0);
    pared2("E33", 8.0, 12.0, -8.0, false, "metal_scratches.tga", "rust.tga", 1.0, 1.0);
    pared2("E34", 4.0, 12.0, -16.0, true, "rust.tga", "metal_scratches.tga", 1.0, 1.0);
    pared2("E35", 6.0, 16.0, -6.0, true, "metal_scratches.tga", "metal_scratches.tga", 1.0, 1.0);
    pared2("E36", 2.0, 16.0, -14.0, false, "rust.tga", "metal_scratches.tga", 1.0, 1.0);
    pared2("E37", 12.0, 12.0, 0.0, true, "metal_scratches.tga", "metal_scratches.tga", 1.0, 1.0);
    pared2("E38", 6.0, 16.0, -0.0, false, "metal_scratches.tga", "metal_scratches.tga", 1.0, 1.0);
    pared2("E39", 6.0, 12.0, -0.0, false, "metal_scratches.tga", "metal_scratches.tga", 1.0, 1.0);
    pared2("E40", 2.0, 12.0, -6.0, true, "metal_scratches.tga", "metal_scratches.tga", 1.0, 1.0);
    pared2("E41", 4.0, 6.0, -18.0, true, "azulejo.tga", "metal_scratches.tga", 0.3, 1.0);
    pared2("E42", 4.0, 6.0, -10.0, true, "metal_scratches.tga", "azulejo.tga", 1.0, 0.3);
    pared2("E43", 4.0, 0.0, -8.0, false, "metal_scratches.tga", "metal_scratches.tga", 1.0, 1.0);
    pared2("E44", 6.0, 0.0, -12.0, false, "metal_scratches.tga", "metal_scratches.tga", 1.0, 1.0);
    pared2("E45", 6.0, 18.0, -14.0, false, "metal_scratches.tga", "rust.tga", 1.0, 1.0);
}

void cielo(){
    escena->agregaObjeto("cielo", (Objeto *) new Esfera(100, 40, 40, 0.0, 0.0, 1.0));
}

void sueloMundo(){
    superficie("sueloMundo", 100, 100, -50, 50, "grass.tga", 0.01, false);
    escena->objetos["sueloMundo"]->posY -= 0.01;
}

void sala(){
	escena->agregaObjeto("cuboSSala", (Objeto *) new Cubo(1.0, 0.0, 0.0, 0.0));
	escena->objetos["cuboSSala"]->posX = 3.0;
	escena->objetos["cuboSSala"]->posY = 0.0;
	escena->objetos["cuboSSala"]->posZ = -3.0;
	escena->objetos["cuboSSala"]->defineMaterial(1.0,1.0,1.0,
                                               1.0,1.0,1.0,
                                               0.0,0.0,0.0,
                                               0.0,0.0,0.0,
                                               "transparente.tga",GL_REPEAT,1.0,0.0,0.0,0.0,0.0,1.0,GL_SPHERE_MAP,false);
	escena->objetos["cuboSSala"]->agregaDescendiente("silla", (Objeto *) new Modelo("silla"));
}

void jeff(){
	escena->agregaObjeto("jeff", (Objeto *) new Modelo("JeffSinAgruparText1"));

	escena->objetos["jeff"]->posX = 3.0;
	escena->objetos["jeff"]->posY = -0.5;
	escena->objetos["jeff"]->posZ = -16.0;
	escena->objetos["jeff"]->agregaKeyFrame(0.0, 
											3.0, 0.0, -16.0, 
											0.0, 0.0, 0.0, 
											1.0, 1.0, 1.0);
	escena->objetos["jeff"]->agregaKeyFrame(80.0, 
											3.0, 0.0, -9.5, 
											0.0, 0.0, 0.0, 
											1.0, 1.0, 1.0);
    escena->objetos["jeff"]->agregaKeyFrame(85.0, 
											3.0, 0.0, -9.5, 
											0.0, 90.0, 0.0,
											1.0, 1.0, 1.0);
	escena->objetos["jeff"]->agregaKeyFrame(185.0, 
											11.0, 0.0, -9.5, 
											0.0, 90.0, 0.0, 
											1.0, 1.0, 1.0);
	escena->objetos["jeff"]->agregaKeyFrame(190.0, 
											11.0, 0.0, -9.5, 
											0.0, 0.0, 0.0, 
											1.0, 1.0, 1.0);
    escena->objetos["jeff"]->agregaKeyFrame(225.0, 
											11.0, 0.0, -7, 
											0.0, 0.0, 0.0, 
											1.0, 1.0, 1.0);
	escena->objetos["jeff"]->agregaKeyFrame(230.0, 
											11.0, 0.0, -7, 
											0.0, 90.0, 0.0, 
											1.0, 1.0, 1.0);
	escena->objetos["jeff"]->agregaKeyFrame(365.0, 
											23.0, 0.0, -7, 
											0.0, 90.0, 0.0, 
											1.0, 1.0, 1.0);
	escena->objetos["jeff"]->agregaKeyFrame(370.0, 
											23.0, 0.0, -7, 
											0.0, 180.0, 0.0, 
											1.0, 1.0, 1.0);
	escena->objetos["jeff"]->agregaKeyFrame(580.0, 
											23.0, 0.0, -25.5, 
											0.0, 180.0, 0.0, 
											1.0, 1.0, 1.0);
	escena->objetos["jeff"]->agregaKeyFrame(585.0, 
											23.0, 0.0, -25.5, 
											0.0, 270.0, 0.0, 
											1.0, 1.0, 1.0);
	escena->objetos["jeff"]->agregaKeyFrame(640.0, 
											17.5, 0.0, -25.5, 
											0.0, 270.0, 0.0, 
											1.0, 1.0, 1.0);
	escena->objetos["jeff"]->agregaKeyFrame(645.0, 
											17.5, 0.0, -25.5, 
											0.0, 180.0, 0.0, 
											1.0, 1.0, 1.0);
	escena->objetos["jeff"]->agregaKeyFrame(680.0, 
											17.5, 0.0, -28.5, 
											0.0, 180.0, 0.0, 
											1.0, 1.0, 1.0);
	escena->objetos["jeff"]->agregaKeyFrame(685.0, 
											17.5, 0.0, -28.5, 
											0.0, 90.0, 0.0, 
											1.0, 1.0, 1.0);
	escena->objetos["jeff"]->agregaKeyFrame(760.0, 
											22.0, 0.0, -28.5, 
											0.0, 90.0, 0.0, 
											1.0, 1.0, 1.0);
	escena->objetos["jeff"]->agregaKeyFrame(765.0, 
											22.0, 0.0, -28.5, 
											0.0, 180.0, 0.0, 
											1.0, 1.0, 1.0);
	escena->objetos["jeff"]->agregaKeyFrame(800.0, 
											22.0, 0.0, -32.5, 
											0.0, 180.0, 0.0, 
											1.0, 1.0, 1.0);
	escena->objetos["jeff"]->agregaKeyFrame(805.0, 
											22.0, 0.0, -32.5, 
											0.0, 270.0, 0.0, 
											1.0, 1.0, 1.0);
	escena->objetos["jeff"]->agregaKeyFrame(840.0, 
											17.5, 0.0, -32.5, 
											0.0, 270.0, 0.0, 
											1.0, 1.0, 1.0);
	escena->objetos["jeff"]->agregaKeyFrame(860.0, 
											17.5, 0.0, -32.5, 
											0.0, 0.0, 0.0, 
											1.0, 1.0, 1.0);
	escena->objetos["jeff"]->agregaKeyFrame(1040.0, 
											17.5, 0.0, -12.5, 
											0.0, 0.0, 0.0, 
											1.0, 1.0, 1.0);
	escena->objetos["jeff"]->agregaKeyFrame(1045.0, 
											17.5, 0.0, -12.5, 
											0.0, 90.0, 0.0, 
											1.0, 1.0, 1.0);
	escena->objetos["jeff"]->agregaKeyFrame(1070.0, 
											19.0, 0.0, -12.5, 
											0.0, 90.0, 0.0, 
											1.0, 1.0, 1.0);
	escena->objetos["jeff"]->agregaKeyFrame(1075.0, 
											19.0, 0.0, -12.5, 
											0.0, 180.0, 0.0, 
											1.0, 1.0, 1.0);
	escena->objetos["jeff"]->agregaKeyFrame(1120.0, 
											19.0, 0.0, -18.5, 
											0.0, 180.0, 0.0, 
											1.0, 1.0, 1.0);
	escena->objetos["jeff"]->agregaKeyFrame(1125.0, 
											19.0, 0.0, -18.5, 
											0.0, 90.0, 0.0, 
											1.0, 1.0, 1.0);
	escena->objetos["jeff"]->agregaKeyFrame(1180.0, 
											23.0, 0.0, -18.5, 
											0.0, 90.0, 0.0, 
											1.0, 1.0, 1.0);
	escena->objetos["jeff"]->agregaKeyFrame(1185.0, 
											23.0, 0.0, -18.5, 
											0.0, 0.0, 0.0, 
											1.0, 1.0, 1.0);
	escena->objetos["jeff"]->agregaKeyFrame(1370.0, 
											23.0, 0.0, -2, 
											0.0, 0.0, 0.0, 
											1.0, 1.0, 1.0);
	escena->objetos["jeff"]->agregaKeyFrame(1375.0, 
											23.0, 0.0, -2, 
											0.0, 270.0, 0.0, 
											1.0, 1.0, 1.0);
	escena->objetos["jeff"]->agregaKeyFrame(1420.0, 
											19.0, 0.0, -2, 
											0.0, 270.0, 0.0, 
											1.0, 1.0, 1.0);
	escena->objetos["jeff"]->agregaKeyFrame(1425.0, 
											19.0, 0.0, -2, 
											0.0, 180.0, 0.0, 
											1.0, 1.0, 1.0);
	escena->objetos["jeff"]->agregaKeyFrame(1445.0, 
											19.0, 0.0, -3, 
											0.0, 180.0, 0.0, 
											1.0, 1.0, 1.0);
	escena->objetos["jeff"]->agregaKeyFrame(1450.0, 
											19.0, 0.0, -3, 
											0.0, 90.0, 0.0, 
											1.0, 1.0, 1.0);
	escena->objetos["jeff"]->agregaKeyFrame(1490.0, 
											23.5, 0.0, -3, 
											0.0, 90.0, 0.0, 
											1.0, 1.0, 1.0);
	escena->objetos["jeff"]->agregaKeyFrame(1495.0, 
											23.5, 0.0, -3, 
											0.0, 180.0, 0.0, 
											1.0, 1.0, 1.0);
	escena->objetos["jeff"]->agregaKeyFrame(1515.0, 
											23.5, 0.0, -7, 
											0.0, 180.0, 0.0, 
											1.0, 1.0, 1.0);
	escena->objetos["jeff"]->agregaKeyFrame(1520.0, 
											23.5, 0.0, -7, 
											0.0, 270.0, 0.0, 
											1.0, 1.0, 1.0);
	escena->objetos["jeff"]->agregaKeyFrame(1640.0, 
											11.0, 0.0, -7, 
											0.0,270.0, 0.0, 
											1.0, 1.0, 1.0);
	escena->objetos["jeff"]->agregaKeyFrame(1645.0, 
											11.0, 0.0, -7, 
											0.0,180.0, 0.0, 
											1.0, 1.0, 1.0);
	escena->objetos["jeff"]->agregaKeyFrame(1765.0, 
											11.0, 0.0, -21, 
											0.0, 180.0, 0.0, 
											1.0, 1.0, 1.0);
	escena->objetos["jeff"]->agregaKeyFrame(1770.0, 
											11.0, 0.0, -21, 
											0.0, 270.0, 0.0, 
											1.0, 1.0, 1.0);
	escena->objetos["jeff"]->agregaKeyFrame(1810.0, 
											7.0, 0.0, -21, 
											0.0, 270.0, 0.0, 
											1.0, 1.0, 1.0);
	escena->objetos["jeff"]->agregaKeyFrame(1815.0, 
											7.0, 0.0, -21, 
											0.0, 90.0, 0.0, 
											1.0, 1.0, 1.0);
	escena->objetos["jeff"]->agregaKeyFrame(1855.0, 
											11.0, 0.0, -21, 
											0.0, 90.0, 0.0, 
											1.0, 1.0, 1.0);
	escena->objetos["jeff"]->agregaKeyFrame(1860.0, 
											11.0, 0.0, -21, 
											0.0, 0.0, 0.0, 
											1.0, 1.0, 1.0);
	escena->objetos["jeff"]->agregaKeyFrame(1980.0, 
											11.0, 0.0, -2.5, 
											0.0, 0.0, 0.0, 
											1.0, 1.0, 1.0);
	escena->objetos["jeff"]->agregaKeyFrame(1985.0, 
											11.0, 0.0, -2.5, 
											0.0, 270.0, 0.0, 
											1.0, 1.0, 1.0);
	escena->objetos["jeff"]->agregaKeyFrame(2185.0, 
											3.0, 0.0, -2.5, 
											0.0, 270.0, 0.0, 
											1.0, 1.0, 1.0);
	escena->objetos["jeff"]->agregaKeyFrame(2190.0, 
											3.0, 0.0, -2.5, 
											0.0, 180.0, 0.0, 
											1.0, 1.0, 1.0);
	escena->objetos["jeff"]->agregaKeyFrame(2270.0, 
											3.0, 0.0, -16, 
											0.0, 180.0, 0.0, 
											1.0, 1.0, 1.0);


}

void avatar()
{
	escena->agregaObjeto("cuboAvatar", (Objeto *) new Cubo(1.0, 0.0, 0.0, 0.5));
	escena->objetos["cuboAvatar"]->agregaDescendiente("avatar",(Objeto *) new Modelo("avatar"));
	//escena->agregaObjeto("cuboAvatar", (Objeto *) new Modelo("avatar"));
	//escena->objetos["al"]->escalaUniforme(3.0);
	escena->objetos["cuboAvatar"]->escalaUniforme(0.6);

	escena->objetos["cuboAvatar"]->posX =11.1;
	escena->objetos["cuboAvatar"]->posY =-0.4;
	escena->objetos["cuboAvatar"]->posZ = 1.0;
	
	/*escena->objetos["cuboAvatar"]->defineMaterial(1.0,1.0,1.0,
                                           1.0,1.0,1.0,
                                           0.0,0.0,0.0,
                                           0.0,0.0,0.0,
                                           "azulejo.tga",GL_REPEAT,0.0,0.0,0.0,0.0,0.0,1.0,GL_EYE_LINEAR,false);*/
}

void creaCasa(){
	paredesCasa();
    pisosCasa();
    techosCasa();
    cielo();
    sueloMundo();
	avatar();
	jeff();
	
}

void creaEscena()
{
	creaCasa();

}

