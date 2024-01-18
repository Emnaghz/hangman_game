#include <stdio.h>
#include <math.h>
#include <stdbool.h>
#include <string.h>
#include "listes.h"
#include "arbres.h"
#include "dico.c"
#include <stdlib.h>
ArbreBin *exempleArbre()
{
    // 0              a
    // 1         c           t
    // 2      a    j    s     x
    ArbreBin *A;
    A = initArbreBin();
    A = creerFeuille('a');
    A->FG = creerFeuille('c');
    A->FD = creerFeuille('t');
    A->FD->FG = creerFeuille('t');
    A->FD->FD = creerFeuille('e');
    A->FG->FD = creerFeuille('f');
    A->FG->FG = creerFeuille('\0');

    return A;
}

char *motAleatoire(char **motArray, int motCount)
{
    if (motCount <= 0 || motArray == NULL)
    {
        // Invalid input or empty array
        return NULL;
    }
    srand(time(NULL));
    // Generate a random index
    int randomIndex = rand() % motCount;
    //printf("%d", randomIndex);

    // Return the word at the random index
    return motArray[randomIndex];
}

void arbres()
{
    ArbreBin *A = exempleArbre();
    QueueNode *queue = NULL;
    generateMermaidScript(A);

    // Liste *L=initListe();

    // ArbreBin *dictionnaire = genererABR();
    // ArbreBin *P=rechercheRecurABR(A,'j',&L);
    // ArbreBin *P=rechercheArbreBin2(A,'j',&L);
    // noeudsdelarbre(A,&L);
    // afficherArbreBinaire(A);
    // afficherListe(L);
    // parcoursInfixe(dictionnaire);

    // coupure(A, 13, &G, &D);
    // parcoursInfixe(G);
    // printf("\n");
    // parcoursInfixe(D);

    // afficherArbreBinaire(A);
    // printf("\n sous arbre gauche \n");
    // afficherArbreBinaire(G);
    // printf("\n sous arbre droite \n");
    // afficherArbreBinaire(D);

    // printf("parcours infixe: (pour un ABR on obtient des valeurs triées) ");
    // parcoursInfixe(A);
    // printf("\n l'arbre est binaire (0:non | 1: oui) %d", estABR(A));
    // printf("\n l'hauteur  de l'arbre est %d ", hauteurAbreRecur(A));
    // printf("\n le nombres de feuilles  de l'arbre %d ", nombreFeuilles(A));
    // printf("\n maximum  de l'arbre %d ", maximumArbre(A));
    // int entree;
    // printf("quel elt cherchez-vous dans l'arbre? ");
    // scanf("%d", &entree);
    // printf("\n recherche récursive de l'element %d dans l'arbre (0:non | 1: oui) %d ",entree, rechercheArbreBin(A, 25));
    // printf("\n sous arbre avec la cle %d \n",entree);
    // afficherArbreBinaire(rechercheArbreBin2(A, entree));
    // libererArbre(A);
}
void afficherMot(char *mot, char *lettresDevinees)
{
    for (int i = 0; i < strlen(mot); i++)
    {
        if (strchr(lettresDevinees, mot[i]) != NULL)
        {
            printf("%c ", mot[i]);
        }
        else
        {
            printf("* ");
        }
    }
    printf("\n");
}

int hangman(char *mot, int maxTentatives, char a)
{
    char lettresDevinees[26] = {'\0'}; // Array to store guessed letters
    int tentatives = 0;

    printf("Bienvenue dans le jeu du Pendu !\n");

    while (tentatives < maxTentatives)
    {
        printf("\nTentative %d/%d\n", tentatives + 1, maxTentatives);
        afficherMot(mot, lettresDevinees);

        char lettre;
        printf("Devinez une lettre : ");
        scanf(" %c", &lettre);
        lettre = tolower(lettre); // Convert to lowercase

        if (strchr(lettresDevinees, lettre) != NULL)
        {
            printf("Vous avez déjà deviné cette lettre. Essayez encore.\n");
            continue;
        }

        lettresDevinees[strlen(lettresDevinees)] = lettre;

        if (strchr(mot, lettre) != NULL)
        {
            printf("Bonne devinette !\n");
            int motComplet = 1;
            for (int i = 0; i < strlen(mot); i++)
            {
                if (strchr(lettresDevinees, mot[i]) == NULL)
                {
                    motComplet = 0;
                    break;
                }
            }

            if (motComplet)
            {
                printf("Félicitations ! Vous avez deviné le mot : %s\n", mot);
                return 1;
            }
        }
        else
        {
            if (a == 'm')
            {
                printf("\033[H\033[J ┏━━━┓\n");
                printf(" ┃   │\n");
                printf(" ┃   %c\n", tentatives < 1 ? ' ' : 'O');
                printf(" ┃  %c%s%c\n", tentatives < 3 ? ' ' : '/', tentatives < 2 ? " " : "│", tentatives < 4 ? ' ' : '\\');
                printf(" ┃   %c\n", tentatives < 5 ? ' ' : '|');
                printf(" ┃  %c %c\n", tentatives < 6 ? ' ' : '/', tentatives < 7 ? ' ' : '\\');
                printf(" ┃\n");
                printf("┏┻━━━━━━┓\n┃       ┗━┓\n┗━━━━━━━━━┛\n");
                // printf("Désolé, la lettre n'est pas dans le mot.\n");
                tentatives++;
            }
            if (a == 'h')
            {
                printf("\033[H\033[J ┏━━━┓\n");
                printf(" ┃   %c\n", tentatives < 0 ? ' ' : 'O');
                printf(" ┃  %c%s%c\n", tentatives < 2 ? ' ' : '/', tentatives < 1 ? " " : "│", tentatives < 3 ? ' ' : '\\');
                printf(" ┃  %c %c\n", tentatives < 4 ? ' ' : '/', tentatives < 5 ? ' ' : '\\');
                printf(" ┃\n");
                printf("┏┻━━━━━━┓\n┃       ┗━┓\n┗━━━━━━━━━┛\n");
                // printf("Désolé, la lettre n'est pas dans le mot.\n");
                tentatives++;
            }
            if (a == 'e')
            {
                printf("\033[H\033[J ┏━━━┓\n");
                printf(" ┃   %c\n", tentatives < 1 ? ' ' : 'O');
                printf(" ┃  %c%s%c\n", tentatives < 3 ? ' ' : '/', tentatives < 2 ? " " : "│", tentatives < 4 ? ' ' : '\\');
                printf(" ┃   %c\n", tentatives < 5 ? ' ' : '|');
                printf(" ┃   %c\n", tentatives < 6 ? ' ' : '|');
                printf(" ┃   %c\n", tentatives < 7 ? ' ' : '|');
                printf(" ┃  %c %c\n", tentatives < 8 ? ' ' : '/', tentatives < 9 ? ' ' : '\\');
                printf(" ┃\n");
                printf("┏┻━━━━━━┓\n┃       ┗━┓\n┗━━━━━━━━━┛\n");
                tentatives++;
            }
            // else {
            //     printf("Désolé, la lettre n'est pas dans le mot.\n");
            //                 tentatives++;}
        }
    }

    printf("Dommage ! Vous n'avez pas réussi à deviner le mot. Le mot était : %s\n", mot);
    return 0;
}

