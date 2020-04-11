#ifndef _STRUCTURE_H_
#define _STRUCTURE_H_

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define COLONNE 40
#define LIGNE 39
#define Square_size 20.0

typedef enum Niveau{
	DEBUTANT=4,INTERMEDIAIRE=3,PRO=2
}Niveau;

typedef struct Position{
	int x;
	int y;
}Position;

typedef struct Car{
	int vie;
	Position pos;	
	bool tir;
}Car;

typedef struct Bike{
	int vie;
	int score;
	Position pos;
	char* nom;
}Bike;

typedef struct Plateau{
	Niveau niveau;
	char tab [LIGNE][COLONNE];
	Bike* joueur;
	int nbEnnemi;
	Car* cars [LIGNE/PRO];
} Plateau;


Bike * newJoueur();
Car * newEnnemi(int vie, int x, int y);
bool colision(Plateau* plateau);
void keyboard(unsigned char deplac, int x, int y);
Plateau* plateau;

void mouvement(char deplac,Plateau* plateau);
void moveLeft(Plateau* plateau);
void moveRight(Plateau* plateau);
void moveUp(Plateau* plateau);
void moveDown(Plateau* plateau);
void afficherPlateau(Plateau* plateau);
void deroulerPlateau(Plateau* plateau);
void placerVoitures(Plateau* plateau);
void checkTirEnnemi(Plateau* plateau);
bool tirEnnemi(Plateau* plateau);

#endif

