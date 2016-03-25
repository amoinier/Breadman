#include "breadman.h"

int aleatoire(void)
{
	int i = 0;
	int nombre = 0;
	int valmin = 300;
	int valmax = 500;

	srand(time(NULL)); // Initialisation de rand gr�ce � 'time'.
	for(i = 0; i < 100; i++)
        nombre = valmin + (rand()%valmax); // Permet d'assigner � 'nombre' une valeur al�atoire.
    return nombre;
}

int aleatoire2(void)
{
	int i = 0;
	int nombre = 0;
	int valmin = 0;
	int valmax = 20;

	srand(time(NULL)); // Initialisation de rand gr�ce � 'time'.
	for(i = 0; i < 100; i++)
        nombre = valmin+(rand()%valmax); // Permet d'assigner � 'nombre' une valeur al�atoire.
    return nombre;
}

int aleatoire3(void)
{
	int i = 0;
	int nombre = 0;
	int valmin = 0;
	int valmax = 20;

	srand(time(NULL)); // Initialisation de rand gr�ce � 'time'.
	for(i = 0; i < 10; i++)
        nombre = valmin+(rand()%valmax); // Permet d'assigner � 'nombre' une valeur al�atoire.
    return nombre;
}

int aleatoire4(void)
{
	int i = 0;
	int nombre = 0;
	int valmin = 0;
	int valmax = 20;

	srand(time(NULL)); // Initialisation de rand gr�ce � 'time'.
	for(i = 0; i < 22; i++)
        nombre = valmin+(rand()%valmax); // Permet d'assigner � 'nombre' une valeur al�atoire.
    return nombre;
}

int aleatoire5(void){
	int i = 0;
	int nombre = 0;
	int valmin = 0;
	int valmax = 20;

	srand(time(NULL)); // Initialisation de rand gr�ce � 'time'.
	for(i = 0; i < 34; i++)
        nombre = valmin+(rand()%valmax); // Permet d'assigner � 'nombre' une valeur al�atoire.
    return nombre;
}
