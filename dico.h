#ifndef DEF_DICO //protection du préprocesseur
#define DEF_DICO
void creerDictionnaire(ArbreBin **dictionnaire, char ***motArray, int *motCount);
int piocherMot(char *motPioche);
int nombreAleatoire(int nombreMax);
void dicoInsererMot(char mot[], ArbreBin **arbre, QueueNode **queue);
#endif