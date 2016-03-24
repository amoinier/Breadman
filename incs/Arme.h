/*-----------------------------

Objet Arme

------------------------------*/
#ifndef ARME_H_INCLUDED
#define ARME_H_INCLUDED
#include <string>

class Arme{

public :

    Arme();
    void changeArme(int idArme);
    std::string getNom()const;
    int getPuissance()const;

protected :

    std::string nom;
    int puissance;

};

#endif // ARME_H_INCLUDED
