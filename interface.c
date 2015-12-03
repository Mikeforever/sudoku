#include "interface.h"

void chercherSolution(int grille[][TAILLE_TABLEAU], int grilleOrigine[][TAILLE_TABLEAU], SDL_Surface *ecran, SDL_Surface *texte, TTF_Font *police, int *nbEssais)
{
    int iNeutre = 0, jNeutre = 0, valeurSuivante = 1;

    // On parcourt le tableau, on repère le premier X
    // On vérifie une valeur possible
    if (!validationGrille(grille))
    {
        // Recherche de la première case vide
        recherchePremierNeutre(&iNeutre, &jNeutre, grille);

        // Pour chaque chiffre possible, il est nécessaire de vérifier s'il est bon avant de le mettre dans la grille
        while ((!validationGrille(grille)) && (valeurSuivante < 10))
        {
            // En cas de succès, on met cette valeur et on itère sur la grille
            grille[iNeutre][jNeutre] = valeurSuivante;

            // Affichage de la grille
            affichage(grille, grilleOrigine, ecran, texte, police, iNeutre, jNeutre, "En cours", nbEssais);
            (*nbEssais)++;

            // Suppression de la valeur de la case pour le moment
            grille[iNeutre][jNeutre] = NEUTRE;

            // Vérification de la possibilité de mettre cette valeur
            if (validationValeurGrille(grille, iNeutre, jNeutre, valeurSuivante))
            {
                // On met la valeur pour la boucle
                grille[iNeutre][jNeutre] = valeurSuivante;

                // Nouvelle récursion sur la case suivante
                chercherSolution(grille, grilleOrigine, ecran, texte, police, nbEssais);
            }

            // Etant ressorti de la boucle, valeur suivante
            valeurSuivante++;
        }
    }

    // Si la solution n'est pas atteinte ou on a une valeur incorrecte, on supprime la valeur de la case
    if (!validationGrille(grille))
        grille[iNeutre][jNeutre] = NEUTRE;
}

void affichageEcranAccueil(SDL_Surface *ecran, SDL_Surface *texte)
{
    TTF_Font *police = NULL;
    SDL_Color couleurNoire = {0, 0, 0};
    SDL_Color couleurBlanche = {255, 255, 255};
    SDL_Color couleurRouge = {255, 0, 0};
    SDL_Color couleurTexte = {0, 0, 0};
    SDL_Color couleurBleu = {0, 0, 255};
    SDL_Rect position;
    int i,j;

    police = TTF_OpenFont(NOM_POLICE, 20);

    SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 0, 0, 0));

    texte = TTF_RenderText_Shaded(police, "SUDOKU", couleurBlanche, couleurNoire);
    position.y = TAILLE_HAUTEUR;
    position.x = ecran->w/2 - texte->w/2;
    SDL_BlitSurface(texte, NULL, ecran, &position);

    texte = TTF_RenderText_Shaded(police, TEXTE_ACCUEIL1, couleurBlanche, couleurNoire);
    position.y = ecran->h / 2 - TAILLE_HAUTEUR;
    position.x = ecran->w/2 - texte->w/2;
    SDL_BlitSurface(texte, NULL, ecran, &position);

    texte = TTF_RenderText_Shaded(police, TEXTE_ACCUEIL2, couleurBlanche, couleurNoire);
    position.y = ecran->h/2 + TAILLE_HAUTEUR;
    position.x = ecran->w/2 - texte->w/2;
    SDL_BlitSurface(texte, NULL, ecran, &position);

    SDL_Flip(ecran);

    TTF_CloseFont(police);
}

