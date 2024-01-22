#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "dico.h"
int piocherMot(char *motPioche)
{
    FILE *dico = NULL; // Le pointeur de fichier qui va contenir notre fichier
    int nombreMots = 0, numMotChoisi = 0, i = 0;
    int caractereLu = 0;
    dico = fopen("dictionnaire.txt", "r"); // On ouvre le dictionnaire en lecture seule
    // On vérifie si on a réussi à ouvrir le dictionnaire
    if (dico == NULL) // Si on n'a PAS réussi à ouvrir le fichier
    {
        printf("\nImpossible de charger le dictionnaire de mots");
        return 0; // On retourne 0 pour indiquer que la fonction a échoué
        // À la lecture du return, la fonction s'arrête immédiatement.
    }
    // On compte le nombre de mots dans le fichier (il suffit de compter les
    // entrées \n
    do
    {
        caractereLu = fgetc(dico);
        if (caractereLu == '\n')
            nombreMots++;
    } while (caractereLu != EOF);
    numMotChoisi = nombreAleatoire(0,nombreMots); // On pioche un mot au hasard                                          // On recommence à lire le fichier depuis le début. On s'arrête lorsqu'on est arrivé au bon mot
    printf("\n le num choisi est %d: \n", numMotChoisi);
    rewind(dico);
    while (numMotChoisi > 0)
    {
        caractereLu = fgetc(dico);
        if (caractereLu == '\n')
            numMotChoisi--;
    }
    /* Le curseur du fichier est positionné au bon endroit.
    On n'a plus qu'à faire un fgets qui lira la ligne */
    fgets(motPioche, 100, dico);
    printf("\n le mot pioche est %s: \n", motPioche);

    // On vire le \n à la fin
    motPioche[strlen(motPioche) - 1] = '\0';
    printf("\n le mot pioche est apres trans %s: \n", motPioche);

    fclose(dico);
    return 1; // Tout s'est bien passé, on retourne 1
}
int nombreAleatoire(int nombreMin,int nombreMax)
{
    srand(time(NULL));
    return (rand() % (nombreMax - nombreMin + 1)) + nombreMin;
}
int compareStrings(const void *a, const void *b)
{
    return strcmp(*(const char **)a, *(const char **)b);
}
void sortDictionary()
{
    FILE *file = fopen("dictionnaire.txt", "r");
    if (file == NULL)
    {
        printf("Error opening the file for reading.\n");
        // Handle the error appropriately
        return;
    }

    char **words = NULL;
    char word[1000];

    // Read words into an array
    int wordCount = 0;
    while (fgets(word, 1000, file) != NULL)
    {
        // Remove newline character
        word[strcspn(word, "\n")] = '\0';

        // Allocate memory for the word and copy it
        char *newWord = strdup(word);

        // Resize the array
        words = (char **)realloc(words, (wordCount + 1) * sizeof(char *));
        if (words == NULL)
        {
            printf("Memory allocation error.\n");
            // Handle the error appropriately
            fclose(file);
            return;
        }

        // Add the word to the array
        words[wordCount] = newWord;
        wordCount++;
    }

    fclose(file);

    // Sort the array
    qsort(words, wordCount, sizeof(char *), compareStrings);

    // Open the file for writing (overwrite)
    file = fopen("dictionnaire.txt", "w");
    if (file == NULL)
    {
        printf("Error opening the file for writing.\n");
        return;
    }

    // Write the sorted words to the file
    for (int i = 0; i < wordCount; i++)
    {
        fprintf(file, "%s\n", words[i]);
        // Free memory allocated for each word
        free(words[i]);
    }

    // Free memory allocated for the array
    free(words);

    fclose(file);
}
void addToDictionary(const char *word)
{
    FILE *file = fopen("dictionnaire.txt", "a");

    if (file != NULL)
    {
        fprintf(file, "%s\n", word);
        fclose(file);
    }
    else
    {
        printf("Error opening the file for writing.\n");
        // Handle the error appropriately
    }
    sortDictionary();
}
void dicoInsererMot(char mot[], ArbreBin **arbre, QueueNode **queue)
{
    if (*arbre != NULL)
    /*si l'arbre n'est pas vide*/
    {
        if (mot[0] != '\0')
        /*on teste si la premiemre valeur egale au premier char de mot*/
        {
            if ((*arbre)->val == mot[0])
            {
                /*si egale Incrémente la position du pointeur dans la chaîne de caractères mot. */
                mot++;

                /*et fait l'appelle recursive du fonction sur la fils gauche*/
                dicoInsererMot(mot, &((*arbre)->FG), queue);
            }
            else
            {
                /*si l'arbre a un fils droite on cherche le char*/
                if ((*arbre)->FD != NULL)
                {
                    /*on fait l'appel recursive de la fonction sur la fils droite*/
                    dicoInsererMot(mot, &((*arbre)->FD), queue);
                }
                else
                { /*si l'arbre vide on fait l'app au fonction arbreConNoeud pour on instialise l'arbre*/
                    (*arbre)->FD = arbreConNoeud(mot[0], NULL, NULL);
                    dicoInsererMot(mot, &(*arbre), queue); /*et on fait l app recursive au fonction pour isererer d'autre char */
                }
            }
        }
        /*si le mot n'est pas inserer dans l'arbre on fait l'appel au fonction arbreConNoeud  pour insialiser une mot dans une arbre*/
        else if ((*arbre)->val != '\0' && mot[0] == '\0')
        {
            ArbreBin *a = arbreConNoeud('\0', NULL, *arbre);
            *arbre = a;
        }
    }
    else
    {
        if (mot[0] != '\0' && mot[0] != '\r')
        /*si toute le mot n'est pas  inserer */
        { /*on fait l'appel recursiv sur la fils gauche pour inserer les autres char*/
            *arbre = arbreConNoeud(mot[0], NULL, NULL);
            mot++;
            dicoInsererMot(mot, &((*arbre)->FG), queue);
        }

        /*sinon on insere /0 donc on a inserer tout les chars*/
        else
        {
            *arbre = arbreConNoeud('\0', NULL, NULL);
        }
    }
}
void creerDictionnaire(ArbreBin **dictionnaire, char ***motArray, int *motCount)
{
    FILE *dico = fopen("dictionnaire.txt", "r");
    if (dico == NULL)
    {
        printf("\nImpossible de charger le dictionnaire de mots");
        return;
    }

    char mot[100];

    // Count the number of words in the file
    *motCount = 0;
    while (fgets(mot, sizeof(mot), dico) != NULL)
    {
        (*motCount)++;
    }

    // Allocate memory for the dynamic array
    *motArray = (char **)malloc(*motCount * sizeof(char *));
    if (*motArray == NULL)
    {
        printf("\nMemory allocation error");
        fclose(dico);
        return;
    }

    // Rewind the file to the beginning
    rewind(dico);

    // Read each word from the file and insert it into the tree and array
    for (int i = 0; i < *motCount; i++)
    {
        (*motArray)[i] = (char *)malloc(100 * sizeof(char)); // Assuming the maximum word length is 100
        if ((*motArray)[i] == NULL)
        {
            printf("\nMemory allocation error");
            fclose(dico);

            // Free the allocated memory before returning
            for (int j = 0; j < i; j++)
            {
                free((*motArray)[j]);
            }
            free(*motArray);

            return;
        }

        fgets((*motArray)[i], 100, dico);

        // Remove newline character at the end
        (*motArray)[i][strcspn((*motArray)[i], "\n")] = '\0';

        // Insert the word into the dictionary tree
        dicoInsererMot((*motArray)[i], dictionnaire, NULL);
    }

    fclose(dico);
    sortDictionary();
}
void visualiserCaracteristiquesDictionnaire() {
    FILE *file = fopen("dictionnaire.txt", "r");
    if (file == NULL) {
        printf("Error: File '%s' not found.\n", "dictionnaire.txt");
        return;
    }

      int total_words = 0;
    int total_characters = 0;
    int shortest_length = -1;
    int longest_length = -1;
    int word_count_by_length[20] = {0};  // Assuming words have lengths between 1 and 20 characters

    char buffer[100]; 

    while (fscanf(file, "%s", buffer) == 1) {
        int length = strlen(buffer);
        total_words++;
        total_characters += length;

        if (shortest_length == -1 || length < shortest_length) {
            shortest_length = length;
        }

        if (length > longest_length) {
            longest_length = length;
        }

        if (length >= 1 && length <= 9) {
            word_count_by_length[length - 1]++;
        }
    }

    fclose(file);

    double average_length = total_characters / (double)total_words;

    // Customize each line separately
    printf("\nStatistiques du dictionnaire :\n");
    printf("==============================\n");
    printf("Nombre total de mots           : \x1b[32m%d\x1b[0m\n", total_words);  // Green color
    printf("Longueur moyenne des mots      : \x1b[34m%.2f\x1b[0m caractères\n", average_length);  // Blue color
    printf("Longueur du mot le plus court  : \x1b[31m%d\x1b[0m caractères\n", shortest_length);  // Red color
    printf("Longueur du mot le plus long   : \x1b[33m%d\x1b[0m caractères\n", longest_length);  // Yellow color

    // Additional statistics
    printf("\nNombre de mots par longueur   :\n");
    for (int i = 0; i < 9; i++) {
        if( word_count_by_length[i] != 0)
            printf("   Longueur %d caractères    : %d mots\n", i + 1, word_count_by_length[i]);
    }

    printf("==============================\n\n");
}