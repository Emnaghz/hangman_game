typedef struct ArbreBin
{
    char val;
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
ArbreBin *creerFeuille(char n)
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
char max2(char x, char y)
{
    if (x > y)
        return x;
    else
        return y;
}
char max3(char a, char b, char c)
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
int hauteurArbreRecur(ArbreBin *A)
{
    if ((A == NULL) || ((A->FG == NULL) && (A->FD == NULL)))
        return 0;
    else
        return 1 + max2(hauteurArbreRecur(A->FG), hauteurArbreRecur(A->FD));
}
char maximumArbre(ArbreBin *A)
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
// void afficherArbreBinaire(ArbreBin *A)
// {
//     if (A)
//     {
//         int hauteur = hauteurArbreRecur(A);

//         Queue *file = createQueue();
//         ArbreBin *delim = initArbreBin();
//         ArbreBin *blank = creerFeuille('-');

//         enqueue(file, A);
//         enqueue(file, delim);
//         int niveau = 0;
//         while (!fileEstVide(file))
//         {
//             ArbreBin *currentArbre = dequeue(file);
//             if (currentArbre != NULL)
//             {
//                 double what = pow(2, hauteur - niveau);
//                 int espaces = (int)what - 1;
//                 for (int i = 0; i < espaces; i++)
//                 {
//                     printf(" ");
//                 }
//                 if (currentArbre->val == '\0')
//                 {
//                     printf(" 0 ");
//                 }
//                 else
//                 {
//                     printf(" %c ", currentArbre->val);
//                 }
//                 for (int i = 0; i < espaces; i++)
//                 {
//                     printf(" ");
//                 }
//                 if (currentArbre->FG != NULL)
//                 {
//                     enqueue(file, currentArbre->FG);
//                     if (!currentArbre->FD)
//                     {
//                         enqueue(file, blank);
//                     }
//                 }
//                 if (currentArbre->FD != NULL)
//                 {
//                     if (!currentArbre->FG)
//                     {
//                         enqueue(file, blank);
//                     }
//                     enqueue(file, currentArbre->FD);
//                 }
//                 if (currentArbre->val != '-' && !currentArbre->FG && !currentArbre->FD)
//                 {
//                     enqueue(file, blank);
//                     enqueue(file, blank);
//                 }
//             }
//             else
//             {
//                 printf("\n");
//                 niveau++;
//                 if (!fileEstVide(file))
//                 {
//                     enqueue(file, delim);
//                 }
//             }
//         }
//     }
//     printf("\n");
// }
void parcoursInfixe(ArbreBin *A)
{
    if (A)
    {
        parcoursInfixe(A->FG);
        printf(" %c ", A->val);
        parcoursInfixe(A->FD);
    }
}
void parcoursPostfixe(ArbreBin *A)
{
    if (A)
    {
        parcoursPostfixe(A->FG);
        parcoursPostfixe(A->FD);
        printf(" %c ", A->val);
    }
}
void parcoursPrefixe(ArbreBin *A)
{
    if (A)
    {
        parcoursPrefixe(A->FG);
        parcoursPrefixe(A->FD);
        printf(" %c ", A->val);
    }
}
bool estComplet(ArbreBin *A)
{
    // la condition d'arret: un noeud a exactement un seul fils!
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
        return estComplet(A->FD) && estComplet(A->FG);
    }
}
bool rechercheArbreBin(ArbreBin *A, char x)
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
// for general purpose trees
ArbreBin *rechercheArbreBin2(ArbreBin *A, char cle, Liste **L)
{
    if (!A)
    {
        return NULL;
    }

    if (A->val == cle)
    {
        *L = ajouterElementDebut(*L, A->val);
        return A;
    }
    else
    {
        ArbreBin *gauche = rechercheArbreBin2(A->FG, cle, L);
        ArbreBin *droite = rechercheArbreBin2(A->FD, cle, L);

        if (gauche || droite)
        {
            *L = ajouterElementDebut(*L, A->val);
            return (gauche) ? gauche : droite;
        }
        else
        {
            return NULL;
        }
    }
}
ArbreBin *rechercheRecurABR(ArbreBin *A, char cle, Liste **L)
{
    if (!A)
    {
        return NULL;
    }

    *L = ajouterElementDebut(*L, A->val);

    if (A->val == cle)
    {
        return A;
    }
    else if (A->val > cle)
    {
        return rechercheRecurABR(A->FG, cle, L);
    }
    else
    {
        return rechercheRecurABR(A->FD, cle, L);
    }
}

