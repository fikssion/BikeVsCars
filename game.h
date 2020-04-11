#ifndef _GAME_H_
#define _GAME_H_

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

void timerIdele(int i);
void repopEnnemi(int count, int xCar, int yCar, Plateau* plateau);
bool checkTir(Plateau* plateau);
bool checkFinPartie(Plateau* plateau);
void tirBike(char d, Plateau* plateau);
void partie(int x, int y,Plateau* plateau);




#endif