void affichage(int grille[][TAILLE_TABLEAU], int grilleOrigine[][TAILLE_TABLEAU], SDL_Surface *ecran, SDL_Surface *texte, TTF_Font *police, int iChoix, int jChoix, int mode[], int *nbEssais)
{

    SDL_Color couleurNoire = {0, 0, 0};
    SDL_Color couleurBlanche = {255, 255, 255};
    SDL_Color couleurRouge = {255, 0, 0};
    SDL_Color couleurBleu = {0, 0, 255};
    SDL_Color couleurTexte = couleurNoire;
    SDL_Color couleurFond = couleurBlanche;
    SDL_Event event;
    TTF_Font *petitePolice = NULL;
    char txt[] = " 0 ";
    char nbEssaisTxt[20] = {0};
    SDL_Rect position;
    int i,j;
    int tempsActuel = 0, tempsPrecedent = 0;
    int continuer = 1;

    SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 0, 0, 0));

    // Gestion du temps
    tempsPrecedent = SDL_GetTicks();
    while (continuer)
    {
        SDL_PollEvent(&event); /* On utilise PollEvent et non WaitEvent pour ne pas bloquer le programme */
        switch(event.type)
        {
            case SDL_QUIT:
                continuer = 0;
                break;
        }

        tempsActuel = SDL_GetTicks();
        if (tempsActuel - tempsPrecedent > TEMPS_AFFICHAGE) /* Si TEMPS_AFFICHAGE ms se sont écoulées depuis le dernier tour de boucle */
        {
            continuer = 0;
            tempsPrecedent = tempsActuel; /* Le temps "actuel" devient le temps "precedent" pour nos futurs calculs */
        }
        else /* Si ça fait moins de TEMPS_AFFICHAGE ms depuis le dernier tour de boucle, on endort le programme le temps qu'il faut */
        {
           SDL_Delay(TEMPS_AFFICHAGE - (tempsActuel - tempsPrecedent));
        }
    }


    for (i=0;i<TAILLE_TABLEAU;i++)
    {
        for (j=0;j<TAILLE_TABLEAU;j++)
        {
            if ((i == iChoix) && (j == jChoix))
                couleurFond = couleurRouge;
            else
                couleurFond = couleurBlanche;

            if (grille[i][j] == NEUTRE)
            {
                txt[1] = '?';
                couleurTexte = couleurFond;
            }
            else
            {
                sprintf(txt, " %d " , grille[i][j]);

                // Couleur du texte en fonction de l'origine
                if (grilleOrigine[i][j] == NEUTRE)
                    couleurTexte = couleurNoire;
                else
                    couleurTexte = couleurBleu;
            }

            texte = TTF_RenderText_Shaded(police, txt, couleurTexte, couleurFond);

            // Calcul de la position et on lie l'image
            position.x = j*TAILLE_LARGEUR + (j+1) * TAILLE_BORDURE + j/3*TAILLE_BORDURE_LIMITE;
            position.y = i*TAILLE_HAUTEUR + (i+1) * TAILLE_BORDURE + i/3*TAILLE_BORDURE_LIMITE;
            SDL_BlitSurface(texte, NULL, ecran, &position);

            SDL_FreeSurface(texte);
        }
    }

    // Ajout de la phrase du bas de la grille
    texte = TTF_RenderText_Shaded(police, mode, couleurBlanche, couleurNoire);
    position.y = TAILLE_TABLEAU*TAILLE_HAUTEUR + (TAILLE_TABLEAU+1) * TAILLE_BORDURE + TAILLE_TABLEAU/3*TAILLE_BORDURE_LIMITE;
    position.x = ecran->w/2 - texte->w/2 - TAILLE_BORDURE;
    SDL_BlitSurface(texte, NULL, ecran, &position);

    SDL_FreeSurface(texte);

    // Affichage compteur si le compteur n'est pas à 0
    if (*nbEssais != 0)
    {
        petitePolice = TTF_OpenFont(NOM_POLICE, 10);
        sprintf(nbEssaisTxt, "%d", *nbEssais);
        texte = TTF_RenderText_Shaded(petitePolice, nbEssaisTxt, couleurBlanche, couleurNoire);
        position.y = TAILLE_SUDOKU_HAUTEUR - texte->h - TAILLE_BORDURE;
        position.x = TAILLE_SUDOKU_LARGEUR - texte->w - TAILLE_BORDURE;
        SDL_BlitSurface(texte, NULL, ecran, &position);

        SDL_FreeSurface(texte);
        TTF_CloseFont(petitePolice);
    }


    SDL_Flip(ecran);
}

int validationValeurGrille(int grille[][TAILLE_TABLEAU], int iValeur, int jValeur, int valeur)
{
    // On vérifie sur les longueurs
    int n;
    int resultat = 1;

    for (n=0;n<TAILLE_TABLEAU;n++)
    {
        // Vérification en ligne
        if ((grille[iValeur][n] == valeur) && (n != jValeur))
        {
            resultat = 0;
        }

        // Vérification en colonne
        if ((grille[n][jValeur] == valeur) && (n != iValeur))
        {
            resultat = 0;
        }

        // On vérifie dans le carré où est la valeur
        if ((grille[(iValeur/3)*3+n/3][(jValeur/3)*3+n%3] == valeur) && (iValeur != ((iValeur/3)*3+n/3)) && (jValeur != ((jValeur/3)*3+n%3)))
        {
            resultat = 0;
        }
    }

    return resultat;
}

