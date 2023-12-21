typedef struct ArbreBin
{
    int val;
    struct ArbreBin *FG;
    struct ArbreBin *FD;
} ArbreBin;

typedef struct QueueNode
{
    ArbreBin *arbre;
    struct QueueNode *suiv;
} QueueNode;

typedef struct Queue
{
    QueueNode *tete;
    QueueNode *queue;
} Queue;
QueueNode *createQueueNode(ArbreBin *arbre)
{
    QueueNode *newNode = (QueueNode *)malloc(sizeof(QueueNode));
    newNode->arbre = arbre;
    newNode->suiv = NULL;
    return newNode;
}
Queue *createQueue()
{
    Queue *file = (Queue *)malloc(sizeof(Queue));
    file->tete = NULL;
    file->queue = NULL;
    return file;
}
void enqueue(Queue *queue, ArbreBin *arbre)
{
    QueueNode *newNode = createQueueNode(arbre);
    if (queue->queue == NULL)
    {
        queue->tete = newNode;
        queue->queue = newNode;
    }
    else
    {
        queue->queue->suiv = newNode;
        queue->queue = newNode;
    }
}
ArbreBin *dequeue(Queue *file)
{
    if (file->tete == NULL)
    {
        return NULL;
    }
    ArbreBin *arbre = file->tete->arbre;
    file->tete = file->tete->suiv;
    if (file->tete == NULL)
    {
        file->queue = NULL;
    }
    return arbre;
}
void afficherFile(Queue *file)
{
    QueueNode *tmp = file->tete;
    while (tmp != NULL)
    {
        printf("%d   | ", tmp->arbre->val);
        tmp = tmp->suiv;
    }
}
int fileEstVide(Queue *file)
{
    return (file->tete == NULL);
}

ArbreBin *initArbreBin()
{
    return NULL;
}

ArbreBin *creerFeuille(int n)
{
    ArbreBin *elt = (ArbreBin *)malloc(sizeof(ArbreBin));
    elt->val = n;
    elt->FD = NULL;
    elt->FG = NULL;
    return elt;
}
int hauteurArbreIter(ArbreBin *A)
{
    int niveau = 0;
    Queue *file = createQueue();
    ArbreBin *delim = initArbreBin();
    enqueue(file, A);
    enqueue(file, delim);
    while (!fileEstVide(file))
    {
        ArbreBin *currentArbre = dequeue(file);

        if (currentArbre != NULL)
        {
            if (currentArbre->FG != NULL)
            {
                enqueue(file, currentArbre->FG);
            }
            if (currentArbre->FD != NULL)
            {
                enqueue(file, currentArbre->FD);
            }
        }
        else
        {
            printf("\n");
            if (!fileEstVide(file))
            {
                enqueue(file, delim);
                niveau++;
            }
        }
    }
    return niveau;
}
int max2(int x, int y)
{
    if (x > y)
        return x;
    else
        return y;
}
int max3(int a, int b, int c)
{
    if (a >= b && a >= c)
    {
        return a;
    }
    else if (b >= a && b >= c)
    {
        return b;
    }
    else
    {
        return c;
    }
}
int hauteurAbreRecur(ArbreBin *A)
{
    if ((A == NULL) || ((A->FG == NULL) && (A->FD == NULL)))
        return 0;
    else
        return 1 + max2(hauteurAbreRecur(A->FG), hauteurAbreRecur(A->FD));
}
int maximumArbre(ArbreBin *A)
{
    if (A == NULL)
        return -1;
    else
        return max3(A->val, maximumArbre(A->FG), maximumArbre(A->FD));
}
int nombreFeuilles(ArbreBin *A)
{
    if (A == NULL)
        return 0;
    else
    {
        if ((A->FG == NULL) && (A->FD == NULL))
            return 1;
        else
            return nombreFeuilles(A->FG) + nombreFeuilles(A->FD);
    }
}
// affichage par niveau
void afficherArbreBinaire(ArbreBin *A)
{
    if (A)
    {
        int hauteur = hauteurAbreRecur(A);

        Queue *file = createQueue();
        ArbreBin *delim = initArbreBin();

        enqueue(file, A);
        enqueue(file, delim);
        int niveau = 0;
        while (!fileEstVide(file))
        {
            ArbreBin *currentArbre = dequeue(file);
            if (currentArbre != NULL)
            {
                double what = pow(2, hauteur - niveau);
                int espaces = (int)what - 1;
                for (int i = 0; i < espaces; i++)
                {
                    printf(" ");
                }
                printf(" %d ", currentArbre->val);
                for (int i = 0; i < espaces; i++)
                {
                    printf(" ");
                }
                if (currentArbre->FG != NULL)
                {
                    enqueue(file, currentArbre->FG);
                }
                if (currentArbre->FD != NULL)
                {
                    enqueue(file, currentArbre->FD);
                }
            }
            else
            {
                printf("\n");
                niveau++;
                if (!fileEstVide(file))
                {
                    enqueue(file, delim);
                }
            }
        }
    }
    printf("\n");
}
void parcoursInfixe(ArbreBin *A)
{
    if (A)
    {
        parcoursInfixe(A->FG);
        printf(" %d ", A->val);
        parcoursInfixe(A->FD);
    }
}
void parcoursPostfixe(ArbreBin *A)
{
    if (A)
    {
        parcoursPostfixe(A->FG);
        parcoursPostfixe(A->FD);
        printf(" %d ", A->val);
    }
}
void parcoursPrefixe(ArbreBin *A)
{
    if (A)
    {
        parcoursPrefixe(A->FG);
        parcoursPrefixe(A->FD);
        printf(" %d ", A->val);
    }
}
bool estComplet(ArbreBin *A)
{
    //la condition d'arret: un noeud a exactement un seul fils!
    if (!A->FG && A->FD || !A->FD && A->FG)
    {
        return false;
    }
    // condition d'arret: feuille
    else if (!(A->FG) && !(A->FD))
    {
        return true;
    }
    else
    {
        return estComplet(A->FD)&& estComplet(A->FG);
    }
}
ArbreBin *insererArbreBinRecherche(ArbreBin *A, int n)
{
    if (A == NULL)
    {
        A = creerFeuille(n);
    }
    else
    {
        if ((n >= A->val) && (A->FD != NULL))
        {
            A = insererArbreBinRecherche(A->FD, n);
        }
        else if ((n < A->val) && (A->FG != NULL))
        {
            A = insererArbreBinRecherche(A->FG, n);
        }
    }
    return A;
}

