#ifndef BREADMAN_H_INCLUDED
#define BREADMAN_H_INCLUDED

# include <SDL/SDL.h>
# include <stdio.h>
# include <stdlib.h>
# include <time.h>
# include <string>
# include <iostream>

# define TAILLE_BLOC         34
# define NB_BLOCS_LARGEUR    20
# define NB_BLOCS_HAUTEUR    20
# define LARGEUR_FENETRE     TAILLE_BLOC * NB_BLOCS_LARGEUR
# define HAUTEUR_FENETRE     TAILLE_BLOC * NB_BLOCS_HAUTEUR

using namespace std;

class Arme {
public :
    Arme();
    void changeArme(int idArme);
    std::string getNom()const;
    int getPuissance()const;

protected :
    std::string nom;
    int puissance;
};

class Personnage {// Definition d'une classe personnage.
    public :
    Personnage();
    void coeur(); // Rends de la vie.
    void attaquer(Personnage &cible); // Retire de la vie � Cible.
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

int aleatoire(void);
int aleatoire2(void);
int aleatoire3(void);
int aleatoire4(void);
int aleatoire5(void);
bool collision(SDL_Rect *pos,SDL_Rect *posE, int sens);
void deplacement(int carte[][NB_BLOCS_HAUTEUR], SDL_Rect *pos, int direction, int vitesse);
int chargerNiveau(int niveau[][NB_BLOCS_HAUTEUR]);
int sauvegarderNiveau(int niveau[][NB_BLOCS_HAUTEUR]);
void ecritureScore(int score);
int lectureScore();
void decouperSprite(SDL_Rect position[][5], int hauteur, int largeur, int lignes, int colonnes);

#endif // MAIN_H_INCLUDED
