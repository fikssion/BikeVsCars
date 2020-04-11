#ifdef __APPLE_CC__
#include <OpenGL/OpenGL.h>
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "structure.h"
#include "loadMap.h"
#include "game.h"
#include "drawMap.h"


int x = 42;
int y = 41;
int last = 0; 
int m_sec = 250; // constante de rafraichissement de partie.
float fDistance[LIGNE/PRO];

void initRendering()
{
    glEnable(GL_DEPTH_TEST);
}

void handleResize(int width,int heigth)
{
    glViewport(0, 0, width, heigth);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, width, heigth, 0);
}

// va gérer le taux de rafraichissement
void timerIdle(int i){
    
    for(int k;k < plateau->nbEnnemi;k++){
        fDistance[k]+=3;
    }
    partie(x,y,plateau);
    glutPostRedisplay();
    glutTimerFunc(m_sec,timerIdle,i);
}

void Display()
{    
    glClearColor(0.0f,0.0f,0.0f,0.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);    
        
    drawPlateau(x,y);
    drawJoueur(plateau);
        
    glutPostRedisplay();
    glutSwapBuffers();
    //glFlush();
}

void keyboard(unsigned char deplac, int x, int y){
    
    switch(deplac)
    {
        case 27:    // touche ESC
            exit(0);

        case'z':
            mouvement('z',plateau);
            break;

        case'q':
            mouvement('q',plateau);
            break;

        case'd':
            mouvement('d',plateau);
            break;

        case's':
            mouvement('s',plateau);
            break;

        case 'u':
            tirBike('u',plateau);
            break;

        case 'i':
            tirBike('i',plateau);
            break;

        case 'o':
            tirBike('o',plateau);
            break;
    }  

    if(checkFinPartie(plateau)){
            exit(1);
    }

    glutPostRedisplay();
}

int main(int argc, char *argv[]){

    
    //1. Initialiser le plateau de jeu
    plateau = malloc(sizeof(Plateau));
    loadMap(x,y);

    //Prévoir un scanf pour lire le niveau voulu
    plateau->niveau = DEBUTANT;
    
    //2.Créer le joueur et l'assigner au plateau
    plateau->joueur=newJoueur();
    
    //3.Créer un nombre d'ennemi selon le niveau de difficulté et les assigner au plateau
    plateau->nbEnnemi = LIGNE/plateau->niveau;
    for(int i=0;i<plateau->nbEnnemi;i++){
        plateau->cars[i]=newEnnemi(0, -1, -1);   
    }

    glutInit(&argc, argv);
    
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);

    glutInitWindowSize(COLONNE*Square_size, LIGNE*Square_size);

    glutCreateWindow("Test");

    initRendering();

    glutDisplayFunc(Display);    

    glutKeyboardFunc(keyboard); 
    glutReshapeFunc(handleResize);
    glutTimerFunc(m_sec,timerIdle,1);


    glutMainLoop();     

}