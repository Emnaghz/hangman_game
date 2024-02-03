#include <stdio.h>
#include <math.h>
#include <stdbool.h>
#include <string.h>
#include "listes.h"
#include "arbres.h"
#include "dico.c"
#include <stdlib.h>
#include <termios.h>
// ANSI escape codes for text colors
#define ANSI_COLOR_RED "\x1b[31m"
#define ANSI_COLOR_RESET "\x1b[0m"
#define ANSI_COLOR_GREEN "\x1b[32m"
#define ANSI_COLOR_BLUE "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
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

char *motAleatoire(char **motArray, int motCount, int mn, int mx)
{
    int a = nombreAleatoire(mn, mx);
    if (motCount <= 0 || motArray == NULL)
    {
        // Invalid input or empty array
        return NULL;
    }
    srand(time(NULL));
    // Generate a random index
    // printf("le nombre %d", a);
    int randomIndex = rand() % motCount;
    while (strlen(motArray[randomIndex]) != a)
        randomIndex = rand() % motCount;
    // Return the word at the random index
    return motArray[randomIndex];
}

void arbres()
{
    ArbreBin *A = exempleArbre();
    QueueNode *queue = NULL;
    generateMermaidScript(A, "mermaid.md");
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
    int wordLength = strlen(mot);
    printf("┌");
    for (int i = 0; i < wordLength * 2 + 1; i++)
    {
        printf("─");
    }
    printf("┐\n");
    printf("│ ");
    for (int i = 0; i < strlen(mot); i++)
    {
        if (strchr(lettresDevinees, mot[i]) != NULL)
        {
            printf(ANSI_COLOR_GREEN "%c " ANSI_COLOR_RESET, mot[i]);
        }
        else
        {
            printf("* ");
        }
    }
    printf("│\n");
    printf("└");
    for (int i = 0; i < wordLength * 2 + 1; i++)
    {
        printf("─");
    }
    printf("┘\n");
    printf("\n");
}

