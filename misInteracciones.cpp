#include "misInteracciones.h"
#include "movimientos.h"

GLuint selectBuf[PICKBUFSIZE];

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
        case '1' : activa = camaraFP; 
				   escena->objetos["cuboAvatar"]->escalaUniforme(1.0);
				   redimensiona(currWidth,currHeight); 
				   break;
            
        case '2' : activa = camaraZenital;
				   redimensiona(currWidth,currHeight);
				   break;
		case '3' : escena->objetos["cuboAvatar"]->escalaUniforme(0.0);
				   activa = camaraFirst;
				   redimensiona(currWidth,currHeight);
				break;
		case 'D':    
        case 'd': 
			girarDerecha();
            break;
		case 'W':
        case 'w': 
			moverAdelante();
            break;
            /*case 'z': activa->zrot+=drot;
             redimensiona(currWidth,currHeight);
             break;*/
		case 'A':    
        case 'a': 
            girarIzquierda();
            break;
            /*case 's': activa->zrot-=drot;
             redimensiona(currWidth,currHeight);
             break;*/
            
            /*case 'Z': activa->zrot-=drot;
             redimensiona(currWidth,currHeight);
             break;*/
        case 'j':
            if(!escena->impideColision2(escena->objetos["cubo1"], -dtran, 0.0, 0.0)){
                escena->objetos["cubo1"]->posX -= dtran;
            }
            break;
            
        case 'i':
            if(!escena->impideColision2(escena->objetos["cubo1"], 0.0, 0.0, -dtran)){
                escena->objetos["cubo1"]->posZ -= dtran;
            }
            break;
            
        case 'l':
            if(!escena->impideColision2(escena->objetos["cubo1"], dtran, 0.0, 0.0)){
                escena->objetos["cubo1"]->posX += dtran;
            }
            break;
            
        case 'k':
            if(!escena->impideColision2(escena->objetos["cubo1"], 0.0, 0.0, dtran)){
                escena->objetos["cubo1"]->posZ += dtran;
            }
            break;
            
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
    if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    {
        startPicking(x, y);
        escena->dibujaEscena();
        stopPicking();
    }
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
void startPicking(int cursorX, int cursorY) {
    GLint viewport[4];
    glSelectBuffer(PICKBUFSIZE,selectBuf);
    glRenderMode(GL_SELECT);
    glMatrixMode(GL_PROJECTION);
    glPushMatrix(); glLoadIdentity();
    glGetIntegerv(GL_VIEWPORT,viewport);
    gluPickMatrix(cursorX,viewport[3]-cursorY,5,5,viewport);
    gluPerspective(activa->fovy,(GLdouble)currWidth/(GLdouble)currHeight, activa->near,activa->far);
    glTranslatef(activa->xview,activa->yview,activa->zview); glRotatef(activa->xrot,1.0,0.0,0.0);
    glRotatef(activa->yrot,0.0,1.0,0.0); glRotatef(activa->zrot,0.0,0.0,1.0); glMatrixMode(GL_MODELVIEW);
    glInitNames();
}

void stopPicking() { int hits;
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
    glFlush();
    hits = glRenderMode(GL_RENDER);
    if (hits != 0) processHits(hits);
}

void processHits (GLint hits) {
    GLuint i,j,index,nitems,zmin,zmax,seleccion;
    // Procesa multiples hits
    for( i = 0, index = 0; i < hits; i++ )
    {
        nitems = selectBuf[index++];
        zmin = selectBuf[index++];
        zmax = selectBuf[index++];
        for( j = 0; j < nitems; j++ )
        {
            seleccion = selectBuf[index++];
            // Se busca el objeto de la escena con el hitName seleccionado
            map<string, Objeto *>::const_iterator iter;
            for (iter=escena->objetos.begin(); iter != escena->objetos.end(); ++iter)
            {
                Objeto *o=(Objeto *)iter->second;
                if (o->hitName==seleccion)
                {
                    acciones(o);
                }
            }
        }
    }
}

void acciones(Objeto *o)
{
    //Acciones con el objeto seleccionado
    /*if (o->velZ!=0.0)
    {
        o->velZ=0.0;
    }
    else
    {
        o->velZ=0.1;
    }*/
}