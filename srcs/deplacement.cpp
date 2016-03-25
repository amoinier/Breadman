/*-----------------------------

Gestion des d�placement,
collisions avec des obstacles

------------------------------*/
#include "breadman.h"

void deplacement(int carte[][NB_BLOCS_HAUTEUR], SDL_Rect *pos, int direction, int vitesse)
{
    switch(direction)
    {
        case 1:
            if ((pos->y) <= 0) // Verifie qu'il n'est pas au bord du mur.
                break;
            if (carte[(pos->x) / TAILLE_BLOC][(pos->y-1) / TAILLE_BLOC] == 1 ||
                carte[(pos->x) / TAILLE_BLOC][(pos->y-1) / TAILLE_BLOC] == 4) // V�rifie qu'il y a un mur ou un arbre.
                break;
            if (carte[((pos->x)+(pos->w)) / TAILLE_BLOC][((pos->y)-1) / TAILLE_BLOC] == 1 ||
                carte[((pos->x)+(pos->w)) / TAILLE_BLOC][((pos->y)-1) / TAILLE_BLOC] == 4) // V�rifie qu'il y a un mur ou un arbre.
                break;
            pos->y=pos->y-vitesse; // Deplacement du personnage.
            break;


        case 2:
            if ((((pos->y) + (pos->h)+1) == TAILLE_BLOC * NB_BLOCS_HAUTEUR))
                break;
            if (carte[((pos->x)+pos->w) / TAILLE_BLOC][((pos->y)+(pos->h)+1) / TAILLE_BLOC] == 1 ||
                carte[((pos->x)+pos->w) / TAILLE_BLOC][((pos->y)+(pos->h)+1) / TAILLE_BLOC] == 4)
                break;
            if (carte[(pos->x) / TAILLE_BLOC][((pos->y)+(pos->h)+1) / TAILLE_BLOC] == 1 ||
                carte[(pos->x) / TAILLE_BLOC][((pos->y)+(pos->h)+1) / TAILLE_BLOC] == 4)
                break;
            pos->y=pos->y+vitesse;
            break;


        case 3:
            if ((pos->x) <= 0)
                break;
            if (carte[(pos->x-1) / TAILLE_BLOC][(pos->y) / TAILLE_BLOC] == 1 ||
                carte[(pos->x-1) / TAILLE_BLOC][(pos->y) / TAILLE_BLOC] == 4)
                break;
            if (carte[(pos->x-1) / TAILLE_BLOC][((pos->y)+(pos->h)) / TAILLE_BLOC] == 1 ||
                carte[(pos->x-1) / TAILLE_BLOC][((pos->y)+(pos->h)) / TAILLE_BLOC] == 4)
                break;
            pos->x=pos->x-vitesse;
            break;


        case 4:
            if (((pos->x) + pos->w) == TAILLE_BLOC * NB_BLOCS_LARGEUR)
                break;
            if (carte[((pos->x)+(pos->w)+1) / TAILLE_BLOC][((pos->y)+(pos->h)) / TAILLE_BLOC] == 1 ||
                carte[((pos->x)+(pos->w)+1) / TAILLE_BLOC][((pos->y)+(pos->h)) / TAILLE_BLOC] == 4)
                break;
            if (carte[((pos->x)+(pos->w)+1) / TAILLE_BLOC][(pos->y) / TAILLE_BLOC] == 1 ||
                carte[((pos->x)+(pos->w)+1) / TAILLE_BLOC][(pos->y) / TAILLE_BLOC] == 4)
                break;
            pos->x=pos->x+vitesse;
            break;
    }
}
