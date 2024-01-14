typedef struct ArbreNaire
{
    char data;
    struct ArbreNaire **enfants;
    int nenfants;
} ArbreNaire;
ArbreNaire *initArbreNaire(char data, int nenfants)
{
    ArbreNaire *node = (ArbreNaire *)malloc(sizeof(ArbreNaire));
    if (node != NULL)
    {
        node->data = data;
        node->nenfants = nenfants;
        node->enfants = (ArbreNaire **)malloc(nenfants * sizeof(ArbreNaire *));
        for (int i = 0; i < nenfants; i++)
        {
            node->enfants[i] = NULL;
        }
    }
    return node;
}

typedef struct NoeudFile
{
    ArbreNaire *arbre;
    struct NoeudFile *suiv;
} NoeudFile;
typedef struct FileArbre
{
    NoeudFile *tete;
    NoeudFile *queue;
} FileArbre;
NoeudFile *creerNoeudFile(ArbreNaire *arbre)
{
    NoeudFile *newNode = (NoeudFile *)malloc(sizeof(NoeudFile));
    newNode->arbre = arbre;
    newNode->suiv = NULL;
    return newNode;
}
FileArbre *creerFile()
{
    FileArbre *file = (FileArbre *)malloc(sizeof(FileArbre));
    file->tete = NULL;
    file->queue = NULL;
    return file;
}
void enfiler(FileArbre *queue, ArbreNaire *arbre)
{
    NoeudFile *newNode = creerNoeudFile(arbre);
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
ArbreNaire *defiler(FileArbre *file)
{
    if (file->tete == NULL)
    {
        return NULL;
    }
    ArbreNaire *arbre = file->tete->arbre;
    file->tete = file->tete->suiv;
    if (file->tete == NULL)
    {
        file->queue = NULL;
    }
    return arbre;
}
void afficherFileNaire(FileArbre *file)
{
    NoeudFile *tmp = file->tete;
    while (tmp != NULL)
    {
        printf("%d   | ", tmp->arbre->data);
        tmp = tmp->suiv;
    }
}
int fileEstVideNaire(FileArbre *file)
{
    return (file->tete == NULL);
}
bool estFeuille(ArbreNaire *A){
    if (!A->nenfants) return true;
    else return false;
}
void afficherArbreNaire(ArbreNaire *A){
    if (A){
        for (int i = 0; i < A->nenfants; i++)
        {
            afficherArbreNaire(A->enfants[i]);
            
        }
        printf("%c ",A->data);
    }
}
void afficherArbreNaireBFS(ArbreNaire *A)
{
    if (A)
    {

        FileArbre *file = creerFile();
        ArbreNaire *delim = NULL;

        enfiler(file, A);
        enfiler(file, delim);
        int niveau = 0;
        while (!fileEstVideNaire(file))
        {
            ArbreNaire *currentArbre = defiler(file);
            if (currentArbre != NULL)
            {
                printf(" %c ", currentArbre->data);
            
                for (int i = 0; i < currentArbre->nenfants; i++)
                {
                    if (currentArbre->enfants[i]){
                        enfiler(file,currentArbre->enfants[i]);
                    }
                }
            }
            else
            {
                printf("\n");
                niveau++;
                if (!fileEstVideNaire(file))
                {
                    enfiler(file, delim);
                }
            }
        }
    }
    printf("\n");
}
ArbreNaire *genererNABR()
{
    ArbreNaire *dictionnaire;
    FILE *file = fopen("dictionnaire.txt", "r");
    char ligne[100];
    int i = 0;
    char c;
    while (fgets(ligne, sizeof(ligne), file) != NULL)
    {
        ligne[strcspn(ligne, "\n")] = '\0';
        c=ligne[0]; //première lettre
        
        
        
    }
    fclose(file);
    return dictionnaire;
}


void testNaire()
{
    ArbreNaire *A = initArbreNaire('c', 3);
    A->enfants[0] = initArbreNaire('a', 2);
    A->enfants[1] = initArbreNaire('b', 0);
    A->enfants[2] = initArbreNaire('d', 0);
    A->enfants[0]->enfants[0]=initArbreNaire('x', 0);
    A->enfants[0]->enfants[1]=initArbreNaire('y', 0);
    //affichage de l'arbre N-aire avec un parcours en largeur
    afficherArbreNaireBFS(A);

}