int hangman(char *mot, int maxTentatives, char a, char *mode)
{
    printf("\n\t Be aware you can be hanged !!\n");

    // Ascii Art
    printf("       _                                             \n");
    printf("      | |                                            \n");
    printf("      | |__   __ _ _ __   __ _ _ __ ___   __ _ _ __  \n");
    printf("      | '_ \\ / _` | '_ \\ / _` | '_ ` _ \\ / _` | '_ \\ \n");
    printf("      | | | | (_| | | | | (_| | | | | | | (_| | | | | \n");
    printf("      |_| |_|\\__,_|_| |_|\\__, |_| |_| |_|\\__,_|_| |_| \n");
    printf("                          __/ |                      \n");
    printf("                         |___/  \n");
    printf("      \n");
    char lettresDevinees[26] = {'\0'}; // Array to store guessed letters
    int tentatives = 0;

    printf("\t Bienvenue dans le jeu du Pendu !\n");

    while (tentatives < maxTentatives)
    {     printf(ANSI_COLOR_MAGENTA "\n*******************************************\n" ANSI_COLOR_RESET);
    printf(ANSI_COLOR_MAGENTA " \t %s \n" ANSI_COLOR_RESET, mode);
    printf(ANSI_COLOR_MAGENTA "*******************************************\n" ANSI_COLOR_RESET);
        printf("\n Il vous reste %d tentative sur %d\n", maxTentatives - tentatives, maxTentatives);
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
            { printf(ANSI_COLOR_BLUE "\n***********************************************************************************\n" ANSI_COLOR_RESET);
              printf(ANSI_COLOR_BLUE "\t \t Résultats \n" ANSI_COLOR_RESET);
              printf(ANSI_COLOR_BLUE "***********************************************************************************\n" ANSI_COLOR_RESET);

                printf("%s   _____                            _         _       _   _                   _ %s\n", ANSI_COLOR_GREEN, ANSI_COLOR_RESET);
                printf("%s  / ____|                          | |       | |     | | (_)                 | |%s\n", ANSI_COLOR_GREEN, ANSI_COLOR_RESET);
                printf("%s | |     ___  _ __   __ _ _ __ __ _| |_ _   _| | __ _| |_ _  ___  _ __  ___  | |%s\n", ANSI_COLOR_GREEN, ANSI_COLOR_RESET);
                printf("%s | |    / _ \\| '_ \\ / _` | '__/ _` | __| | | | |/ _` | __| |/ _ \\| '_ \\/ __| | |%s\n", ANSI_COLOR_GREEN, ANSI_COLOR_RESET);
                printf("%s | |___| (_) | | | | (_| | | | (_| | |_| |_| | | (_| | |_| | (_) | | | \\__ \\ |_|%s\n", ANSI_COLOR_GREEN, ANSI_COLOR_RESET);
                printf("%s  \\_____\\___/|_| |_|\\__, |_|  \\__,_|\\__|\\__,_|_|\\__,_|\\__|_|\\___/|_| |_|___/ (_)%s\n", ANSI_COLOR_GREEN, ANSI_COLOR_RESET);
                printf("%s                     __/ |                                                      %s\n", ANSI_COLOR_GREEN, ANSI_COLOR_RESET);
                printf("%s                    |___/                                                       %s\n", ANSI_COLOR_GREEN, ANSI_COLOR_RESET);

                printf(ANSI_COLOR_GREEN "Félicitations !\n" ANSI_COLOR_RESET "Vous avez deviné le mot: \t" ANSI_COLOR_BLUE "%s\n" ANSI_COLOR_RESET, mot);
                    afficherMot(mot, mot);
            printf(ANSI_COLOR_BLUE "***********************************************************************************\n" ANSI_COLOR_RESET);                return 1;
            }
        }
        else
        {
            if (a == 'm')
            {
                printf("\n");
                printf("\033[H\033[J ┏━━━┓\n");
                printf(" ┃   │\n");
                printf(" ┃   %c\n", tentatives < 1 ? ' ' : 'O');
                printf(" ┃  %c%s%c\n", tentatives < 3 ? ' ' : '/', tentatives < 2 ? " " : "│", tentatives < 4 ? ' ' : '\\');
                printf(" ┃   %c\n", tentatives < 5 ? ' ' : '|');
                printf(" ┃  %c %c\n", tentatives < 6 ? ' ' : '/', tentatives < 7 ? ' ' : '\\');
                printf(" ┃\n");
                printf("┏┻━━━━━━┓\n┃       ┗━┓\n┗━━━━━━━━━┛\n");
                // printf("Désolé, la lettre %c n'est pas dans le mot.\n", lettre);
                tentatives++;
            }
            if (a == 'h')
            {
                printf("\n");
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
                printf("\n");
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
     printf(ANSI_COLOR_BLUE "\n******************************************************\n" ANSI_COLOR_RESET);
    printf(ANSI_COLOR_BLUE "\t \t Résultats \n" ANSI_COLOR_RESET);
     printf(ANSI_COLOR_BLUE "******************************************************\n " ANSI_COLOR_RESET);
    printf("%s   _____                                             %s\n", ANSI_COLOR_RED, ANSI_COLOR_RESET);
    printf("%s  / ____|                                            %s\n", ANSI_COLOR_RED, ANSI_COLOR_RESET);
    printf("%s | |  __  __ _ _ __ ___   ___    _____   _____ _ __ %s\n", ANSI_COLOR_RED, ANSI_COLOR_RESET);
    printf("%s | | |_ |/ _` | '_ ` _ \\ / _ \\  / _ \\ \\ / / _ \\ '__|%s\n", ANSI_COLOR_RED, ANSI_COLOR_RESET);
    printf("%s | |__| | (_| | | | | | |  __/ | (_) \\ V /  __/ |   %s\n", ANSI_COLOR_RED, ANSI_COLOR_RESET);
    printf("%s  \\_____|\\__,_|_| |_| |_|\\___|  \\___/ \\_/ \\___|_|   %s\n", ANSI_COLOR_RED, ANSI_COLOR_RESET);
    printf("%s                                                    %s\n", ANSI_COLOR_RED, ANSI_COLOR_RESET);
    printf("%s                                                    %s\n", ANSI_COLOR_RED, ANSI_COLOR_RESET);

    printf(ANSI_COLOR_RED "Dommage ! Vous n'avez pas réussi à deviner le mot.\n" ANSI_COLOR_RESET);
    printf("Le mot était : \t" ANSI_COLOR_BLUE "%s\n" ANSI_COLOR_RESET, mot);
    afficherMot(mot, mot);
    printf(ANSI_COLOR_BLUE "******************************************************\n " ANSI_COLOR_RESET);
    return 0;
}
// Fonction pour obtenir un caractère sans afficher à l'écran
char getch()
{
    char buf = 0;
    struct termios old = {0};
    fflush(stdout);

    if (tcgetattr(0, &old) < 0)
        perror("tcsetattr()");
    old.c_lflag &= ~ICANON;
    old.c_lflag &= ~ECHO;
    old.c_cc[VMIN] = 1;
    old.c_cc[VTIME] = 0;

    if (tcsetattr(0, TCSANOW, &old) < 0)
        perror("tcsetattr ICANON");

    if (read(0, &buf, 1) < 0)
        perror("read()");

    old.c_lflag |= ICANON;
    old.c_lflag |= ECHO;

    if (tcsetattr(0, TCSADRAIN, &old) < 0)
        perror("tcsetattr ~ICANON");

    return (buf);
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
    // Display menu
    printf(ANSI_COLOR_MAGENTA "\n============================================================\n" ANSI_COLOR_RESET);
    printf("                            Menu     \n");
    printf(ANSI_COLOR_MAGENTA "============================================================\n" ANSI_COLOR_RESET);
    printf("\t 1. Ajouter un mot\n");
    printf("\t 2. Visualiser l'arbre\n");
    printf("\t 3. Rechercher un mot\n");
    printf("\t 4. Supprimer un mot\n");
    printf("\t 5. Visualiser les caractéristiques du dictionnaire\n");
    printf("\t 6. Jouer au Pendu\n");
    printf("\t 0. Quitter\n");
    printf(ANSI_COLOR_MAGENTA "============================================================ \n" ANSI_COLOR_RESET);
    // Get user choice
    printf("Choix: ");
    scanf("%d", &choix);
    printf("\n \n");
    // Perform action based on user choice
    switch (choix)
    {
    case 1:
        printf("donner le mot a inserer ");
        scanf("%s", manuelle);
        //  Allocate memory for the new word in the dynamic array
        char *newWord = (char *)malloc(100 * sizeof(char)); // Assuming the maximum word length is 100
        if (newWord == NULL)
        {
            printf("\nMemory allocation error");
            break;
        }
        // Copy the manually entered word to the new memory
        strcpy(newWord, manuelle);
        addToDictionary(manuelle);
        // Insert the word into the dictionary tree
        dicoInsererMot(newWord, &A, &queue);
        // printf("\n insertion terminé \n");
        //  Insert the word into the dynamic array
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
        break;
    case 2:
        generateMermaidScript(A, "mermaid.md");
        break;
    case 3:
        printf("Donner le mot a chercher  ");
        scanf("%s", manuelle);
        sousArbreDeRecherche(manuelle);
        break;
        case 4:
           printf("Donner le mot a supprimer :");
        scanf("%s", manuelle);
            supprimerMot("dictionnaire.txt",manuelle);
            supprimerLignesVides("dictionnaire.txt");
            break;
    case 5:
        visualiserCaracteristiquesDictionnaire();
        break;
    case 6:
        int nbr;
        printf(ANSI_COLOR_MAGENTA "*******************************************\n" ANSI_COLOR_RESET);
        printf("              MENU DE JEU                  \n");
        printf(ANSI_COLOR_MAGENTA "*******************************************\n " ANSI_COLOR_RESET);
        printf(" 1. Jouer en mode solo\n");
        printf("  2. Jouer en mode deux joueurs\n");
        printf(ANSI_COLOR_MAGENTA "*******************************************\n" ANSI_COLOR_RESET);
        printf("Choisissez l'option (1 ou 2) : ");
        scanf("%d", &nbr);
        switch (nbr)
        {
        case 1:
            printf("Vous avez choisi de jouer en mode solo.\n");
            break;

        case 2:
            printf("Vous avez choisi de jouer en mode deux joueurs.\n");
            break;
        default:
            printf("Choix invalide. Veuillez choisir 1 ou 2.\n");
            scanf("%d", &nbr);
            break;
        }
        char l, a[2], rep;
        printf("Choisir le niveau de difficulté :\n");
        printf("e: easy\n");
        printf("m: medium\n");
        printf("h: hard\n");
        scanf(" %1s", a);
        printf("\n");
        char *randomWord = "";
        randomWord = (char *)malloc(50 * sizeof(char));
        int i = 0;
        char c;
        if (nbr == 2)
        {
         printf(ANSI_COLOR_MAGENTA "*******************************************\n" ANSI_COLOR_RESET);
            printf(ANSI_COLOR_MAGENTA "\t Tour de Joueur 1 : \n" ANSI_COLOR_RESET);
          printf(ANSI_COLOR_MAGENTA "*******************************************\n" ANSI_COLOR_RESET);
            printf("Joueur 1, veuillez entrer le mot secret : \n");
            switch (a[0])
            {
            case 'e':
                printf("Vous etes en niveau easy de preference ,le mot entre 2 et 4 caracteres \n");
                break;
            case 'm':
                printf("Vous etes en niveau medium   de preference le mot entre 4 et 6 caracteres \n");
                break;
            case 'h':
                printf("Vous etes en niveau hard ,de preference le mot entre 7 et 10 caracteres \n ");
                break;
            default:
                printf("Niveau de difficulté non reconnu.\n");
                break;
            }
            while (1)
            {
                c = getch();
                if (c == '\r' || c == '\n')
                {
                    // Si l'utilisateur appuie sur Entrée, terminer la saisie
                    randomWord[i] = '\0';
                    break;
                }
                else if (i < sizeof(randomWord) - 1)
                {
                    // Stocker le caractère dans le motSecret
                    randomWord[i++] = c;
                    // Afficher un astérisque à l'écran
                    printf("*");
                }
            }
            printf("\n  Voulez vous enregister ce mot dans le dictionnaire : \n");
            printf("O. OUI \n");
            printf("N. NON \n");
            scanf(" %c", &rep);
            if (rep == 'O')
            {
                addToDictionary(randomWord);
                // Insert the word into the dictionary tree
                dicoInsererMot(randomWord, &A, &queue);
            }
        }
        switch (a[0])
        {
        case 'e':
            if (nbr == 2)
            {

                hangman(randomWord, 10, 'e', "Tour de Joueur 2");
            }
            else if (nbr == 1)
            {
                randomWord = motAleatoire(motArray, motCount, 2, 4);
                hangman(randomWord, 10, 'e', "Mon tour");
            }
            break;
        case 'm':
            if (nbr == 2)
            {
                hangman(randomWord, 8, 'm', "Tour de Joueur 2");
            }
            else if (nbr == 1)
            {
                randomWord = motAleatoire(motArray, motCount, 4, 6);
                hangman(randomWord, 8, 'm', "Mon tour");
            }
            break;
        case 'h':
            if (nbr == 2)
            {
                hangman(randomWord, 6, 'h', "Tour de Joueur 2");
            }
            else if (nbr == 1)
            {
                randomWord = motAleatoire(motArray, motCount, 7, 10);
                hangman(randomWord, 6, 'h', "Mon tour");
            }
            break;
        default:
            printf("Niveau de difficulté non reconnu.\n");
            scanf(" %1s", a);
            break;
        }
        free(randomWord);
    }
}
