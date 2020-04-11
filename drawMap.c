#ifdef __APPLE_CC__
#include <OpenGL/OpenGL.h>
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <stdio.h>
#include <stdlib.h>

#include "structure.h"
#include "loadMap.h"
#include "drawMap.h"

/*
Fonction de dessin du plateau
*/
void drawPlateau(int x, int y){

    for (int j = 0; j < x; ++j)
    {
        for (int i = 0; i < y; ++i)
        {

            if(plateau->tab[j][i] == '#')
            {
                glColor3f(1.0f,1.0f,1.0f);

                glMatrixMode(GL_MODELVIEW);
                glLoadIdentity();
                glTranslatef(i*Square_size,j*Square_size,0.0f);
                //glTranslatef(j*Square_size,i*Square_size,0.0f);

                glBegin(GL_QUADS);
                //glColor3f(1.0,1.0,0.0);
                glVertex3f(0.0f, 0.0f, 0.0f);
                glVertex3f(Square_size, 0.0f, 0.0f);
                glVertex3f(Square_size,Square_size, 0.0f);
                glVertex3f(0.0f,Square_size, 0.0f);

                glEnd();
                
                glBegin(GL_POLYGON);         //draw road
                glColor3f(0.5,0.5,0.5);
                glVertex3f(0,15, 0.0f);
                glVertex3f(50, 15, 0.0f);
                glVertex3f(x*Square_size, 15, 0.0f);
                glVertex3f(0, y*Square_size, 0.0f);
                glEnd();
            }

            if(plateau->tab[j][i] == '|')
            {
                glColor3f(1.0f,1.0f,0.0f);

                glMatrixMode(GL_MODELVIEW);
                glLoadIdentity();
                glTranslatef(i*Square_size,j*Square_size,0.0f);
                //glTranslatef(j*Square_size, i*Square_size,0.0f);
                glBegin(GL_QUADS);

                glVertex3f(0.0f, 0.0f, 0.0f);
                glVertex3f(Square_size, 0.0f, 0.0f);
                glVertex3f(Square_size,Square_size, 0.0f);
                glVertex3f(0.0f,Square_size, 0.0f);

                glEnd();
            }       
            
            if(plateau->tab[j][i] == 'e')
            {   
                //glColor3f(1.0f,1.0f,0.0f);
                glColor3f(1,0,0);

                glMatrixMode(GL_MODELVIEW);
                glLoadIdentity();
                glTranslatef(i*Square_size,j*Square_size,0.0f);
                //glTranslatef(j*Square_size, i*Square_size,0.0f);
            
                glBegin(GL_QUADS);

                glVertex3f(0.0f, 0.0f, 0.0f);
                glVertex3f(Square_size, 0.0f, 0.0f);
                glVertex3f(Square_size,Square_size, 0.0f);
                glVertex3f(0.0f,Square_size, 0.0f);

                glEnd();
            
            }

            if(plateau->tab[j][i] == 'u' || plateau->tab[j][i] == 'i' || plateau->tab[j][i] == 'o')
            {
                glColor3f(0.0f,1.0f,1.0f);

                glMatrixMode(GL_MODELVIEW);
                glLoadIdentity();
                glTranslatef(i*Square_size,j*Square_size,0.0f);
                //glTranslatef(j*Square_size,i*Square_size,0.0f);

                glBegin(GL_QUADS);
                //glColor3f(1.0,1.0,0.0);
                glVertex3f(0.0f, 0.0f, 0.0f);
                glVertex3f(10, 0.0f, 0.0f);
                glVertex3f(10,10, 0.0f);
                glVertex3f(0.0f,10, 0.0f);

                glEnd();
                
                glBegin(GL_POLYGON);         //draw road
                glColor3f(0.5,0.5,0.5);
                glVertex3f(0,15, 0.0f);
                glVertex3f(50, 15, 0.0f);
                glVertex3f(10, 15, 0.0f);
                glVertex3f(0, 10, 0.0f);
                glEnd();
            }  

            if(plateau->tab[j][i] == 't')
            {
                glColor3f(5.0f,5.0f,1.0f);

                glMatrixMode(GL_MODELVIEW);
                glLoadIdentity();
                glTranslatef(i*Square_size,j*Square_size,0.0f);
                //glTranslatef(j*Square_size,i*Square_size,0.0f);

                glBegin(GL_QUADS);
                //glColor3f(1.0,1.0,0.0);

                //1er coin gauche bas 
                glVertex3f(0.0f, 0.0f, 0.0f);
                // coin bas droit 
                glVertex3f(10, 0.0f, 0.0f);
                // haut droit 
                glVertex3f(10,10, 0.0f);
                // haut gauche 
                glVertex3f(0.0f,10, 0.0f);

                glEnd();
                
                glBegin(GL_POLYGON);         //draw road
                glColor3f(0.5,0.5,0.5);
                glVertex3f(0,15, 0.0f);
                glVertex3f(50, 15, 0.0f);
                glVertex3f(10, 15, 0.0f);
                glVertex3f(0, y*10, 0.0f);
                glEnd();
            }      
        
        }
    }
}

void drawJoueur(Plateau* plateau){

    int i,j;
    i = plateau->joueur->pos.y;
    j = plateau->joueur->pos.x;

    glColor3f(0.0f,1.0f,0.0f);
    
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glTranslatef(i*Square_size,j*Square_size,0.0f);

    glBegin(GL_QUADS);

    glVertex3f(0.0f, 0.0f, 0.0f);
    glVertex3f(Square_size, 0.0f, 0.0f);
    glVertex3f(Square_size,Square_size, 0.0f);
    glVertex3f(0.0f,Square_size, 0.0f);

    glEnd();
}