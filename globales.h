#pragma once

#include "Escena.h"
#include "misCamaras.h"

// Declaraciones de Variables globales

extern Escena *escena;       //Escena actual
extern int currWidth;        //Ancho de la ventana grafica
extern int currHeight;       //Alto de la ventana grafica
extern GLfloat dtran;        //Delta de traslacion interactiva
extern GLfloat drot;         //Delta de rotacion interactiva
extern Camara *activa;       //Camara activa
extern bool leftMouse;       //Boton izquierdo oprimido
extern bool rightMouse;      //Boton derecho oprimido
extern bool middleMouse;     //Boton central oprimido
extern int lastMouseX;       //Posicion previa de mouse en X
extern int lastMouseY;       //Posicion previa de mouse en Y
extern bool tecladoDefault;  //Determina si debe ejecutarse la interaccion default para teclado
extern bool mouseDefault;    //Determina si debe ejecutarse la interaccion default para mouse