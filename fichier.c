#include "fichier.h"

void remplissageGrille(int grille[][TAILLE_TABLEAU])
{
    FILE* fichier = NULL;
    int caractereActuel = 0;
    int i = 0, j = 0;

    // Ouverture du fichier
    fichier = fopen(NOM_FICHIER, "r");
    if (fichier != NULL)
    {
        // Parcours du fichier
        do
        {
            caractereActuel = fgetc(fichier);

            // Si on a un saut de ligne, on change de ligne dans le tableau
            if ((caractereActuel != '\n') && (caractereActuel != EOF))
            {
                if (caractereActuel == NEUTRE)
                    grille[i][j] = NEUTRE;
                else
                    grille[i][j] = caractereActuel - '0'; // On positionne les vraies valeurs plutôt que le caractère, plus facile pour incrémenter

                j++;
            }
            else
            {
                j = 0;
                i++;
            }

        } while (caractereActuel != EOF);
    }

    // Fermeture du fichier
    fclose(fichier);
}

void remplissageGrilleNeutre(int grille[][TAILLE_TABLEAU])
{
    int i,j;

    for (i=0;i<TAILLE_TABLEAU;i++)
    {
        for (j=0;j<TAILLE_TABLEAU;j++)
        {
            grille[i][j] = NEUTRE;
        }
    }
}

void stockageSolution(int grille[][TAILLE_TABLEAU], int nomFichier[])
{
    FILE* fichier = NULL;
    int i,j;

    fichier = fopen(nomFichier, "w");

    if (fichier != NULL)
    {
        for (i=0;i<TAILLE_TABLEAU;i++)
        {
            for (j=0;j<TAILLE_TABLEAU;j++)
            {
                if (grille[i][j] == NEUTRE)
                    fputc(NEUTRE, fichier);
                else
                    fputc(grille[i][j] + '0', fichier);
            }
            fputc('\n', fichier);
        }

        // Fermeture du fichier
        fclose(fichier);
    }
}
