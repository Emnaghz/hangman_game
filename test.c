#include <stdio.h>
#include <math.h>
#include <stdbool.h>
#include <string.h>
#include "listes.h"
#include "arbres.h"
#include "dico.c"
#include <stdlib.h>
// ANSI escape codes for text colors
#define ANSI_COLOR_RED "\x1b[31m"
#define ANSI_COLOR_RESET "\x1b[0m"
#define ANSI_COLOR_GREEN "\x1b[32m"
void testSubtree(char *mot)
{
    printf("test recherche : génère le sous arbre représentant le chemin de recherche parcouru \n");
    sousArbreDeRecherche(mot);
    printf("TEST VALIDÉ de la recherche \n");
}
void testAffichage()
{
    int choix;
    ArbreBin *A = NULL;
    QueueNode *queue = NULL;
    char **motArray = NULL;
    int motCount = 0;
        printf("TEST AFFICHAGE: génère l'arbre du dictionnaire \n");
    creerDictionnaire(&A, &motArray, &motCount);
    generateMermaidScript(A, "mermaid.md");
    printf("TEST VALIDÉ de l'affichage \n");
}
void testAjout(char *mot)
{     printf("test ajout : \n");
    ArbreBin *A = NULL;
    QueueNode *queue = NULL;
    addToDictionary(mot);
    dicoInsererMot(mot, &A, &queue);
    printf("TEST VALIDÉ : Le mot %s est ajouté \n",mot);
}
int main(int argc, char *argv[])
{
    testSubtree("chat");
    testAjout("maroc");
    testAffichage();
}