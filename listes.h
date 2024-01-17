#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>

typedef struct Liste
{
    int val;
    struct Liste *suiv;
} Liste;
Liste *initListe()
{
    return NULL;
}
typedef struct Pile
{
    struct Liste *sommet;
} Pile;

typedef struct File
{
    struct Liste *tete;
} File;

Liste *creerNoeud(int n)
{
    Liste *elt = (Liste *)malloc(sizeof(Liste));
    elt->val = n;
    elt->suiv = NULL;
    return elt;
}
Liste *ajouterElementDebut(Liste *L, int n)
{
    Liste *head = creerNoeud(n);
    head->suiv = L;
    L = head;
    return L;
}
Liste *ajouterElementFin(Liste *L, int n)
{
    Liste *elt = creerNoeud(n);
    Liste *tmp = L;
    if (tmp == NULL)
    {
        L = elt;
    }
    else
    {
        while (tmp->suiv != NULL)
        {
            tmp = tmp->suiv;
        }
        tmp->suiv = elt;
    }
    return L;
}
Liste *creerListeDunTableau(Liste *L, int *T, int taille)
{
    // traiter la tete de la liste à part
    L = creerNoeud(T[0]);
    Liste *tmp = L;
    // traiter les cases restantes du tableau
    for (int i = 1; i < taille; i++)
    {
        L = ajouterElementDebut(L, T[i]);
    }
    return L;
}
Liste *creerListeDunTableau2(Liste *L, int *T, int taille)
{
    // traiter la tete de la liste à part

    L = creerNoeud(T[0]);
    Liste *tmp = L;
    // traiter les cases restantes du tableau
    for (int i = 1; i < taille; i++)
    {
        L = ajouterElementFin(L, T[i]);
    }
    return L;
}
void afficherListe(Liste *L)
{
    Liste *tmp = L;
    while (tmp != NULL)
    {
        printf(" %c ", tmp->val);
        tmp = tmp->suiv;
    }
    printf("\n");
}
void libererListe(Liste *L)
{
    Liste *tmp = L;
    Liste *nouveau;
    while (tmp != NULL)
    {
        nouveau = tmp->suiv;
        free(tmp);
        tmp = nouveau;
    }
}
Liste *suppressionEntete(Liste *L)
{
    Liste *tete = L;
    L = L->suiv;
    free(tete);
    return L;
}
Liste *suppressionDernierElement(Liste *L)
{
    // Utiliser deux pointeurs tmp et prec
    Liste *tmp = L;
    Liste *prec = NULL;
    while (tmp->suiv != NULL)
    {
        prec = tmp;
        tmp = tmp->suiv;
    }
    prec->suiv = tmp->suiv;
    free(tmp);
    return L;
}
Liste *suppressionParIndice(Liste *L, int pos)
{
    // les indices commencent à 1.
    // pos=1 suppression de l'entete
    if (pos == 1)
    {
        return L->suiv;
    }
    // pos >1 : utiliser deux pointeurs tmp et prec , avec un compteur
    Liste *tmp = L;
    Liste *prec = NULL;
    int compteur = 1;
    while ((tmp != NULL) && (compteur < pos))
    {
        compteur += 1;
        prec = tmp;
        tmp = tmp->suiv;
    }
    prec->suiv = tmp->suiv;
    free(tmp);
    return L;
}
Liste *insertionParIndice(Liste *L, int pos, int n)
{
    // les indices commencent à 1.
    if (pos == 1)
    {
        Liste *head = creerNoeud(n);
        head->suiv = L;
        L = head;
        return L;
    }
    // pos >1 : utiliser deux pointeurs tmp et prec , avec un compteur
    Liste *tmp = L;
    Liste *prec = NULL;
    int compteur = 1;
    while ((tmp != NULL) && (compteur < pos))
    {
        compteur += 1;
        prec = tmp;
        tmp = tmp->suiv;
    }
    Liste *head = creerNoeud(n);
    prec->suiv = head;
    head->suiv = tmp;

    return L;
}
int nombreNoeudsListe(Liste *L)
{
    Liste *tmp = L;
    int n = 0;
    while (tmp != NULL)
    {
        n++;
        tmp = tmp->suiv;
    }
    return n;
}

// https://www.youtube.com/watch?v=MRe3UsRadKw
// inversion recursive d'une liste chainee
Liste *inverserListe(Liste *L)
{
    if (!L)
    {
        return NULL;
    }
    else if (!L->suiv)
    {
        return L;
    }
    Liste *dernier = inverserListe(L->suiv);
    L->suiv->suiv = L;
    L->suiv = NULL;
    L = dernier;
    return dernier;
}
// e.g. liste=inverserListe(liste);

Liste *inverserRecur(Liste *actuel, Liste *prev)
{
    if (actuel == NULL)
    {
        Liste *newList = prev; // tout dernier element
        return newList;
    }
    Liste *resultat = inverserRecur(actuel->suiv, actuel);
    actuel->suiv = prev;
    return resultat;
}

Liste *copieListe(Liste *L)
{
    Liste *tmp = L;
    Liste *resultat = initListe();
    while (tmp)
    {
        resultat = ajouterElementFin(resultat, tmp->val);
        tmp = tmp->suiv;
    }
    return resultat;
}

