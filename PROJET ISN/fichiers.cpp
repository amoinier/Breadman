/*-----------------------------

Lecture et écriture du fichier
"level.map"

------------------------------*/
#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL.h>

#include "constantes.h"
#include "fichiers.h"

int chargerNiveau(int niveau[][NB_BLOCS_HAUTEUR])
{
    FILE *fichier = NULL;
    char ligneFichier[NB_BLOCS_LARGEUR * NB_BLOCS_HAUTEUR + 1] = {0}; // Création d'un tableau 'char'.
    int i = 0, j = 0;

    fichier = fopen("niveaux.map", "r"); // Ouverture du fichier 'niveaux.map'.
    if (fichier == NULL)
        return 0;

    fgets(ligneFichier, NB_BLOCS_LARGEUR * NB_BLOCS_HAUTEUR + 1, fichier); // Lecture du contenue du fichier 'niveaux.map'.

    for (i = 0 ; i < NB_BLOCS_LARGEUR ; i++)
    {
        for (j = 0 ; j < NB_BLOCS_HAUTEUR ; j++)
        {
            switch (ligneFichier[(i * NB_BLOCS_LARGEUR) + j])
            {
                case '0':
                    niveau[j][i] = 0;
                    break;
                case '1':
                    niveau[j][i] = 1;
                    break;
                case '2':
                    niveau[j][i] = 2;
                    break;
                case '3':
                    niveau[j][i] = 3;
                    break;
                case '4':
                    niveau[j][i] = 4;
                    break;
            }
        }
    }

    fclose(fichier); // Fermeture du fichier.
    return 1;
}
