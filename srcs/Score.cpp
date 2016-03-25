#include "breadman.h"

void ecritureScore(int score)
{
    FILE* fichier = NULL;

    fichier = fopen("score.dat", "w+");
    fprintf(fichier, "%d",score);
    fclose(fichier);
}
int lectureScore()
{
    FILE* fichier = NULL;
    int score = 6;

    fichier = fopen("score.dat", "r");
    fscanf(fichier, "%d", &score);
    fclose(fichier);
    return score;
}
