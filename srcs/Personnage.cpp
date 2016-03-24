/*-----------------------------

Objet Personnage

------------------------------*/
#include "Personnage.h"
#include "Arme.h"

using namespace std;

Personnage::Personnage()
{
    vie = 100; // Vie des personnages.
    puissance_defense = 0;

}

void Personnage::coeur()
{
    vie = vie + 20; // R�cup�re '20' de vie.
    if (vie > 100) // Sans d�passer '100' de vie.
        vie = 100;
}

void Personnage::degat(int force)
{
    if (force>puissance_defense)
    	vie = vie - (force-puissance_defense); // On perd de la vie en fonction de la force et de la defense.
    else if (force<puissance_defense) // Si la defense est plus grande que la force de l'arme, ont fait perdre de la vie 1 par 1.
        vie = (vie - 1);
    if (vie < 0)
        vie = 0;
}

bool Personnage::enVie()const
{
    if (vie > 0) // Si on a de la vie, on est encore vivant.
        return 1;
    else // Sinon on est mort.
        return 0;
}

int Personnage::getVie() const
{
    return vie; // Retourne la vie restante du personnage.
}

void Personnage::attaquer(Personnage &cible)
{ // On utilise un poiteur vers la cible indiquer en parametre.
    cible.degat(arme.getPuissance()); // On utilise la fonction degat avec comme parametre la puissance de l'arme.
}

string Personnage::getNomArme()const
{
    return arme.getNom(); // On retourne le nom de l'arme.
}

void Personnage::changerArme(int id)
{
    arme.changeArme(id); // Permet de changer d'arme en fonction de l'id (Cf Arme.cpp).
}

int Personnage::getPuissanceArme()const
{
    return arme.getPuissance(); // Retourne la puissance de l'arme.
}

void Personnage::setDefense(int intensiter)
{
    puissance_defense = intensiter;
}

int Personnage::getDefense()const
{
    return (puissance_defense);
}

void Personnage::setVie(int taux)
{
    if (taux < 0)
        vie = 0;
    if (taux > 100)
        vie = 100;
    else
        vie = taux;
}
