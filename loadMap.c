#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>

#include "structure.h"
#include "loadMap.h"
#include "drawMap.h"

bool loadMap(int x, int y){
	
    FILE *f = NULL;
    //printf("ta mère load map \n");
    f = fopen("map2.txt", "r");
    if(f == NULL)
    {

    	printf("teste if == null");
        printf("file empty");
        return false;
    }
    char c;
    int i = 0;
    int j = 0;

    printf(" avant le boucle de création\n");
	
	//*(map + i) = malloc(sizeof(char *) * y);	
	for(i = 0; i < x; i++)
		{
		//*(map + i) = malloc(sizeof(char *) * y);	
			for(j = 0; j < y; j++)
			{		
				c = fgetc(f);
				plateau->tab[i][j]= c;
				//*(*(map + i) + j) = c;
			}
			fgetc(f);
		}

	    fclose(f);
		
	    printf("\n");

		for(i = 0; i < x; i++)
		{
			for(j = 0; j < y; j++)
			{
				printf("%c", plateau->tab[i][j]);
			}
			printf("\n");
		}				
		
	return true;
}


void writeMap(Plateau* plateau){

	FILE *f = NULL;
    f = fopen("map2.txt", "w+");

    if(f == NULL)
    {
        printf("file empty");
        return;
    }

	for(int i = 0; i < LIGNE; i++){
        for(int j = 0; j < COLONNE; j++){
        	 printf("%c",plateau->tab[i][j]);
            fputc(plateau->tab[i][j],f);           

        }
        printf("\n");
        fputc('\n',f);
    }

    fclose(f);

}

