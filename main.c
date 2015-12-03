#include "constantes.h"
#include "fichier.h"

int main(int argc, char* argv[])
{
    // Initialisation des variables
    int grille[TAILLE_TABLEAU][TAILLE_TABLEAU] = {0};
    int grilleSolution[TAILLE_TABLEAU][TAILLE_TABLEAU] = {0};
    SDL_Event event;
    int continuer = 1;
    int choix = 0;
    int nbEssais = 0;

    // Initialisation du mode vid�o
    SDL_Surface *ecran = NULL, *texte = NULL;
    TTF_Font *police = NULL;

    if (SDL_Init(SDL_INIT_VIDEO) == -1) // D�marrage de la SDL. Si erreur :
    {
        fprintf(stderr, "Erreur d'initialisation de la SDL : %s\n", SDL_GetError()); // �criture de l'erreur
        exit(EXIT_FAILURE); // On quitte le programme
    }

    // Mise en place de l'ic�ne
    SDL_WM_SetIcon(IMG_Load("sudoku.png"), NULL);

    TTF_Init();

    ecran = SDL_SetVideoMode(TAILLE_SUDOKU_LARGEUR, TAILLE_SUDOKU_HAUTEUR, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);
    SDL_WM_SetCaption("Sudoku en solution", NULL);

    police = TTF_OpenFont(NOM_POLICE, TAILLE_POLICE);



    while (continuer)
    {
        // Affichage de la page d'accueil
        affichageEcranAccueil(ecran, texte);

        choix = 0;
        SDL_WaitEvent(&event);
        switch(event.type)
        {
            case SDL_QUIT: // Clic sur la croix rouge, on ferme le programme
                continuer = 0;
                break;
            case SDL_KEYDOWN:
                switch (event.key.keysym.sym)
                {
                    case SDLK_ESCAPE: /* Appui sur la touche Echap, on arr�te le programme */
                        continuer = 0;
                        break;
                    case SDLK_1: // Choix 1 : on lance le jeu
                        choix = 1;
                        break;
                    case SDLK_2: // Choix 2 : on lance l'�diteur
                        choix = 2;
                        break;
                }
                break;
        }

        // Choix 1 : lancement de la r�solution
        if (choix == 1)
        {
            // R�cup�ration de la grille dans un fichier
            remplissageGrille(grille);
            remplissageGrille(grilleSolution);
            nbEssais = 0;

            // Lancement de la recherche de la solution
            chercherSolution(grilleSolution, grille, ecran, texte, police, &nbEssais);

            // Affichage final
            if (validationGrille(grilleSolution))
            {
                affichage(grilleSolution, grille, ecran, texte, police, -1, -1, "R�sultat trouv�", &nbEssais);

                // Stockage du r�sultat dans un fichier de r�sultat
                stockageSolution(grilleSolution, NOM_FICHIER_RESULTAT);
            }
            else
            {
                affichage(grilleSolution, grille, ecran, texte, police, -1, -1, "Pas de r�sultat", &nbEssais);
            }

            // Pause pour l'affichage du r�sultat
            while (continuer)
            {
                SDL_WaitEvent(&event);
                switch(event.type)
                {
                    case SDL_QUIT: // Clic sur la croix rouge, on ferme le programme
                        continuer = 0;
                        break;
                    case SDL_KEYDOWN:
                        switch (event.key.keysym.sym)
                        {
                            case SDLK_ESCAPE: /* Appui sur la touche Echap, on arr�te le programme */
                            case SDLK_RETURN:
                                continuer = 0;
                                break;
                        }
                        break;
                }
            }

            continuer = 1;
        }
        // Choix 2 : lancement du mode �diteur
        else if (choix == 2)
        {
            // Chargement de la partie Editeur de la solution
            remplissageGrilleNeutre(grille);
            remplissageGrilleNeutre(grilleSolution);
            nbEssais = 0;

            modeEdition(grille, grilleSolution, ecran, texte, police, &nbEssais);
        }
    }

    // Fermeture propre de ce qui a �t� ouvert
    TTF_CloseFont(police);
    TTF_Quit();

    SDL_FreeSurface(texte);
    SDL_Quit();

    return EXIT_SUCCESS;
}
