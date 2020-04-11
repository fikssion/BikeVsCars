#ifdef __APPLE_CC__
#include <OpenGL/OpenGL.h>
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include "structure.h"
#include "game.h"
#include "loadMap.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

/**
 * Initialise un nouveau joueur
 **/
Bike * newJoueur(){ 
    Bike * joueur = malloc(sizeof(Bike));
    joueur->vie=3;
    // On positionne le joueur sur la derniere ligne
    joueur->pos.x=LIGNE-2;
    // On positionne le joueur au milieu du plateau
    joueur->pos.y=(COLONNE/2)-1;
    return joueur;
}

/**
 * Initialise une nouvelle voiture (ennemi)
 **/
Car * newEnnemi(int vie, int x, int y){
    Car * ennemi = malloc(sizeof(Car));
    ennemi->vie=vie;
    ennemi->pos.x=x;
    ennemi->pos.y=y;
    ennemi->tir = false;
    
    return ennemi;
}

void mouvement(char deplac,Plateau* plateau){


    int x = plateau->joueur->pos.x;
    int y = plateau->joueur->pos.y;

    switch (deplac){
            /* deplacement vers le bas */
            case 's' : {
                if(x<LIGNE-2){
                    plateau->tab[x+1][y]='X';
                    plateau->tab[x][y]=' ';   
                    plateau->joueur->pos.x++;
                }
            }
            break ;
            
            /* deplacement vers la droite */
            case 'd' : {
                if(y<COLONNE-2){

                    plateau->tab[x][y+1]='X';
                    plateau->tab[x][y]= ' ';   
                    plateau->joueur->pos.y++;
                }
            }
            break ;
            
            /* deplacement vers le haut */
            case 'z' : {
                if(x>1){
                    plateau->tab[x-1][y]='X';
                    plateau->tab[x][y]=' ';   
                    plateau->joueur->pos.x--;
                }
            }
            break ;
            
            /* deplacement vers la gauche */
            case 'q' : {
                if(y>1){
                    plateau->tab[x][y-1]='X';
                    plateau->tab[x][y]=' ';   
                    plateau->joueur->pos.y--;
                }
            }
            break ;
        
    }
}


/**
 * Affiche le plateau de jeu
 */
void afficherPlateau(Plateau* plateau){
    for(int i = 0; i < LIGNE; i++){
        for(int j = 0; j < COLONNE; j++){
            printf("%c",plateau->tab[i][j]);
        }
        printf("\n");
    }   
}

void deroulerPlateau(Plateau* plateau){

    for(int i = LIGNE-2; i>=1 ; i--){
        for(int j = COLONNE-2; j>=1; j--){
            if(i==1){
                if(plateau->tab[i][j]!='X')
                {
                    plateau->tab[i][j]=' ';
                    // ici pour faire apparaitre les lignes de route central?
                }                
                
            }else /*if(i==LIGNE-2)*/{
                char d = plateau->tab[i][j];
                // conserve la voiture et les tirs sur la ligne courante.
                if(d!='X' && d!='i' && d!='u' && d!='o'){
                    char k = plateau->tab[i-1][j];
                    // empeche de copier les voitures et les tirs des lignes précédente.
                    if(k!='X' && k!='i'&& k!='u'&& k!='o'){                                               
                        
                        plateau->tab[i][j]=plateau->tab[i-1][j];                        

                    }else{
                        plateau->tab[i][j]=' ';                  
                    }
                }                   
            }
        }
    }

    //Boucle spécifique pour dérouler les tirs du bas vers le haut.
    for(int i = 1; i<LIGNE-1; i++){
        for(int j = 1; j<COLONNE-1;j++){
            char d = plateau->tab[i][j];
            //char w = plateau->tab[i+1][j];

            // condition qui vient vérifier si on est sur le bord de la map
            // et remple le tir qui arrive en haut, par un ' '
            if(i==1){
                plateau->tab[i][j]= ' ';  
            }                              
             
            // propage les tirs dans la bonne direction
            else{
                if(d=='i'){                    
                    plateau->tab[i-1][j] = plateau->tab[i][j];
                    plateau->tab[i][j] = ' ';
                }
                if(d=='u'){
                    if(j != 1){
                        plateau->tab[i-1][j-1] = plateau->tab[i][j];
                    }                    
                    plateau->tab[i][j] = ' ';
                }
                if(d=='o'){
                    if( j != COLONNE-2){
                        plateau->tab[i-1][j+1] = plateau->tab[i][j];  
                    }                    
                    plateau->tab[i][j] = ' ';
                }
            } 
        }
    }   

    // boucle pour les tirs voitures 
    for(int i = LIGNE-1; i>0; i--){
        for(int j = COLONNE-2; j>1;j--){

            // 2 conditions car incrémente le tir de 2 ref ligne 185
            if(i == LIGNE-1 || i == LIGNE-2){
                if(plateau->tab[i][j] == 't'){                    
                    plateau->tab[i][j] = ' ';                   
                }       
            }
            else{
                if(plateau->tab[i][j] == 't'){               
                                     
                   plateau->tab[i][j] =' ';
                   plateau->tab[i+1][j] = 't';
                }  
            }
        }
    }
}


