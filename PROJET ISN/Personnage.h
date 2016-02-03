/*-----------------------------

Objet Personnage

------------------------------*/
#ifndef PERSONNAGE_H_INCLUDED
#define PERSONNAGE_H_INCLUDED
#include "Arme.h"

using namespace std;

class Personnage{ // Definition d'une classe personnage.

    public :

    Personnage();
    void coeur(); // Rends de la vie.
    void attaquer(Personnage &cible); // Retire de la vie à Cible.
    void degat(int force); // Retire de la vie.
    bool enVie() const; // Retourne '0' si le personnage est en vie, sinon retourne '1'.
    void changerArme(int id);
    int getVie() const; // Retourne la vie du personnage.
    string getNomArme()const; // Fonction get qui retourne le nom d'arme en type 'string'.
    int getPuissanceArme()const; // Fonction get qui retourne la puissance de l'arme (entre 1 et 100).
    void setDefense(int intensiter);
    int getDefense()const;
    void setVie(int taux);


    protected :
    int vie; // Nombre de vie /100.
    int puissance_arme;
    int puissance_defense;
    Arme arme;

};


#endif // PERSONNAGE_H_INCLUDED
