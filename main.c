#include <stdio.h>
#include <math.h>
#include <stdbool.h>

#include "listes.h"
#include "arbres.h"
#include "autre/polynomes.h"

ArbreBin *exempleArbre()
{
    // 0              12
    // 1       10           18
    // 2      4    11     17    25
    ArbreBin *A;
    A = initArbreBin();
    A = creerFeuille(12);
    A->FG = creerFeuille(10);
    A->FD = creerFeuille(18);
    A->FG->FG = creerFeuille(4);
    A->FG->FD = creerFeuille(11);
    A->FD->FG = creerFeuille(17);
    A->FD->FD = creerFeuille(25);

    return A;
}
void arbres()
{
    ArbreBin *A = exempleArbre();
    // afficherArbreBinaire(A);
    // ArbreBin *G = NULL;
    // ArbreBin *D = NULL;
    // suppression(&A,12);
    // coupure(A, 13, &G, &D);
    afficherArbreBinaire(A);
    parcoursInfixe(A);
    // insererRacine(&A,13);
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

void listes()
{
    Liste *l1, *l2, *l3;
    int T[] = {1, 2, 3, 4, 5};
    l2 = creerListeDunTableau2(l2, T, 5);
    l2 = inverserListe(l2);
    afficherListe(l2);
    libererListe(l2);
}

int main(int argc, char *argv[])
{

    arbres();
    // polynomes();
    // listes();
}