void placerVoitures(Plateau* plateau){
    //1. On incrémente la position x de toute les voitures déjà placées jusqu'à LIGNE-2
    //Une fois LIGNE-2 atteint, on reset les x et y à -1
    for(int i=0;i<plateau->nbEnnemi;i++){
        
        //On commence a checker a la ligne 1, donc on commence à l'index 1 minimum
        if(plateau->cars[i]->pos.x > 0 && plateau->cars[i]->pos.y > 0){
            if(plateau->cars[i]->pos.x<LIGNE-2){
                plateau->cars[i]->pos.x++;  
                  


                // rajouter un Srand pour les mouvement de gauche à droite 
            }else{
                plateau->cars[i]->pos.x=-1;    
                plateau->cars[i]->pos.y=-1;    
            }            
        }
    }
    //2 .On check s'il reste des voitures de dispo (dont x et y == -1)
    for(int i=0;i<plateau->nbEnnemi;i++){
        if(plateau->cars[i]->pos.x == -1 && plateau->cars[i]->pos.y == -1){
            //On peut placer la voiture sur la premiere ligne
            //Et on utilise un srand pour choisir aleatoirement sa colonne
            //srand(time(NULL)); // initialisation de rand
            int j = (rand()%COLONNE-2)+1;
            plateau->tab[1][j]='e';
            plateau->cars[i]->pos.x=1;
            plateau->cars[i]->pos.y=j;
            plateau->cars[i]->tir = false;
            //Break pour sortir de la boucle si on a trouvé une voiture qui peut etre placée
            //Sinon, il va assigner toutes celle qui ont des coordonnées à -1
            break;
        }
    }
}

//on va vérifié si un véhicule à déjà tiré
// fonctionne pas terrible ! 
void checkTirEnnemi(Plateau* plateau){

    for(int i=LIGNE-2;i>0;i--){
        for(int j=COLONNE-2;j>0;j--){             
            for(int k=0;k<plateau->nbEnnemi;k++){

                int xCar = plateau->cars[k]->pos.x;
                int yCar = plateau->cars[k]->pos.y;
                if(plateau->tab[i][j] == plateau->tab[xCar][yCar]){
                    if(plateau->cars[k]->tir == false){
                        tirEnnemi(plateau);
                    }                    
                }                     
            }
        }
    }
}

// fonctionne pas bien  ! 
bool tirEnnemi(Plateau* plateau){

    int a;

    for(int i=LIGNE-2;i>0;i--){
        for(int j=COLONNE-2;j>0;j--){ 
            // reglé pour le tir aléatoire            
            for(int k = 0;k<plateau->nbEnnemi; k++){ 

                int xCar = plateau->cars[k]->pos.x;
                int yCar = plateau->cars[k]->pos.y;

                if(plateau->tab[i][j] == plateau->tab[xCar][yCar]){

                    if(plateau->cars[k]->tir == false){  

                        // recupère l'index de K, pour retourner le bool.
                        a=k;                   

                        plateau->tab[xCar+1][yCar] = 't';                      
                        plateau->cars[k]->tir = true;
                    }                   
                } 
            }           
        }
    }

    return plateau->cars[a]->tir;
}