bool rechercheArbreBin(ArbreBin *A, int x)
{
    if (!A)
    {
        return false;
    }
    if (A->val == x)
    {
        return true;
    }
    else
    {
        return rechercheArbreBin(A->FG, x) || rechercheArbreBin(A->FD, x);
    }
}
// Retourne le père et le fils pour un arbre binaire
ArbreBin *rechercheArbreBin2(ArbreBin *A, int cle)
{
    if (!A)
    {
        return NULL;
    }
    if (A->val == cle)
    {
        return A;
    }
    else
    {
        ArbreBin *gauche = rechercheArbreBin2(A->FG, cle);
        ArbreBin *droite = rechercheArbreBin2(A->FD, cle);
        if (gauche)
        {
            return gauche;
        }
        else if (droite)
        {
            return droite;
        }
        else
        {
            return NULL;
        }
    }
}
// recherche recursive dans un arbre binaire
ArbreBin *rechercheRecurABR(ArbreBin *A, int cle)
{
    if (!A)
    {
        return NULL;
    }
    if (A->val == cle)
    {
        return A;
    }
    else
    {
        if (A->val > cle)
        {
            return rechercheRecurABR(A->FG, cle);
        }
        else
        {
            return rechercheRecurABR(A->FD, cle);
        }
    }
}
// basique
bool estABR(ArbreBin *A)
{
    if ((!A) || (!A->FD && !A->FG))
    {
        return true;
    }
    if (A->FD && A->val > A->FD->val || A->FG && A->val < A->FG->val)
    {
        return false;
    }
    else
    {
        return (estABR(A->FD) && estABR(A->FG));
    }
}

// générer deux sous-arbres G et D suivant la clé introduite
// deux cas de figure
void coupure(ArbreBin *A, int cle, ArbreBin **G, ArbreBin **D)
{
    if (!A)
    {
        *G = NULL;
        *D = NULL;
    }
    else
    {
        if (A->val > cle)
        {
            *D = A;
            coupure(A->FG, cle, G, &((*D)->FG));
        }
        else
        {
            *G = A;
            coupure(A->FD, cle, &((*G)->FD), D);
        }
    }
}
void *insererRacine(ArbreBin **A, int cle)
{
    ArbreBin *racine = creerFeuille(cle);
    ArbreBin *G = NULL;
    ArbreBin *D = NULL;
    coupure(*A, cle, &G, &D);
    racine->FG = G;
    racine->FD = D;
    *A = racine;
}
void supMax(ArbreBin **A, int *max)
{
    if (!(*A)->FD)
    {
        *max = (*A)->val;
        ArbreBin *tmp = *A;
        *A = (*A)->FG;
        free(tmp);
    }
    else
    {
        supMax(&((*A)->FD), max);
    }
}
void suppression(ArbreBin **A, int cle)
{
    if (*A)
    {
        if ((*A)->val > cle)
        {
            suppression(&((*A)->FG), cle);
        }
        else if ((*A)->val < cle)
        {
            suppression(&((*A)->FD), cle);
        }
        else

        {
            // 1 ou 0 fils
            if (!(*A)->FD)
            {
                ArbreBin *tmp = *A;
                *A = (*A)->FG;
                free(tmp);
            }
            // exactement un seul fils
            else if (!(*A)->FG)
            {
                ArbreBin *tmp = *A;
                *A = (*A)->FD;
                free(tmp);
            }
            // deux fils
            else
            {
                int max;
                supMax(A, &max);
                (*A)->val = max;
            }
        }
    }
}
void libererArbre(ArbreBin *P)
{
    if (P)
    {
        libererArbre(P->FG);
        libererArbre(P->FD);
        free(P);
    }
}
