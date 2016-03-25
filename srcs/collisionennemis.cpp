#include "breadman.h"

bool collision(SDL_Rect *pos,SDL_Rect *posE, int sens)
{
    if (sens == 1)
	{ // Indique le sens du personnage.
        if ((pos->x + 6 >= posE->x + posE->w) || (pos->x + pos->w-6<=posE->x) ||
		(pos->y-2 >= posE->y + posE->h) || (pos->y + pos->h-10<=posE->y))
            return 0; // Retourne '0' si le personnage ne touche pas un autre personnage.
        else
            return 1; // Sinon retourne '1'.
    }
    if (sens == 2)
	{
        if((pos->x + 6 >= posE->x + posE->w) || (pos->x + pos->w-6<=posE->x) ||
		(pos->y) + 5 >= (posE->y + posE->h) || (pos->y + pos->h)<=(posE->y))
            return 0;
        else
            return 1;
    }
    if (sens == 3)
	{
        if((pos->x >= posE->x + posE->w) || (pos->x + pos->w-6<=posE->x) ||
		(pos->y + pos->h)-3<=(posE->y) || (pos->y) + 3 >= (posE->y + posE->h))
            return 0;
        else
            return 1;
    }
    if (sens == 4)
	{
        if((pos->x + 6 >= posE->x + posE->w) || (pos->x + pos->w<=posE->x) ||
		(pos->y + pos->h)-3<=(posE->y) || (pos->y) + 3 >= (posE->y + posE->h))
            return 0;
        else
            return 1;
    }
    return (1);
}