int main(int argc, char *argv[])
{
    char manuelle[100];
    arbres();
    int choix;
    ArbreBin *A = NULL;
    char **motArray = NULL;
    int motCount = 0;
    creerDictionnaire(&A, &motArray, &motCount);
    QueueNode *queue = NULL;
    // afficherArbreBinaire(A);
    for (int i = 0; i < motCount; i++)
    {
        printf("%s\n", motArray[i]);
    }
    // char *testing="";
    // int a=piocherMot(&testing);
    printf("voulez vous ajouter d'autre mots manuellement ? \n");
    printf("1 :oui  \t 0:non \n");
    scanf("%d", &choix);
    while (choix == 1)
    {
        printf("donner le mot a inserer ");
        scanf("%s", manuelle);
        // Allocate memory for the new word in the dynamic array
        char *newWord = (char *)malloc(100 * sizeof(char)); // Assuming the maximum word length is 100
        if (newWord == NULL)
        {
            printf("\nMemory allocation error");
            break;
        }

        // Copy the manually entered word to the new memory
        strcpy(newWord, manuelle);

        // Insert the word into the dictionary tree
        dicoInsererMot(newWord, &A, &queue);

        // Insert the word into the dynamic array
        char **newMotArray = (char **)realloc(motArray, (motCount + 1) * sizeof(char *));
        if (newMotArray == NULL)
        {
            printf("\nMemory reallocation error");
            free(newWord);
            break;
        }

        newMotArray[motCount] = newWord;
        motArray = newMotArray;
        motCount++;
        dicoInsererMot(manuelle, &A, &queue);
        printf("le nouveau dictionnaire ");
        // afficherArbreBinaire(A);
        for (int i = 0; i < motCount; i++)
        {
            printf("%s\n", motArray[i]);
        }
        printf("voulez vous ajouter d'autre mots manuellement ? \t '1' :oui  \t '0':non \n");
        scanf("%d", &choix);
    }

    printf("\n\t Be aware you can be hanged!!.");
    // Ascii Art
    printf("       _                                             \n");
    printf("      | |                                            \n");
    printf("      | |__   __ _ _ __   __ _ _ __ ___   __ _ _ __  \n");
    printf("      | '_ \\ / _` | '_ \\ / _` | '_ ` _ \\ / _` | '_ \\ \n");
    printf("      | | | | (_| | | | | (_| | | | | | | (_| | | | | \n");
    printf("      |_| |_|\\__,_|_| |_|\\__, |_| |_| |_|\\__,_|_| |_| \n");
    printf("                          __/ |                      \n");
    printf("                         |___/  \n");
    printf("      ");
    char l;
    char a[2];
    printf("choisir le niveau de difficulté :");
    printf("e: easy ,m :medium , h: hard \n");
    scanf(" %1s", a);
    char *randomWord = motAleatoire(motArray, motCount);
    printf("Mot aleatoire : %s\n", randomWord);
    // Get the length of the random word
    int wordLength = strlen(randomWord);
    // Print * for each character in the word
    for (int i = 0; i < wordLength; i++)
    {
        printf("*");
    }
    printf("\n");
    switch (a[0])
    {
    case 'e':
        hangman(randomWord, 10, 'e');
        break;
    case 'm':
        hangman(randomWord, 8, 'm');
        break;
    case 'h':
        hangman(randomWord, 6, 'h');
        break;
    default:
        printf("Niveau de difficulté non reconnu.\n");
        break;
    }
}