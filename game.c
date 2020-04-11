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
#include <time.h>

#include "structure.h"
#include "loadMap.h"
#include "drawMap.h"

// vérifie si il y a collision entre le tir et l'ennemi.
// si touche = true, l'ennemi est replacé en x et y -1 ( réinitialisé )
int score = 0;

// fait repoper des ennemis alétoire 
void repopEnnemi(int count, int xCar, int yCar, Plateau* plateau){
    
    if(xCar== -1 && yCar == -1){
        //On peut placer la voiture sur la premiere ligne
        //Et on utilise un srand pour choisir aleatoirement sa colonne
        srand(time(NULL)); // initialisation de rand
        int w = (rand()%COLONNE-2)+1;
        // condition pour le Rand, car parfois beugé et ce met à 0 ou -1
        if(w<=0){
            w = (rand()%(COLONNE-2)-LIGNE)+1;
        }
        plateau->tab[1][w]='e';
        plateau->cars[count]->pos.x=1;
        plateau->cars[count]->pos.y=w;            
    }
}

//va regarder si le tir et les ennemis vont entrer en collision
bool checkTir(Plateau* plateau){

    bool touche = false;    

    for(int i=0;i<LIGNE-2;i++){
        for(int j=0;j<COLONNE-2;j++){  
            for(int k=0;k<plateau->nbEnnemi;k++){

            int xCar = plateau->cars[k]->pos.x;
            int yCar = plateau->cars[k]->pos.y;

                //vérifie la position de la voiture 
                if(plateau->tab[i][j] == plateau->tab[xCar][yCar]){   
                    //vérifie en fonction 'i' si le tir se trouve à i-1 de la voiture                          
                    if(plateau->tab[i-1][j] == 'i'){                        
                        score ++;                        
                        xCar=-1;
                        yCar=-1; 
                        plateau->cars[k]->pos.x = xCar;
                        plateau->cars[k]->pos.x = yCar;
                        repopEnnemi(k,xCar,yCar,plateau);  

                        plateau->tab[i-1][j] = ' ';

                    }
                    //vérifie en fonction 'u' si le tir se trouve à i-1 j+1(diagnale) de la voiture   
                    else if(plateau->tab[i-1][j+1] == 'u'){                        
                        score ++;                        
                        xCar=-1;
                        yCar=-1; 
                        plateau->cars[k]->pos.x = xCar;
                        plateau->cars[k]->pos.x = yCar;
                        repopEnnemi(k,xCar,yCar,plateau);
                        plateau->tab[i-1][j+1] = ' ';
                    }
                    //vérifie en fonction 'o' si le tir se trouve à i-1 j-1(diagonal) de la voiture   
                    else if(plateau->tab[i-1][j-1] == 'o'){                        
                        score ++;                        
                        xCar=-1;
                        yCar=-1; 
                        plateau->cars[k]->pos.x = xCar;
                        plateau->cars[k]->pos.x = yCar;
                        repopEnnemi(k,xCar,yCar,plateau);
                        plateau->tab[i-1][j-1] = ' ';
                    }
                }                              
            }        
        }            
    }
    return touche;
}

bool checkFinPartie(Plateau* plateau){
    
    bool estFinie = false;
    
    for(int i=0;i<plateau->nbEnnemi;i++){
        int xCar = plateau->cars[i]->pos.x;
        int yCar = plateau->cars[i]->pos.y;
        if(xCar == plateau->joueur->pos.x && yCar == plateau->joueur->pos.y){          

            plateau->joueur->vie--;
        
            if(plateau->joueur->vie == 0){
                estFinie = true;
                printf("Partie terminée, vous êtes entré en collision\n");
                exit(1);
            }
        }            
    }
    
    return estFinie;
}

// fera apparaitre un tir en fonction de la position du joueur et de la touche
// xTir est affecté à la position -1 du joueur, car le tir sera toujours devant
// en fonction de la touche, on affectera le tir soit à gauche, à droit, ou devant.
void tirBike(char d, Plateau* plateau){

    int xTir = plateau->joueur->pos.x-1;
    int yTir;

    if(d == 'u' && plateau->joueur->pos.y != 1)
    {        
        yTir = plateau->joueur->pos.y-1;
        plateau->tab[xTir][yTir]=d;

    }
    else if(d == 'i')
    {
        yTir = plateau->joueur->pos.y;  
        plateau->tab[xTir][yTir]=d;      
    }
    else if(d == 'o' && plateau->joueur->pos.y != COLONNE-2)
    {
        yTir = plateau->joueur->pos.y+1;
        plateau->tab[xTir][yTir]=d;
    }  
}


void partie(int x, int y,Plateau* plateau ){
            
    //1. Dérouler le plateau de jeu
    deroulerPlateau(plateau);
    //2. Placement des nouvelles voitures si nécessaire
    //modifier les index des voitures deja placée    
        
    placerVoitures(plateau);


    checkTirEnnemi(plateau);
    //tirEnnemi(plateau);
    //3. Afficher le plateau
    afficherPlateau(plateau);
    //4. Checker si c'est la fin de la partie  
    if(checkTir(plateau)) {}        
    

    if(checkFinPartie(plateau) == false){
        printf("vie joueur : %i \n",plateau->joueur->vie);
    }

    else if(checkFinPartie(plateau)){
        exit(1);            
    }                 
        
}
