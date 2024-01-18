#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "dico.h"
int piocherMot(char *motPioche)
{
    FILE *dico = NULL; // Le pointeur de fichier qui va contenir notre fichier
    int nombreMots = 0, numMotChoisi = 0, i = 0;
    int caractereLu = 0;
    dico = fopen("dictionnaire.txt", "r"); // On ouvre le dictionnaire en lecture seule
    // On vérifie si on a réussi à ouvrir le dictionnaire
    if (dico == NULL) // Si on n'a PAS réussi à ouvrir le fichier
    {
        printf("\nImpossible de charger le dictionnaire de mots");
        return 0; // On retourne 0 pour indiquer que la fonction a échoué
        // À la lecture du return, la fonction s'arrête immédiatement.
    }
    // On compte le nombre de mots dans le fichier (il suffit de compter les
    // entrées \n
    do
    {
        caractereLu = fgetc(dico);
        if (caractereLu == '\n')
            nombreMots++;
    } while (caractereLu != EOF);
    numMotChoisi = nombreAleatoire(nombreMots); // On pioche un mot au hasard                                          // On recommence à lire le fichier depuis le début. On s'arrête lorsqu'on est arrivé au bon mot
    printf("\n le num choisi est %d: \n", numMotChoisi);
    rewind(dico);
    while (numMotChoisi > 0)
    {
        caractereLu = fgetc(dico);
        if (caractereLu == '\n')
            numMotChoisi--;
    }
    /* Le curseur du fichier est positionné au bon endroit.
    On n'a plus qu'à faire un fgets qui lira la ligne */
    fgets(motPioche, 100, dico);
    printf("\n le mot pioche est %s: \n", motPioche);

    // On vire le \n à la fin
    motPioche[strlen(motPioche) - 1] = '\0';
    printf("\n le mot pioche est apres trans %s: \n", motPioche);

    fclose(dico);
    return 1; // Tout s'est bien passé, on retourne 1
}

int nombreAleatoire(int nombreMax)
{
    srand(time(NULL));
    return (rand() % nombreMax);
}

void creerDictionnaire(ArbreBin **dictionnaire, char ***motArray, int *motCount)
{
    FILE *dico = fopen("dictionnaire.txt", "r");
    if (dico == NULL)
    {
        printf("\nImpossible de charger le dictionnaire de mots");
        return;
    }

    char mot[100];

    // Count the number of words in the file
    *motCount = 0;
    while (fgets(mot, sizeof(mot), dico) != NULL)
    {
        (*motCount)++;
    }

    // Allocate memory for the dynamic array
    *motArray = (char **)malloc(*motCount * sizeof(char *));
    if (*motArray == NULL)
    {
        printf("\nMemory allocation error");
        fclose(dico);
        return;
    }

    // Rewind the file to the beginning
    rewind(dico);

    // Read each word from the file and insert it into the tree and array
    for (int i = 0; i < *motCount; i++)
    {
        (*motArray)[i] = (char *)malloc(100 * sizeof(char)); // Assuming the maximum word length is 100
        if ((*motArray)[i] == NULL)
        {
            printf("\nMemory allocation error");
            fclose(dico);

            // Free the allocated memory before returning
            for (int j = 0; j < i; j++)
            {
                free((*motArray)[j]);
            }
            free(*motArray);

            return;
        }

        fgets((*motArray)[i], 100, dico);

        // Remove newline character at the end
        (*motArray)[i][strcspn((*motArray)[i], "\n")] = '\0';

        // Insert the word into the dictionary tree
        dicoInsererMot((*motArray)[i], dictionnaire, NULL);
    }

    fclose(dico);
}
void dicoInsererMot(char mot[], ArbreBin **arbre, QueueNode **queue)
{
    if (*arbre != NULL)
    /*si l'arbre n'est pas vide*/
    {
        if (mot[0] != '\0')
        /*on teste si la premiemre valeur egale au premier char de mot*/
        {
            if ((*arbre)->val == mot[0])
            {
                /*si egale Incrémente la position du pointeur dans la chaîne de caractères mot. */
                mot++;

                /*et fait l'appelle recursive du fonction sur la fils gauche*/
                dicoInsererMot(mot, &((*arbre)->FG), queue);
            }
            else
            {
                /*si l'arbre a un fils droite on cherche le char*/
                if ((*arbre)->FD != NULL)
                {
                    /*on fait l'appel recursive de la fonction sur la fils droite*/
                    dicoInsererMot(mot, &((*arbre)->FD), queue);
                }
                else
                { /*si l'arbre vide on fait l'app au fonction arbreConNoeud pour on instialise l'arbre*/
                    (*arbre)->FD = arbreConNoeud(mot[0], NULL, NULL);
                    dicoInsererMot(mot, &(*arbre), queue); /*et on fait l app recursive au fonction pour isererer d'autre char */
                }
            }
        }
        /*si le mot n'est pas inserer dans l'arbre on fait l'appel au fonction arbreConNoeud  pour insialiser une mot dans une arbre*/
        else if ((*arbre)->val != '\0' && mot[0] == '\0')
        {
            ArbreBin *a = arbreConNoeud('\0', NULL, *arbre);
            *arbre = a;
        }
    }
    else
    {
        if (mot[0] != '\0')
        /*si toute le mot n'est pas  inserer */
        { /*on fait l'appel recursiv sur la fils gauche pour inserer les autres char*/
            *arbre = arbreConNoeud(mot[0], NULL, NULL);
            mot++;
            dicoInsererMot(mot, &((*arbre)->FG), queue);
        }
        /*sinon on insere /0 donc on a inserer tout les chars*/
        else
        {
            *arbre = arbreConNoeud('\0', NULL, NULL);
        }
    }
}