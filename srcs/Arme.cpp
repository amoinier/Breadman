/*-----------------------------

Objet Arme

------------------------------*/
#include "Arme.h"

using namespace std;

Arme::Arme()
{
    nom = "Carambar"; // Arme de base de chaque personnage avec '10' de puissance.
    puissance = 10;

}
void Arme::changeArme(int idArme){

    switch(idArme)
	{
        case 1 :
            nom = "Carambar";
            puissance = 10;
            break;
        case 2 :
            nom = "Baguette de pain";
            puissance = 20;
            break;
        case 3 :
            nom = "Planche de pain";
            puissance = 30;
            break;
        case 4:
            nom = "Paris brest";
            puissance = 100;
            break;
    }

}

int Arme::getPuissance()const
{
    return puissance; // Retourne la puissance de l'arme.
}
string Arme::getNom()const
{
    return nom; // Retourne le nom de l'arme.
}
