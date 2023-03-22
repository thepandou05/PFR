
#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include "Menu.h"
#include "../chemin.h"

chaine_typ lire_fichier()
{
    char *ptr;
    chaine_typ chaine;
    FILE *fichier = NULL;
    fichier = fopen("../../pont/pontJavaC.txt", "r");
    if (fichier != NULL)
    {

        while (fscanf(fichier, "%s\n", chaine.entiere) != EOF)
        {

            if (chaine.entiere != NULL)
            {
                ptr = strchr(chaine.entiere, '(');
                char temp[100];
                strcpy(temp, chaine.entiere);
                strcpy(&temp[strlen(chaine.entiere) - strlen(ptr)], "\0");
                strcpy(chaine.fonction, temp);
            }
        }
    }
    fclose(fichier);
    return (chaine);
}

void choixfonction()
{
    chaine_typ etat_courant = lire_fichier();
    //  variables a utiliser au cours du programme
    char chemin[100];
    tab_similaire tabResultat[3];
    char requete[100];
    int erreur = 0;
    int nombreElemetTab = 0;
    CONFIG config;
    char cheminDescripteurTxt[200] = BASE_TXT;
    char cheminDescripteurIMG[100] = BASE_IMG;
    char cheminDescripteurAudio[100] = BASE_AUD;
    config = Lire_CONFIG(&erreur);
    int erreurImage = 0, erreurAudio = 0, erreurTexte = 0, erreurIndex = 0;

    if (strcmp(etat_courant.fonction, "indexationGeneraleFerme") == 0)
    {
        indexation_generale_ferme(config, &erreurImage, &erreurAudio, &erreurTexte, &erreurIndex);
        ecrireCJava(NULL, 0, erreurImage, erreurAudio, erreurTexte, erreurIndex);
    }
    else if (strcmp(etat_courant.fonction, "systemTexte") == 0)
    {
        strcpy(requete, "chmod a-w ");
        strcat(requete, BASE_TXT);
        system(requete);
        strcpy(requete, "gedit ");
        strcat(requete, BASE_TXT);
        system(requete);
        strcpy(requete, "chmod 777 ");
        strcat(requete, BASE_TXT);
        system(requete);
    }
    else if (strcmp(etat_courant.fonction, "systemImage") == 0)
    {
        strcpy(requete, "chmod a-w ");
        strcat(requete, BASE_IMG);
        system(requete);
        strcpy(requete, "gedit ");
        strcat(requete, BASE_IMG);
        system(requete);
        strcpy(requete, "chmod 777 ");
        strcat(requete, BASE_IMG);
        system(requete);
    }
    else if (strcmp(etat_courant.fonction, "systemAudio") == 0)
    {
        strcpy(requete, "chmod a-w ");
        strcat(requete, BASE_AUD);
        system(requete);
        strcpy(requete, "gedit ");
        strcat(requete, BASE_AUD);
        system(requete);
        strcpy(requete, "chmod 777 ");
        strcat(requete, BASE_AUD);
        system(requete);
    }
    else if (strcmp(etat_courant.fonction, "rechercheMot") == 0)
    {
        char motCle[27];
        sscanf(etat_courant.entiere, "%12s(%s)", etat_courant.fonction, motCle);
        strcpy(&motCle[strlen(motCle) - 1], "\0");
        erreur = 0;
        tab_similaire *tabResultatMot = malloc(100 * sizeof(tab_similaire));
        rechercheMot(motCle, cheminDescripteurTxt, tabResultatMot, config.Nb_Mots_Cle, &nombreElemetTab, &erreur);
        ecrireCJava(tabResultatMot, nombreElemetTab, erreurImage, erreurAudio, erreurTexte, erreurIndex);
        free(tabResultatMot);
    }
    //"comparaisonTexte()"
    else if (strcmp(etat_courant.fonction, "comparaisonTexte") == 0)
    {
        sscanf(etat_courant.entiere, "%16s(%s)", etat_courant.fonction, chemin);
        strcpy(&chemin[strlen(chemin) - 1], "\0");
        erreur = 0, nombreElemetTab = 0;
        tab_similaire *tabResultatTexte = malloc(100 * sizeof(tab_similaire));
        tabResultatTexte = comparaison_texte(config.Nb_Mots_Cle, chemin, cheminDescripteurTxt, &erreur, &nombreElemetTab);
        ecrireCJava(tabResultatTexte, nombreElemetTab, erreurImage, erreurAudio, erreurTexte, erreurIndex);
        free(tabResultatTexte);
    }
    else if (strcmp(etat_courant.fonction, "comparaisonDescripteurImage") == 0)
    {
        sscanf(etat_courant.entiere, "%27s(%s)", etat_courant.fonction, chemin);
        strcpy(&chemin[strlen(chemin) - 1], "\0");
        erreur = 0, nombreElemetTab = 0;
        tab_similaire *tabResultatIMG;
        tabResultatIMG = Comparaison_descripteur_image(&erreur, cheminDescripteurIMG, chemin, config.Nb_Bit_Fort, &nombreElemetTab);
        ecrireCJava(tabResultatIMG, nombreElemetTab, erreurImage, erreurAudio, erreurTexte, erreurIndex);
        free(tabResultatIMG);
    }

    else if (strcmp(etat_courant.fonction, "comparaisonAudio") == 0)
    {
        sscanf(etat_courant.entiere, "%16s(%s)", etat_courant.fonction, chemin);
        strcpy(&chemin[strlen(chemin) - 1], "\0");
        erreur = 0;
        nombreElemetTab = 0;
        tab_similaire *tabResultatAudio = malloc(100 * sizeof(tab_similaire));
        tabResultatAudio = comparaison_audio(config.Nb_Fenetre, config.Intervale, chemin, cheminDescripteurAudio, &erreur, &nombreElemetTab);
        ecrireCJava(tabResultatAudio, nombreElemetTab, erreurImage, erreurAudio, erreurTexte, erreurIndex);
        free(tabResultatAudio);
    }
    else if ( (strcmp(etat_courant.fonction, "indexation") == 0))
    {
        indexation(config,&erreurImage,&erreurAudio,&erreurTexte,&erreurIndex);
        if (erreurImage != 0 || erreurAudio != 0 || erreurTexte != 0 || erreurIndex != 0)
        {
            ecrireCJava(NULL, 0, erreurImage, erreurAudio, erreurTexte, erreurIndex);
        }
    }
    /*else if (strcmp(etat_courant.fonction, "indexationOuverte") == 0)
    {
        ecrireCJava(NULL, 0, erreurImage, erreurAudio, erreurTexte, erreurIndex);
        indexation_ouverte(config, "rgb", &erreurImage, &erreurAudio, &erreurTexte, &erreurIndex);
        if (erreurImage != 0 || erreurAudio != 0 || erreurTexte != 0 || erreurIndex != 0)
        {
            ecrireCJava(NULL, 0, erreurImage, erreurAudio, erreurTexte, erreurIndex);
        }
        indexation_ouverte(config, "nb", &erreurImage, &erreurAudio, &erreurTexte, &erreurIndex);
        if (erreurImage != 0 || erreurAudio != 0 || erreurTexte != 0 || erreurIndex != 0)
        {
            ecrireCJava(NULL, 0, erreurImage, erreurAudio, erreurTexte, erreurIndex);
        }
        indexation_ouverte(config, "texte", &erreurImage, &erreurAudio, &erreurTexte, &erreurIndex);
        if (erreurImage != 0 || erreurAudio != 0 || erreurTexte != 0 || erreurIndex != 0)
        {
            ecrireCJava(NULL, 0, erreurImage, erreurAudio, erreurTexte, erreurIndex);
        }
        indexation_ouverte(config, "audio", &erreurImage, &erreurAudio, &erreurTexte, &erreurIndex);
        if (erreurImage != 0 || erreurAudio != 0 || erreurTexte != 0 || erreurIndex != 0)
        {
            ecrireCJava(NULL, 0, erreurImage, erreurAudio, erreurTexte, erreurIndex);
        }
    }*/
}