int validationGrille(int grille[][TAILLE_TABLEAU])
{
    int i,j;
    int resultat = 1;

    for (i=0;i<TAILLE_TABLEAU;i++)
    {
        for (j=0;j<TAILLE_TABLEAU;j++)
        {
            if (grille[i][j] == NEUTRE)
                resultat = 0;
        }
    }

    return resultat;
}

void recherchePremierNeutre(int *i, int *j, int grille[][TAILLE_TABLEAU])
{
    // Parcours du tableau
    while (grille[*i][*j] != NEUTRE)
    {
        (*j)++;
        if (*j == TAILLE_TABLEAU)
        {
            *j = 0;
            (*i)++;
        }
    }
}

void modeEdition(int grille[][TAILLE_TABLEAU], int grilleSolution[][TAILLE_TABLEAU], SDL_Surface *ecran, SDL_Surface *texte, TTF_Font *police, int *nbEssais)
{
    int iChoix = -1, jChoix = -1, continuer = 1;
    SDL_Event event;

    while (continuer)
    {
        // Affichage de la grille de base
        affichage(grille, grilleSolution, ecran, texte, police, iChoix, jChoix, "Mode Edition", nbEssais);

        SDL_WaitEvent(&event);
        switch(event.type)
        {
            case SDL_QUIT: // Clic sur la croix rouge, on ferme le programme
                continuer = 0;
                break;
            case SDL_MOUSEBUTTONDOWN:
                jChoix = event.button.x/(TAILLE_LARGEUR + TAILLE_BORDURE);
                iChoix = event.button.y/(TAILLE_HAUTEUR + TAILLE_BORDURE);
                break;
            case SDL_KEYDOWN:
                switch (event.key.keysym.sym)
                {
                    case SDLK_ESCAPE: /* Appui sur la touche Echap, on se désengage de la case */
                        iChoix = -1;
                        jChoix = -1;
                        break;
                    case SDLK_RETURN:
                        continuer = 0;
                        break;
                    case SDLK_1:
                        if ((iChoix != -1) && (jChoix != -1))
                        {
                            grille[iChoix][jChoix] = 1;
                            iChoix = -1;
                            jChoix = -1;
                        }
                        break;
                    case SDLK_2:
                        if ((iChoix != -1) && (jChoix != -1))
                        {
                            grille[iChoix][jChoix] = 2;
                            iChoix = -1;
                            jChoix = -1;
                        }
                        break;
                    case SDLK_3:
                        if ((iChoix != -1) && (jChoix != -1))
                        {
                            grille[iChoix][jChoix] = 3;
                            iChoix = -1;
                            jChoix = -1;
                        }
                        break;
                    case SDLK_4:
                        if ((iChoix != -1) && (jChoix != -1))
                        {
                            grille[iChoix][jChoix] = 4;
                            iChoix = -1;
                            jChoix = -1;
                        }
                        break;
                    case SDLK_5:
                        if ((iChoix != -1) && (jChoix != -1))
                        {
                            grille[iChoix][jChoix] = 5;
                            iChoix = -1;
                            jChoix = -1;
                        }
                        break;
                    case SDLK_6:
                        if ((iChoix != -1) && (jChoix != -1))
                        {
                            grille[iChoix][jChoix] = 6;
                            iChoix = -1;
                            jChoix = -1;
                        }
                        break;
                    case SDLK_7:
                        if ((iChoix != -1) && (jChoix != -1))
                        {
                            grille[iChoix][jChoix] = 7;
                            iChoix = -1;
                            jChoix = -1;
                        }
                        break;
                    case SDLK_8:
                        if ((iChoix != -1) && (jChoix != -1))
                        {
                            grille[iChoix][jChoix] = 8;
                            iChoix = -1;
                            jChoix = -1;
                        }
                        break;
                    case SDLK_9:
                        if ((iChoix != -1) && (jChoix != -1))
                        {
                            grille[iChoix][jChoix] = 9;
                            iChoix = -1;
                            jChoix = -1;
                        }
                        break;
                    case SDLK_DELETE:
                        if ((iChoix != -1) && (jChoix != -1))
                        {
                            grille[iChoix][jChoix] = NEUTRE;
                        }
                        break;
                }
                break;
        }
    }

    // Enregistrement de la grille
    stockageSolution(grille, NOM_FICHIER);
}
