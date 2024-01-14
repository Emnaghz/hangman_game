#include <stdio.h>
#include <math.h>
#include <stdbool.h>
#include <string.h>
#include "listes.h"
#include "verifortho.h"
#include "arbres.h"
#include "autre/polynomes.h"
#include "arbresnaires.h"

ArbreBin *exempleArbre()
{
    // 0              p
    // 1        c           t
    // 2      a    j    s     x
    ArbreBin *A;
    A = initArbreBin();
    A = creerFeuille('p');
    A->FG = creerFeuille('c');
    A->FD = creerFeuille('t');
    // A->FG->FG = creerFeuille('a');
    A->FG->FD = creerFeuille('j');
    A->FD->FG = creerFeuille('s');
    // A->FD->FD = creerFeuille('x');
    return A;
}


void arbres()
{
    ArbreBin *A = exempleArbre();
    Liste *L=initListe();

    // ArbreBin *dictionnaire = genererABR();
    // ArbreBin *P=rechercheRecurABR(A,'j',&L);
    // ArbreBin *P=rechercheArbreBin2(A,'j',&L);
    noeudsdelarbre(A,&L);
    afficherArbreBinaire(A);
    afficherListe(L);
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
{
    arbres();
    
}
