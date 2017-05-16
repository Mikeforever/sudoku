#ifndef INTERFACE
#define INTERFACE

#include "constantes.h"

void chercherSolution(int grille[][TAILLE_TABLEAU], int grilleOrigine[][TAILLE_TABLEAU], SDL_Surface *ecran, SDL_Surface *texte, TTF_Font *police, int *nbEssais, int *tempsAffichage);
void recherchePremierNeutre(int *i, int *j, int grille[][TAILLE_TABLEAU]);
int validationGrille(int grille[][TAILLE_TABLEAU]);
int validationValeurGrille(int grille[][TAILLE_TABLEAU], int i, int j, int valeur);
void affichage(int grille[][TAILLE_TABLEAU], int grilleOrigine[][TAILLE_TABLEAU], SDL_Surface *ecran, SDL_Surface *texte, TTF_Font *police, int iChoix, int jChoix, int mode[], int *nbEssais, int *tempsAffichage);
void affichageEcranAccueil();
void modeEdition(int grille[][TAILLE_TABLEAU], int grilleSolution[][TAILLE_TABLEAU], SDL_Surface *ecran, SDL_Surface *texte, TTF_Font *police, int *nbEssais, int *tempsAffichage);

#endif // INTERFACE
