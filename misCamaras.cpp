//#include "Escena.h"
#include "misCamaras.h"

// Definiciones de camaras - Mantener al menos las definiciones de camaraDefault y activa
Camara *camaraDefault;
Camara *activa;

//Definiciones de camaras especiales
Camara *camaraZenital;
Camara *camaraFP;
Camara *camaraFirst;

void defineCamaras()
{
  // Definiciones de camaras - Mantener al menos la definicion de camaraDefault
  camaraDefault = new Camara(0.0,0.0,-5.0,0.0,0.0,0.0,100000.0,1.0,90.0);

  //camaraZenital = new Camara(-11.1,-17.0,-43.0,90.0,0.0,0.0,100.0,1.0,45.0);
  camaraFP = new Camara(11.1, 1.0, 2.0,0.0,0.0,0.0,100000.0,0.5,90.0);
  camaraFirst = new Camara(11.1, 0.5, 2.0,0.0,0.0,0.0,100000.0,0.5,45.0);
  //camaraFP = new Camara(11.1, 1.0, 2.0,0.0,0.0,0.0,100000.0,0.5,90.0); Camara tercera persona
  //Asignar a activa la camara con la que se desea iniciar
  
  activa=camaraFP;

  camaraZenital = new Camara(-10.0,-17.0,-12.0,
							 90.0,0.0,0.0,
							 100.0, 1.0,
							 120.0);
  
  //Asignar a activa la camara con la que se desea iniciar
  
  //activa=camaraDefault;
  //activa=camaraZenital;

}

