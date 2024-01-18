#include <stdio.h>
#include <math.h>
#include <stdbool.h>
#include <string.h>
#include "listes.h"
#include "arbres.h"
#include "dico.c"

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

int main(int argc, char *argv[])
{char manuelle[100];
    arbres();
    int choix;
        ArbreBin *A =NULL;
        char **motArray = NULL;
    int motCount = 0;
        creerDictionnaire(&A,&motArray,&motCount);
    QueueNode *queue = NULL;
        // afficherArbreBinaire(A);
        for (int i = 0; i < motCount; i++)
    {
        printf("%s\n", motArray[i]);
    }
    // char *testing="";
    // int a=piocherMot(&testing);
    printf("voulez vous ajouter d'autre mots manuellement ? \n");
     printf("1 :oui  \n 0:non \n");
    scanf("%d",&choix);
        while(choix==1){
        printf("donner le mot a inserer ");
    scanf("%s",manuelle);
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
    dicoInsererMot(manuelle,&A,&queue);
    printf("le nouveau dictionnaire ");
    //afficherArbreBinaire(A);
         for (int i = 0; i < motCount; i++)
    {
        printf("%s\n", motArray[i]);
    }
        printf("voulez vous ajouter d'autre mots manuellement ? \t '1' :oui  \t '0':non \n");
     scanf("%d",&choix);}

}