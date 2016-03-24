/*-----------------------------

Assignation des images aux diff�rents tableaux pour les sprites
et d�coupage des sprites images

-----------------------------*/
#include "sprite.h"
#include <SDL/SDL.h>

void decouperSprite(SDL_Rect position[][5], int hauteur, int largeur, int lignes, int colonnes)
{
    for (int y=0; y<lignes; y++)
	{
        for (int i = 0; i<colonnes; i++)
		{
        	position[y][i].x = largeur * i;
        	position[y][i].y = hauteur * y;
        	position[y][i].w = largeur;
        	position[y][i].h = hauteur;
        }
    }
}
