#include "Escena.h"

// Definiciones de camaras - Mantener al menos las definiciones de camaraDefault y activa
Camara *camaraDefault;
Camara *activa;

//Definiciones de camaras especiales
Camara *camaraZenital;

void defineCamaras()
{
  // Definiciones de camaras - Mantener al menos la definicion de camaraDefault
  camaraDefault = new Camara(0.0,0.0,-5.0,0.0,0.0,0.0,100000.0,1.0,90.0);
  camaraZenital = new Camara(0.0,0.0,-5.0,90.0,0.0,0.0,100.0,1.0,45.0);
  
  //Asignar a activa la camara con la que se desea iniciar
  
  activa=camaraDefault;
}