// void noeudsdelarbre(ArbreBin *A, Liste **L)
// {
//     if (!A)
//     {
//         // Base case: A is a null node, do nothing
//     }
//     else if (!A->FD && !A->FG)
//     {
//         // Leaf node: add its value to the list
//         *L = ajouterElementDebut(*L, A->val);
//     }
//     else
//     {
//         // Internal node: recursively process the children
//         noeudsdelarbre(A->FD, L);
//         noeudsdelarbre(A->FG, L);
//     }
// }
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
void coupure(ArbreBin *A, char cle, ArbreBin **G, ArbreBin **D)
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
void *insererRacine(ArbreBin **A, char cle)
{
    ArbreBin *racine = creerFeuille(cle);
    ArbreBin *G = NULL;
    ArbreBin *D = NULL;
    coupure(*A, cle, &G, &D);
    racine->FG = G;
    racine->FD = D;
    *A = racine;
}
void *insererFeuille(ArbreBin **A, char cle)
{
    if (!(*A))
    {
        *A = creerFeuille(cle);
    }
    else
    {
        if (cle > (*A)->val)
        {
            insererFeuille(&((*A)->FD), cle);
        }
        else
        {
            insererFeuille(&((*A)->FG), cle);
        }
    }
}
void supMax(ArbreBin **A, char *max)
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
void suppression(ArbreBin **A, char cle)
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
                char max;
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
void generateMermaidNodes(ArbreBin *node, FILE *file)
{
    if (node != NULL)
    {
        // Assign a unique name to each node
        if (node->val == '\00')
        {
            fprintf(file, "  %p[%c]\n", (void *)node, '-');
        }
        else
        {
            fprintf(file, "  %p[%c]\n", (void *)node, node->val);
        }

        if (node->FG != NULL)
        {
            fprintf(file, "  %p --> %p\n", (void *)node, (void *)node->FG);
            fprintf(file, "  style %p fill:#ffaaaa,color:#000000;  \n", (void *)node->FG);
            generateMermaidNodes(node->FG, file);
        }

        if (node->FD != NULL)
        {
            fprintf(file, "  %p --> %p\n", (void *)node, (void *)node->FD);
            fprintf(file, "  style %p fill:#aaaaff,color:#000000;  \n", (void *)node->FD);

            generateMermaidNodes(node->FD, file);
        }
    }
}
void generateMermaidScript(ArbreBin *root)
{
    FILE *file = fopen("mermaid.md", "w");

    if (root == NULL)
    {
        return;
    }

    fprintf(file, "```mermaid \n graph TD;\n");
    generateMermaidNodes(root, file);
    fclose(file);
}

ArbreBin *arbreConNoeud(char val, ArbreBin *FG, ArbreBin *FD)
{
    ArbreBin *nouveauNoeud = (ArbreBin *)malloc(sizeof(ArbreBin));
    if (nouveauNoeud != NULL)
    {
        nouveauNoeud->val = val;
        nouveauNoeud->FG = FG;
        nouveauNoeud->FD = FD;
    }
    return nouveauNoeud;
}
void sousArbreDeRecherche(){
    ArbreBin *A = NULL;
    char **motArray = NULL;
    int motCount = 0;
    creerDictionnaire(&A, &motArray, &motCount);
    generateMermaidScript(A);
    // printf("that val is %d and %d",A->FD->FD->FG->FG->FD->FG->val,A->FD->FD->FG->FG->FD->FG->val=='\r');
}