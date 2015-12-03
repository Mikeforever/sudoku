#ifndef CONSTANTES
#define CONSTANTES

#include <stdio.h>
#include <stdlib.h>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

#define TAILLE_TABLEAU 9
#define TAILLE_CARRE 3
#define TAILLE_POLICE 30
#define NOM_FICHIER "sudoku.txt"
#define NOM_FICHIER_RESULTAT "resultat.txt"
#define NOM_POLICE "arial.ttf"
#define NEUTRE 'X'
#define TAILLE_LARGEUR 33
#define TAILLE_HAUTEUR 35
#define TAILLE_BORDURE 1
#define TAILLE_BORDURE_LIMITE 2
#define TAILLE_SUDOKU_LARGEUR TAILLE_LARGEUR*9 + TAILLE_BORDURE*10 + TAILLE_BORDURE_LIMITE * 2
#define TAILLE_SUDOKU_HAUTEUR TAILLE_HAUTEUR*10 + TAILLE_BORDURE*10 + TAILLE_BORDURE_LIMITE * 2
#define TEMPS_AFFICHAGE 15
#define TEXTE_ACCUEIL1 "1 : Lancer solution"
#define TEXTE_ACCUEIL2 "2 : Lancer éditeur"

#endif // CONSTANTES
