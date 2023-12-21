// vérificateur d'orthographe implémenté sous la forme d'un ABR
typedef struct Noeud
{
    char *mot;
    struct Noeud *FG;
    struct Noeud *FD;
} Noeud;
typedef struct Dictionnaire
{
    struct Noeud *racine;
} Dictionnaire;

Dictionnaire *initDictionnaire()
{
    Dictionnaire *dict = (Dictionnaire *)malloc(sizeof(Dictionnaire));
    dict->racine = NULL;
    return dict;
}
Noeud *creerFeuilleDict(char *mot)
{
    Noeud *elt = (Noeud *)malloc(sizeof(Noeud));
    // allouer de la mémoire pour le mot du noeud
    elt->mot = (char *)malloc(strlen(mot) + 1);
    strcpy(elt->mot, mot);
    elt->FD = NULL;
    elt->FG = NULL;
}

void *insererNoeud(Noeud **N, char *mot)
{
    if (!(*N))
    {
        *N = creerFeuilleDict(mot);
    }
    else
    {
        int resultat = strcmp(mot, (*N)->mot);
        if (resultat < 0)
        {
            insererNoeud(&((*N)->FG), mot);
        }
        else if (resultat > 0)
        {
            insererNoeud(&((*N)->FD), mot);
        }
    }
}
int maximum2(int x, int y)
{
    if (x > y)
        return x;
    else
        return y;
}
int hauteurDictionnaire(Noeud *N)
{
    if ((N == NULL) || ((N->FG == NULL) && (N->FD == NULL)))
        return 0;
    else
        return 1 + maximum2(hauteurDictionnaire(N->FG), hauteurDictionnaire(N->FD));
}
void parcoursInfixeDict(Noeud *N)
{
    if (N)
    {
        parcoursInfixeDict(N->FG);
        printf(" %s ", N->mot);
        parcoursInfixeDict(N->FD);
    }
}
bool existeDict(Noeud *N, char *mot)
{
    if (!N)
        return false;
    else if (strcmp(mot, N->mot) == 0)
    {
        return true;
    }
    else
    {
        if (strcmp(mot, N->mot) > 0)
        {
            return existeDict(N->FD, mot);
        }
        else
        {
            return existeDict(N->FG, mot);
        }
    }
}