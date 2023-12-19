#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>
typedef struct Polynome
{
    int coeff;
    int deg;
    struct Polynome *suiv;
} Polynome;
Polynome *initPolynome()
{
    return NULL;
}
Polynome *creerMonome(int coeff, int deg)
{
    Polynome *elt = (Polynome *)malloc(sizeof(Polynome));
    elt->coeff = coeff;
    elt->deg = deg;
    elt->suiv = NULL;
    return elt;
}
Polynome *ajouterMonomeFin(Polynome *P, int coeff, int deg)
{
    Polynome *elt = creerMonome(coeff, deg);
    Polynome *tmp = P;
    if (!tmp)
    {
        P = elt;
    }
    else
    {
        while (tmp->suiv)
        {
            tmp = tmp->suiv;
        }
        tmp->suiv = elt;
    }
    return P;
}
Polynome *creerPolynomesAvec2Tab(Polynome *P, int *coeff, int *deg, int taille)
{
    P = creerMonome(coeff[0], deg[0]);
    Polynome *tmp = P;
    for (int i = 1; i < taille; i++)
    {
        P = ajouterMonomeFin(P, coeff[i], deg[i]);
    }
    return P;
}
void afficherPolynome(Polynome *p)
{
    if (p)
    {
        printf("%d*X^%d ", p->coeff, p->deg);
        p = p->suiv;
    }
    while (p)
    {
        printf("+ %d*X^%d ", p->coeff, p->deg);
        p = p->suiv;
    }
    printf("\n");
}
Polynome *copiePolynome(Polynome *P)
{
    // il FAUT initialiser le polynome
    Polynome *res = initPolynome();
    Polynome *tmp = P;
    while (tmp)
    {
        Polynome *nouveau = creerMonome(tmp->coeff, tmp->deg);
        res = ajouterMonomeFin(res, nouveau->coeff, nouveau->deg);
        tmp = tmp->suiv;
    }
    return res;
}
Polynome *additionnerPolynomes(Polynome *P1, Polynome *P2)
{
    if ((!P1) && (!P2))
        return NULL;
    else if ((P1) && (!P2))
        return copiePolynome(P1);
    else if ((!P1) && (P2))
        return copiePolynome(P2);
    else
    {
        Polynome *res = initPolynome();
        Polynome *tmp1 = P1;
        Polynome *tmp2 = P2;
        while (tmp1 && tmp2)
        {
            Polynome *nouveau;
            // comment créer le nouveau monome? 3 cas de figures se présentent.
            if (tmp1->deg < tmp2->deg)
            {
                nouveau = creerMonome(tmp1->coeff, tmp1->deg);
                tmp1 = tmp1->suiv;
            }
            else if (tmp2->deg < tmp1->deg)
            {
                nouveau = creerMonome(tmp2->coeff, tmp2->deg);
                tmp2 = tmp2->suiv;
            }
            else
            {
                nouveau = creerMonome(tmp1->coeff + tmp2->coeff, tmp1->deg);
                tmp1 = tmp1->suiv;
                tmp2 = tmp2->suiv;
            }
            res = ajouterMonomeFin(res, nouveau->coeff, nouveau->deg);
        }
        while (tmp1)
        {
            res = ajouterMonomeFin(res, tmp1->coeff, tmp1->deg);
            tmp1 = tmp1->suiv;
        }
        while (tmp2)
        {
            res = ajouterMonomeFin(res, tmp2->coeff, tmp2->deg);
            tmp2 = tmp2->suiv;
        }
        return res;
    }
}
Polynome *multiplierPolynomeParMonome(Polynome *P, Polynome *p)
{
    if (!P)
        return NULL;
    else
    {
        Polynome *res = initPolynome();
        Polynome *tmp = P;
        while (tmp)
        {
            Polynome *nouveau = creerMonome(tmp->coeff * p->coeff, tmp->deg + p->deg);
            res = ajouterMonomeFin(res, nouveau->coeff, nouveau->deg);
            tmp = tmp->suiv;
        }
        return res;
    }
}
Polynome *multiplierPolynomes(Polynome *P1, Polynome *P2)
{
    if ((!P1) || (!P2))
    {
        return NULL;
    }
    else
    {
        Polynome *res = initPolynome();
        Polynome *tmp1 = P1;
        Polynome *tmp2 = P2;
        while (tmp2)
        {
            Polynome *terme = multiplierPolynomeParMonome(tmp1, tmp2);
            res = additionnerPolynomes(res, terme);
            tmp2 = tmp2->suiv;
        }
        return res;
    }
}
void libererPolynome(Polynome *P)
{
    Polynome *tmp = P;
    Polynome *suivant;
    while (tmp)
    {
        suivant = tmp->suiv;
        free(tmp);
        tmp = suivant;
    }
}

void polynomes()
{
    int coeff[] = {1, 1};
    int coeff1[] = {1};

    int deg[] = {0, 1};
    int deg1[] = {0};

    Polynome *P, *Q, *R, *p;
    P = creerPolynomesAvec2Tab(P, coeff, deg, 2);
    Q = creerPolynomesAvec2Tab(Q, coeff1, deg1, 1);

    Polynome *T = multiplierPolynomes(P, P);
    printf("\n");

    afficherPolynome(P);
    afficherPolynome(Q);
    printf("\n");

    afficherPolynome(T);
    libererPolynome(P);
    libererPolynome(T);
}