#ifndef DEF_DICO //protection du préprocesseur
#define DEF_DICO
int piocherMot(char *motPioche);
int nombreAleatoire(int nombreMin,int nombreMax);
int compareStrings(const void *a, const void *b);
void sortDictionary();
void addToDictionary(const char *word);
void dicoInsererMot(char mot[], ArbreBin **arbre, QueueNode **queue);
void visualiserCaracteristiquesDictionnaire();
void creerDictionnaire(ArbreBin **dictionnaire, char ***motArray, int *motCount);
#endif