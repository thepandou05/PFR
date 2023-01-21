#ifndef LIRERESULTAT_H_INCLUS    
#define LIRERESULTAT_H_INCLUS   
#include "../Pile/Pile.h"
#include "../comparaison/comparaison.h"

typedef struct {
    int id;
    int pourcentage;
}tabRes;

void LireResultat(tab_similaire*, int, char*, char*, char**,int, int, int,int*);
int lire_chemin (tab_similaire*,char**,int,char*,int,int,int, int*);
char visualiser_fichier(char **, int, char *);

#endif