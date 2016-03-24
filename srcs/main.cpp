/*-----------------------------

Fichier principale,
Gestion principale de la SDL

------------------------------*/

// Include des diff�rentes librairies utilis�es.
#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL.h>
#include <iostream>
#include <string>
#include <SDL/SDL_ttf.h>

// Include des fonctions et objets dans les autres fichiers.
#include "constantes.h"
#include "Arme.h"
#include "fichiers.h"
#include "deplacement.h"
#include "Personnage.h"
#include "collisionennemis.h"
#include "sprite.h"
#include "aleatoire.h"
#include "Score.h"


using namespace std;

int main(int argc, char *argv[])
{
    Personnage bread, ennemi; // Cr�ation des diff�rents objets personnages.

    SDL_Surface *ecran = NULL, *mur = NULL, *arbre = NULL, *textefin = NULL, *textefin2 = NULL, *textefin3 = NULL, *coeur = NULL; // Cr�ation de diff�rents poiteurs pour les surfaces.
    SDL_Event event;
    SDL_Rect positionHero; // Gere les positions du Hero
    SDL_Rect position; // Gere les positions de la carte
    SDL_Rect positionEnnemis; // Gere la position des Ennemis
    SDL_Rect positionArme; // Gere la position des Armes.
    SDL_Rect positionTexte; // Gere la position de la partie 1 des texte.
    SDL_Rect positionTexte2; // Gere la position de la partie 2 des texte.
    SDL_Rect positionTexte3;
    SDL_Rect positionCoeur; // Gere la position des coeurs.
    SDL_Rect positionArmeE; // Gere la position des Armes.
    bool vraie = 1; // Variable permettant de sortir de la boucle
    int i = 0, j = 0; // Variables pour la carte.
    int carte[NB_BLOCS_LARGEUR][NB_BLOCS_HAUTEUR]; // Tableau qui stock les diff�rents objets de la cartes.
    int score = 0, xaleatoire = 0, yaleatoire = 0, xcaleatoire = 0, ycaleatoire = 0;
    char perdue[100] = "";
    char hs[100] = "";
    int meilleur = 0;

    int tempsActuel = 0, tempsPrecedent = 0, tempsPrecedent2 = 0, tempsPrecedent3 = 0, tempsPrecedent4 = 0, tempsPrecedent5 = 0, tempsPrecedent6 = 0; // Variables pour comparaison du temps (annimation des sprites);

    SDL_Init(SDL_INIT_VIDEO); // Initialisation de la partie vid�o de la SDL.

    TTF_Init();
    TTF_Font *police = NULL;
    police = TTF_OpenFont("testpolice.ttf", 100);
    SDL_Color blanc = {255,255,255};

    ecran = SDL_SetVideoMode(LARGEUR_FENETRE, HAUTEUR_FENETRE, 32, SDL_HWSURFACE|SDL_DOUBLEBUF); // D�finition de l'�cran.
    SDL_WM_SetCaption( "BreadMan", NULL); // Parametre le nom de la fen�tre.

    // Assignation des image aux diff�rents tableaux pour les sprites.

    // Gestion de l'image du h�ro.
    SDL_Surface *imageHeroe = SDL_LoadBMP ("Ressources/images/heroeSprites.bmp");
    SDL_Rect heroeSens[4][5];
    decouperSprite(heroeSens, 27, 16, 4, 4);
    SDL_Rect nouveauSensHeroe = heroeSens[1][1];
    int n = 1; // Variable utilis� pour l'animation du h�ro.

    // Gestion de l'image du h�ro.
    SDL_Surface *imageEnnemi = SDL_LoadBMP ("Ressources/images/ennemiSprites.bmp");
    SDL_Rect ennemiSens[4][5];
    decouperSprite(ennemiSens, 27, 16, 4, 4);
    SDL_Rect nouveauSensEnnemi = ennemiSens[0][0];
    int w = 1;

    // Gestion de l'image des d�cors.
    SDL_Surface *feuille_image = SDL_LoadBMP ("Ressources/images/decors/feuilleSprites.bmp");
    SDL_Rect feuilleFrame[1][5];
    decouperSprite(feuilleFrame, 34, 34, 1, 4);
    SDL_Rect nouvelleFeuilleFrame = feuilleFrame[0][0];
    int v = 1; // Variable pour l'animation des d�cors.

    // Gestion de l'image des armes.
    SDL_Surface *imageArme = SDL_LoadBMP ("Ressources/images/heroe/ventSprite.bmp");
    SDL_Rect armeSens[4][5];
    decouperSprite(armeSens, 50, 50, 4, 5);
    SDL_Rect nouveauSensArme = armeSens[0][0];
    int im = 0;
    int variableSensHeroe = 1;

    // Gestion de l'image des armes ennemies.
    SDL_Surface *imageArmeE = SDL_LoadBMP ("Ressources/images/ennemi/ventSprite.bmp");
    SDL_Rect armeSensEnnemie[4][5];
    decouperSprite(armeSensEnnemie, 50, 50, 4, 5);
    SDL_Rect nouveauSensArmeEnnemi = armeSensEnnemie[0][0];
    int em = 0;
    int variableSensEnnemi = 1;

    // Gestion d'image de differents �l�ments.
    mur = SDL_LoadBMP ("Ressources/images/cailloux.bmp");
    arbre = SDL_LoadBMP ("Ressources/images/decors/arbres.bmp");
    coeur = SDL_LoadBMP ("Ressources/images/decors/coeur.bmp");

    // Chargement de la carte.
    if (!chargerNiveau(carte))
    exit(EXIT_FAILURE); // Arr�t du programme si 'niveaux.map' n'a pas pu �tre ouvert.


    // Gestion des positions � l'aide de SDl_Rect.
    // Position hero :
    positionHero.x = LARGEUR_FENETRE/2; // On positionne le h�ro au milieu de la fen�tre.
    positionHero.y = HAUTEUR_FENETRE/2;
    positionHero.w = 16; // On indique la taille du sprite en pixel.
    positionHero.h = 27;

    // Position de l'ennemie.
    positionEnnemis.x = 5*34; // On positionne le h�ro au milieu de la fen�tre.
    positionEnnemis.y = 5*34;
    positionEnnemis.w = 16; // On indique la taille du sprite en pixel.
    positionEnnemis.h = 27;

    // Placement de l'arme dans la main du hero.
    positionArme.w = 50;
    positionArme.h = 50;
    positionArme.x = 1500;
    positionArme.y = 1500;

    // Placement de l'arme dans la main de l'ennemi.
    positionArmeE.w = 50;
    positionArmeE.h = 50;
    positionArmeE.x = 1500;
    positionArmeE.y = 1500;

    // Placement des coeurs au d�but
    positionCoeur.w = 34;
    positionCoeur.h = 34;
    positionCoeur.x = 1500;
    positionCoeur.y = 1500;

    // Diff�rentes jauges de vie.
    SDL_Surface *jaugeVieImage= SDL_LoadBMP ("Ressources/images/jauge.bmp");//chargement de l'image de la jauge

    // Jauge de l'ennemie.
    SDL_Rect jaugeDeVieEnnemiPosition;//cr�ation d'un sdl rect pour la position de la jauge
    SDL_Rect jaugeDeVieEnnemiValeur;//cr�ation d'un sdl rect pour la selection de la partie de l'image de la jauge voulue
    jaugeDeVieEnnemiPosition.x = positionEnnemis.x;//on positionne la jauge au dessu de l'ennemie
    jaugeDeVieEnnemiPosition.y = positionEnnemis.y -5;
    jaugeDeVieEnnemiValeur.x=0;//on place le rectange au debut de l'image de la jauge
    jaugeDeVieEnnemiValeur.y=0;
    jaugeDeVieEnnemiValeur.h=3;//on indique la taille finale de la jauge
    jaugeDeVieEnnemiValeur.w=16;

    // Jauge du heroe.
    SDL_Rect jaugeDeVieHeroePosition;
    SDL_Rect jaugeDeVieHeroeValeur;
    jaugeDeVieHeroePosition.x = positionHero.x;
    jaugeDeVieHeroePosition.y = positionHero.y -5;
    jaugeDeVieHeroeValeur.x=0;
    jaugeDeVieHeroeValeur.y=0;
    jaugeDeVieHeroeValeur.h=3;
    jaugeDeVieHeroeValeur.w=16;

    // Active la r�p�tition des touches pour �viter d'appuyer plusieurs fois sur les touches
    SDL_EnableKeyRepeat(1,1);

    // Parametres des armes et de la d�fense des personnages.
    bread.changerArme(1);
    ennemi.changerArme(1);
    bread.setDefense(3);
    ennemi.setDefense(0);

    while(vraie) // Boucle principale.
    {
        // Actualisation de la jauge de l'ennemie en fonction de sa vie et de sa position.
        jaugeDeVieEnnemiPosition.x = positionEnnemis.x;
        jaugeDeVieEnnemiPosition.y = positionEnnemis.y -5;
        jaugeDeVieEnnemiValeur.x=0.16*(100-ennemi.getVie());
        /*comme la jauge fais 16px et que la valeurs de la vie
        va de 0 � 100 on multiplie par 0.16).*/

        // Actualisation de la jauge du h�roe en fonction de sa vie et de sa position.
        jaugeDeVieHeroePosition.x = positionHero.x;
        jaugeDeVieHeroePosition.y = positionHero.y-5;
        jaugeDeVieHeroeValeur.x=0.16*(100-bread.getVie());

        SDL_Delay(5); // Ralentissement de la vitesse du personnage.

        tempsActuel = SDL_GetTicks(); // Affectation � tempsActuel, le temps en secondes.

        SDL_PollEvent(&event); // Permet d'enchainer et ne pas avoir de pause entre chaque evenement.

        if (tempsActuel - tempsPrecedent2 > 100){ // Animation des fleurs.
        tempsPrecedent2 = tempsActuel; // On reaffecte � temps pr�cedent le temps actuel.
        if (v>3){v=0;} // Si on d�passe 4 on retourne � 1.
        nouvelleFeuilleFrame = feuilleFrame[0][v]; // On stock l'image de la feuille dans la variable finale.
        v++;
        }

        /* Ces lignes de codes permettent de g�r� les d�placement et les collisions avec un ennemi,
        ainsi que l'animation, le deplacement et la collision de l'ennemi.*/

        Uint8 *keystates = SDL_GetKeyState( NULL ); // Initialisation de 'SDL_GetKeyState' et son raccourcis.
        if (keystates[SDLK_UP]){
            variableSensHeroe = 0;
            // Tout le code jusqu'au 'deplacement' sert � animer le sprite avec 4 images.
            if (tempsActuel - tempsPrecedent > 100){ // Si 100ms ce sont �coul�.
                tempsPrecedent = tempsActuel; // On affecte a la variable temps pr�c�dent le temps actuel.
                if (n>3){n=0;} // Si n est sup�rieur � 4 on retourne � 1 pour faire l'animation en boucle.
                    nouveauSensHeroe = heroeSens[0][n]; // On affecte l'image � charger.
                    n++; // On incr�mente n.
                }
                if (collision(&positionHero, &positionEnnemis, 1) == 0 ){
                    deplacement(carte, &positionHero, 1, 1);
                }
        }
        if (keystates[SDLK_DOWN]){
            variableSensHeroe = 1;
            if (tempsActuel - tempsPrecedent > 100){
                tempsPrecedent = tempsActuel;
                if (n>3){n=0;}
                    nouveauSensHeroe = heroeSens[1][n];
                    n++;
                }
            if (collision(&positionHero, &positionEnnemis, 2) == 0 ){
                deplacement(carte, &positionHero, 2, 1);
            }
        }
        if (keystates[SDLK_LEFT]){
            variableSensHeroe = 2;
            if (tempsActuel - tempsPrecedent > 100){
                tempsPrecedent = tempsActuel;
                if (n>3){n=0;}
                    nouveauSensHeroe = heroeSens[2][n];
                    n++;
                }
            if (collision(&positionHero, &positionEnnemis, 3) == 0 ){
                deplacement(carte, &positionHero, 3, 1);
                }
        }
        if (keystates[SDLK_RIGHT]){
            variableSensHeroe = 3;
            if (tempsActuel - tempsPrecedent > 100){
                tempsPrecedent = tempsActuel;
                if (n>3){n=0;}
                    nouveauSensHeroe = heroeSens[3][n];
                    n++;
                }
            if (collision(&positionHero, &positionEnnemis, 4) == 0 ){
                deplacement(carte, &positionHero, 4, 1);
                }
        }

        if ((((positionHero.x/TAILLE_BLOC) == positionEnnemis.x/TAILLE_BLOC) && ((positionHero.y/TAILLE_BLOC)-1 == positionEnnemis.y/TAILLE_BLOC)) ||
            ((((positionHero.x/TAILLE_BLOC) == positionEnnemis.x/TAILLE_BLOC) && (positionHero.y/TAILLE_BLOC)-2 == positionEnnemis.y/TAILLE_BLOC))){
                if(collision(&positionEnnemis, &positionHero, 2) == 0){
                    if (tempsActuel - tempsPrecedent4 > 100){ // Si 100ms se sont �coul�.
                        tempsPrecedent4 = tempsActuel; // On affecte a la variable temps pr�c�dent le temps actuel.
                        if (w>3){w=0;} // Si w est sup�rieur � 4 on retourne � 1 pour faire l'animation en boucle.
                            nouveauSensEnnemi = ennemiSens[1][w]; // On affecte l'image � charger.
                            w++; // On incr�mente w.
                        }
                    deplacement(carte, &positionEnnemis, 2, 1);
                    variableSensEnnemi = 1;
                }

            }

        else if (((positionHero.x/TAILLE_BLOC) == positionEnnemis.x/TAILLE_BLOC && (positionHero.y/TAILLE_BLOC)+1 == positionEnnemis.y/TAILLE_BLOC) ||
                 ((positionHero.x/TAILLE_BLOC) == positionEnnemis.x/TAILLE_BLOC && (positionHero.y/TAILLE_BLOC)+2 == positionEnnemis.y/TAILLE_BLOC)){
                if(collision(&positionEnnemis, &positionHero, 1) == 0){
                    if (tempsActuel - tempsPrecedent4 > 100){ // Si 100ms se sont �coul�.
                        tempsPrecedent4 = tempsActuel; // On affecte a la variable temps pr�c�dent le temps actuel.
                        if (w>3){w=0;} // Si w est sup�rieur � 4 on retourne � 1 pour faire l'animation en boucle.
                            nouveauSensEnnemi = ennemiSens[0][w]; // On affecte l'image � charger.
                            w++; // On incr�mente w.
                        }
                    deplacement(carte, &positionEnnemis, 1, 1);
                    variableSensEnnemi = 0;
                }
            }

        else if (((positionHero.x/TAILLE_BLOC)-1 == positionEnnemis.x/TAILLE_BLOC && (positionHero.y/TAILLE_BLOC) == positionEnnemis.y/TAILLE_BLOC) ||
                 ((positionHero.x/TAILLE_BLOC)-2 == positionEnnemis.x/TAILLE_BLOC && (positionHero.y/TAILLE_BLOC) == positionEnnemis.y/TAILLE_BLOC)){
                if(collision(&positionEnnemis,&positionHero, 4) == 0){
                    if (tempsActuel - tempsPrecedent4 > 100){ // Si 100ms ce sont �coul�.
                        tempsPrecedent4 = tempsActuel; // On affecte a la variable temps pr�c�dent le temps actuel.
                        if (w>3){w=0;} // Si w est sup�rieur � 4 on retourne � 1 pour faire l'animation en boucle.
                            nouveauSensEnnemi = ennemiSens[3][w]; // On affecte l'image � charger.
                            w++; // On incr�mente w.
                        }
                    deplacement(carte, &positionEnnemis, 4, 1);
                    variableSensEnnemi = 3;
                }
            }

        else if (((positionHero.x/TAILLE_BLOC)+1 == positionEnnemis.x/TAILLE_BLOC && (positionHero.y/TAILLE_BLOC) == positionEnnemis.y/TAILLE_BLOC) ||
                 ((positionHero.x/TAILLE_BLOC)+2 == positionEnnemis.x/TAILLE_BLOC && (positionHero.y/TAILLE_BLOC) == positionEnnemis.y/TAILLE_BLOC)){
                if(collision(&positionEnnemis,&positionHero, 3) == 0){
                    if (tempsActuel - tempsPrecedent4 > 100){ // Si 100ms ce sont �coul�.
                        tempsPrecedent4 = tempsActuel; // On affecte a la variable temps pr�c�dent le temps actuel.
                        if (w>3){w=0;} // Si w est sup�rieur � 4 on retourne � 1 pour faire l'animation en boucle.
                            nouveauSensEnnemi = ennemiSens[2][w]; // On affecte l'image � charger.
                            w++; // On incr�mente w.
                        }
                    deplacement(carte, &positionEnnemis, 3, 1);
                    variableSensEnnemi = 2;
                }
            }
        else if (((positionHero.x/TAILLE_BLOC)-1 == positionEnnemis.x/TAILLE_BLOC && (positionHero.y/TAILLE_BLOC)+1 == positionEnnemis.y/TAILLE_BLOC) ||
                 ((positionHero.x/TAILLE_BLOC)-2 == positionEnnemis.x/TAILLE_BLOC && (positionHero.y/TAILLE_BLOC)+2 == positionEnnemis.y/TAILLE_BLOC)){
                if(collision(&positionEnnemis,&positionHero, 4) == 0 || collision(&positionEnnemis,&positionHero, 1) == 0){
                    if (tempsActuel - tempsPrecedent4 > 100){ // Si 100ms se sont �coul�.
                        tempsPrecedent4 = tempsActuel; // On affecte a la variable temps pr�c�dent le temps actuel.
                        if (w>3){w=0;} // Si w est sup�rieur � 4 on retourne � 1 pour faire l'animation en boucle.
                            nouveauSensEnnemi = ennemiSens[0][w]; // On affecte l'image � charger.
                            w++; // On incr�mente w.
                        }
                    deplacement(carte, &positionEnnemis, 4, 1);
                    deplacement(carte, &positionEnnemis, 1, 1);
                }
            }
        else if (((positionHero.x/TAILLE_BLOC)-1 == positionEnnemis.x/TAILLE_BLOC && (positionHero.y/TAILLE_BLOC)-1 == positionEnnemis.y/TAILLE_BLOC) ||
                 ((positionHero.x/TAILLE_BLOC)-2 == positionEnnemis.x/TAILLE_BLOC && (positionHero.y/TAILLE_BLOC)-2 == positionEnnemis.y/TAILLE_BLOC)){
                if(collision(&positionEnnemis,&positionHero, 4) == 0 || collision(&positionEnnemis,&positionHero, 2) == 0){
                    if (tempsActuel - tempsPrecedent4 > 100){ // Si 100ms se sont �coul�.
                        tempsPrecedent4 = tempsActuel; // On affecte a la variable temps pr�c�dent le temps actuel.
                        if (w>3){w=0;} // Si w est sup�rieur � 4 on retourne � 1 pour faire l'animation en boucle.
                            nouveauSensEnnemi = ennemiSens[1][w]; // On affecte l'image � charger.
                            w++; // On incr�mente w.
                        }
                    deplacement(carte, &positionEnnemis, 4, 1);
                    deplacement(carte, &positionEnnemis, 2, 1);
                }
            }
        else if (((positionHero.x/TAILLE_BLOC)+1 == positionEnnemis.x/TAILLE_BLOC && (positionHero.y/TAILLE_BLOC)-1 == positionEnnemis.y/TAILLE_BLOC) ||
                 ((positionHero.x/TAILLE_BLOC)+2 == positionEnnemis.x/TAILLE_BLOC && (positionHero.y/TAILLE_BLOC)-2 == positionEnnemis.y/TAILLE_BLOC)){
                if(collision(&positionEnnemis,&positionHero, 3) == 0 || collision(&positionEnnemis,&positionHero, 2) == 0){
                    if (tempsActuel - tempsPrecedent4 > 100){ // Si 100ms se sont �coul�.
                        tempsPrecedent4 = tempsActuel; // On affecte a la variable temps pr�c�dent le temps actuel.
                        if (w>3){w=0;} // Si w est sup�rieur � 4 on retourne � 1 pour faire l'animation en boucle.
                            nouveauSensEnnemi = ennemiSens[1][w]; // On affecte l'image � charger.
                            w++; // On incr�mente w.
                        }
                    deplacement(carte, &positionEnnemis, 3, 1);
                    deplacement(carte, &positionEnnemis, 2, 1);
                }
            }
        else if (((positionHero.x/TAILLE_BLOC)+1 == positionEnnemis.x/TAILLE_BLOC && (positionHero.y/TAILLE_BLOC)+1 == positionEnnemis.y/TAILLE_BLOC) ||
                 ((positionHero.x/TAILLE_BLOC)+2 == positionEnnemis.x/TAILLE_BLOC && (positionHero.y/TAILLE_BLOC)+2 == positionEnnemis.y/TAILLE_BLOC)){
                if(collision(&positionEnnemis,&positionHero, 3) == 0 || collision(&positionEnnemis,&positionHero, 1) == 0){
                    if (tempsActuel - tempsPrecedent4 > 100){ // Si 100ms se sont �coul�.
                        tempsPrecedent4 = tempsActuel; // On affecte a la variable temps pr�c�dent le temps actuel.
                        if (w>3){w=0;} // Si w est sup�rieur � 4 on retourne � 1 pour faire l'animation en boucle.
                            nouveauSensEnnemi = ennemiSens[0][w]; // On affecte l'image � charger.
                            w++; // On incr�mente w.
                        }
                    deplacement(carte, &positionEnnemis, 3, 1);
                    deplacement(carte, &positionEnnemis, 1, 1);
                }
            }

            if (tempsActuel - tempsPrecedent5 > aleatoire()){
                tempsPrecedent5 = tempsActuel;
                if(collision(&positionEnnemis,&positionHero, 3) == 1 || collision(&positionEnnemis,&positionHero, 1) == 1 || collision(&positionEnnemis,&positionHero, 2) == 1 || collision(&positionEnnemis,&positionHero, 4) == 1){
                        for (em=0; em<4; em++){ // On fais une boucle.
                            switch (variableSensEnnemi){ // En fonction du sens de l'ennemi, on positione l'image diff�rement.
                                case 0 :
                                    positionArmeE.x = (positionEnnemis.x-15);
                                    positionArmeE.y = (positionEnnemis.y-10);
                                    break;
                                case 1 :
                                    positionArmeE.x = (positionEnnemis.x-15);
                                    positionArmeE.y = (positionEnnemis.y-10);
                                    break;

                                case 2 :
                                    positionArmeE.x = (positionEnnemis.x-15);
                                    positionArmeE.y = (positionEnnemis.y-10);
                                    break;

                                case 3 :
                                    positionArmeE.x = (positionEnnemis.x-15);
                                    positionArmeE.y = (positionEnnemis.y-10);
                                    break;
                                }
                        nouveauSensArmeEnnemi = armeSensEnnemie[variableSensEnnemi][em]; // On d�place le rectange d'afffichage dans l'image spriteVent.
                        SDL_SetColorKey(imageArmeE, SDL_SRCCOLORKEY, SDL_MapRGB(imageArmeE->format, 0, 0, 255)); // On met en transparence le bleu.
                        SDL_BlitSurface(imageArmeE, &nouveauSensArmeEnnemi, ecran, &positionArmeE);
                        SDL_Flip(ecran); // Rafraichissement de l'�cran.
                        SDL_Delay(15); // Pause de 15ms.
                        }
                    em = 0;
                    positionArmeE.x = 1500; // Suppression de l'arme en la sortant de l'ecran.
                    positionArmeE.y = 1500;
                    ennemi.attaquer(bread);
                }
            }

        switch(event.type)
        {
            case SDL_QUIT: // Si on clique sur la croix.
                vraie = 0; // On sort de la boucle.
                break;
            case SDL_KEYDOWN:
                switch(event.key.keysym.sym)
                {
                    case SDLK_ESCAPE:
                        vraie = 0;
                        break;
                    case SDLK_SPACE:
                        // Gestion des mouvements de l'armes.
                        if (tempsActuel - tempsPrecedent > 300){ // On met un timer pour ralentir le temps entre 2 mouvements.
                            tempsPrecedent = tempsActuel;
                            for (im=0; im<4; im++){ // On fais une boucle.
                                switch (variableSensHeroe){ // On fonction du sens du heroe on position l'image diff�rement.
                                    case 0 :
                                        positionArme.x = (positionHero.x-15);
                                        positionArme.y = (positionHero.y-10);
                                        break;
                                    case 1 :
                                        positionArme.x = (positionHero.x-15);
                                        positionArme.y = (positionHero.y-10);
                                        break;
                                    case 2 :
                                        positionArme.x = (positionHero.x-15);
                                        positionArme.y = (positionHero.y-10);
                                        break;
                                    case 3 :
                                        positionArme.x = (positionHero.x-15);
                                        positionArme.y = (positionHero.y-10);
                                        break;
                                    }
                                nouveauSensArme = armeSens[variableSensHeroe][im]; // On d�place le rectange d'afffichage dans l'image spriteVent.
                                SDL_SetColorKey(imageArme, SDL_SRCCOLORKEY, SDL_MapRGB(imageArme->format, 0, 0, 255)); // On met en transparence le bleu.
                                SDL_BlitSurface(imageArme, &nouveauSensArme, ecran, &positionArme);
                                SDL_BlitSurface(imageArmeE, &nouveauSensArmeEnnemi, ecran, &positionArmeE);
                                SDL_Flip(ecran); // On rafra�chit l'�cran.
                                SDL_Delay(15); // On fais une pause de 15ms.
                                }
                            im = 0;
                            positionArme.x = 1500; // On efface l'arme en la mettant en dehors de l'�cran.
                            positionArme.y = 1500;
                            }

                        if (tempsActuel-tempsPrecedent3 >200){
                            tempsPrecedent3 = tempsActuel;
                            if(collision(&positionHero, &positionEnnemis, 1)){
                                if(variableSensHeroe == 0){
                                    bread.attaquer(ennemi);
                                }
                            }
                            else if(collision(&positionHero, &positionEnnemis, 2)){
                                if(variableSensHeroe == 1){
                                    bread.attaquer(ennemi);
                                }
                            }
                            else if(collision(&positionHero, &positionEnnemis, 3)){
                                if(variableSensHeroe == 2){
                                    bread.attaquer(ennemi);
                                }
                            }
                            else if(collision(&positionHero, &positionEnnemis, 4)){
                                if(variableSensHeroe == 3){
                                    bread.attaquer(ennemi);
                                }
                            }
                        }
                        default:
                        break;
                    }

        }

        SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 0, 140, 0)); // On met le fond de la fenetre en vert

        for (i = 0 ; i < NB_BLOCS_LARGEUR ; i++) // Boucle pour charger les diff�rente image en fonction du tableau 'carte'.
        {
            for (j = 0 ; j < NB_BLOCS_HAUTEUR ; j++)
            {
                position.x = i* TAILLE_BLOC;
                position.y = j* TAILLE_BLOC;

                switch(carte[i][j])
                {
                    case 1:
                        SDL_SetColorKey(mur, SDL_SRCCOLORKEY, SDL_MapRGB(mur->format, 0, 0, 255)); // On met en transparence le bleu.
                        SDL_BlitSurface(mur, NULL, ecran, &position); // On charge un rocher.
                        break;
                    case 3:
                        SDL_SetColorKey(feuille_image, SDL_SRCCOLORKEY, SDL_MapRGB(feuille_image->format, 0, 0, 255)); // On met en transparence le bleu.
                        SDL_BlitSurface(feuille_image, &nouvelleFeuilleFrame, ecran, &position); // On charge l'image d'une feuille.
                        break;
                    case 4:
                        SDL_SetColorKey(arbre, SDL_SRCCOLORKEY, SDL_MapRGB(arbre->format, 0, 0, 255)); // On met en transparence le bleu.
                        SDL_BlitSurface(arbre, NULL, ecran, &position); // On charge l'image d'un arbre.
                        break;
                    default:
                        break;
                }
                if(ennemi.enVie() == 0){
                ennemi.setVie(100);
                score+=1;
                xaleatoire = aleatoire2()*TAILLE_BLOC;
                yaleatoire = aleatoire3()*TAILLE_BLOC;
                xcaleatoire = aleatoire4()*TAILLE_BLOC;
                ycaleatoire = aleatoire5()*TAILLE_BLOC;
                while(carte[xaleatoire/TAILLE_BLOC][yaleatoire/TAILLE_BLOC] == 1 || carte[xaleatoire/TAILLE_BLOC][yaleatoire/TAILLE_BLOC] == 4){
                    xaleatoire = aleatoire2()*TAILLE_BLOC;
                    yaleatoire = aleatoire3()*TAILLE_BLOC;
                }
                positionEnnemis.x = xaleatoire;
                positionEnnemis.y = yaleatoire;

                while(carte[xcaleatoire/TAILLE_BLOC][ycaleatoire/TAILLE_BLOC] == 1 || carte[xcaleatoire/TAILLE_BLOC][ycaleatoire/TAILLE_BLOC] == 4){
                    xcaleatoire = aleatoire4()*TAILLE_BLOC;
                    ycaleatoire = aleatoire5()*TAILLE_BLOC;
                }
                positionCoeur.x = xcaleatoire;
                positionCoeur.y = ycaleatoire;
                }
                if(positionCoeur.x/TAILLE_BLOC == positionHero.x/TAILLE_BLOC && positionCoeur.y/TAILLE_BLOC == positionHero.y/TAILLE_BLOC){
                    bread.coeur();
                    positionCoeur.x = 2000;
                    positionCoeur.y = 2000;
                }
                if(bread.enVie() == 0){
                    meilleur = lectureScore();
                    if (score > meilleur){
                        ecritureScore(score);
                        meilleur = score;
                    }
                    sprintf(perdue, "Score : %d", score);
                    sprintf(hs, "Meilleur Score : %d", meilleur);
                    positionTexte.x = 8*TAILLE_BLOC;
                    positionTexte.y = 7*TAILLE_BLOC;
                    positionTexte2.x = 5*TAILLE_BLOC;
                    positionTexte2.y = 4*TAILLE_BLOC;
                    positionTexte3.x = 5*TAILLE_BLOC;
                    positionTexte3.y = 10*TAILLE_BLOC;
                    positionHero.x = 1500;
                    positionHero.y = 1500;
                    positionEnnemis.x = 1500;
                    positionEnnemis.y = 1500;
                    if (tempsActuel-tempsPrecedent6 >1000){
                        tempsPrecedent6 = tempsActuel;
                        textefin = TTF_RenderText_Blended(police, perdue, blanc);
                        textefin2 = TTF_RenderText_Blended(police, "Vous avez perdu.", blanc);
                        textefin3 = TTF_RenderText_Blended(police, hs, blanc);
                    }
                }
            }
        }

        // Affichage des images.
        SDL_SetColorKey(imageHeroe, SDL_SRCCOLORKEY, SDL_MapRGB(imageHeroe->format, 0, 0, 255)); // On met en transparence le bleu.
        SDL_BlitSurface(imageHeroe, &nouveauSensHeroe, ecran, &positionHero); // On affiche le heroe.
        SDL_SetColorKey(imageEnnemi, SDL_SRCCOLORKEY, SDL_MapRGB(imageEnnemi->format, 0, 0, 255)); // On met en transparence le bleu.
        SDL_BlitSurface(imageEnnemi, &nouveauSensEnnemi, ecran, &positionEnnemis); // On affiche l'ennemie.
        SDL_SetColorKey(imageArme, SDL_SRCCOLORKEY, SDL_MapRGB(imageArme->format, 0, 0, 255)); // On met en transparence le bleu.
        SDL_BlitSurface(imageArme, &nouveauSensArme, ecran, &positionArme); // On affiche l'ennemie.
        SDL_BlitSurface(imageArmeE, &nouveauSensArmeEnnemi, ecran, &positionArmeE); // On affiche l'ennemie.
        SDL_SetColorKey(imageArmeE, SDL_SRCCOLORKEY, SDL_MapRGB(imageArmeE->format, 0, 0, 255));
        SDL_BlitSurface(jaugeVieImage, &jaugeDeVieEnnemiValeur, ecran, &jaugeDeVieEnnemiPosition);
        SDL_BlitSurface(jaugeVieImage, &jaugeDeVieHeroeValeur, ecran, &jaugeDeVieHeroePosition);
        SDL_SetColorKey(coeur, SDL_SRCCOLORKEY, SDL_MapRGB(coeur->format, 0, 0, 255)); // On met en transparence le bleu.
        SDL_BlitSurface(coeur, NULL, ecran, &positionCoeur);
        SDL_BlitSurface(textefin, NULL, ecran, &positionTexte);
        SDL_BlitSurface(textefin2, NULL, ecran, &positionTexte2);
        SDL_BlitSurface(textefin3, NULL, ecran, &positionTexte3);

        SDL_Flip(ecran); // Rafra�chissement de l'�cran.
        }

    SDL_EnableKeyRepeat(0,0);

    // Lib�ration des surfaces charg�es.
    SDL_FreeSurface(mur);
    SDL_FreeSurface(arbre);
    SDL_FreeSurface(feuille_image);
    SDL_FreeSurface(imageEnnemi);
    SDL_FreeSurface(imageHeroe);
    SDL_FreeSurface(textefin2);
    SDL_FreeSurface(textefin);
    SDL_FreeSurface(coeur);


    TTF_CloseFont(police);
    TTF_Quit();
    SDL_Quit();
    return EXIT_SUCCESS;
}
