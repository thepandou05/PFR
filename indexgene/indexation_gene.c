//
// AUTEUR :
//          YASMINE ALLAL
// DERNIERE VERSION :
//    12/01/2023

#include "indexation_gene.h"

//____________________________________________
// Recupere le chemin des fichiers dans DATA dans une pile
//____________________________________________
void recup_path(PILE *pourchemin, int deb, String path, String type, int *erreur)
{
      ELEMENT element;
      String nom_fic, chemin;
      char commande[500];
      FILE *ptr_fic;
      /*------------------------------------------------------*/
      /* RECUPERATION DU CONTENU DU REPERTOIRE  CHEMIN        */
      /*------------------------------------------------------*/
      strcpy(commande, "ls -l ");
      strcat(commande, path);

      if (strcmp(type, "texte") == 0) // recuperer chemin pour fichier texte
            strcat(commande, " > fic_temp");
      else // recuperer chemin pour fichier .txt audio et image
            strcat(commande, " | grep \".txt\" > fic_temp");

      printf("execution de %s\n", commande);
      fflush(stdout);

      /*---------------------------------------------------------------------*/
      /* AFFICHAGE DU CONTENU DU FICHIER CREE LORS DE LA PRECEDENTE COMMANDE */
      /*---------------------------------------------------------------------*/
      system(commande);
      system("cat fic_temp");
      printf("---------------------------------\n");

      /* ouverture du fichier temporaire fic_temp*/
      ptr_fic = fopen("fic_temp", "r");

      if (ptr_fic != NULL)
      {
            if (strcmp(type, "texte") == 0)
                  fscanf(ptr_fic, "%*s %*s"); /* SAUTER LA PREMIERE LIGNE CONSTITUEE DE 2 CHAINES total xxxx */

            fscanf(ptr_fic, "%*s %*s %*s %*s %*s %*s %*s %*s %s", nom_fic); /* %*s INGNORE LA CHAINE LUE */
            while (!feof(ptr_fic))
            {
                  strcpy(chemin, path);
                  strcat(chemin, nom_fic);
                  element.id = deb;
                  strcpy(element.CHEMIN, chemin);

                  *pourchemin = emPILE(*pourchemin, element);
                  /* nom de fichier suivant */
                  deb++;
                  fscanf(ptr_fic, "%*s %*s %*s %*s %*s %*s %*s %*s %s", nom_fic);
            }
      }
      else
      {
            *erreur = 7;
      }
      fclose(ptr_fic);
}

//____________________________________________
// depiler le chemin de le fichier liste_base_texte ou liste _base_audio ou liste_base_image
//____________________________________________
void depiler_path(PILE *pourchemin, char *path, int *erreur)
{
      ELEMENT elementsupp;
      FILE *fichier = NULL;
      fichier = fopen(path, "w");

      if (fichier != NULL)
      {
            while ((*pourchemin) != NULL)
            {
                  *pourchemin = dePILE(*pourchemin, &elementsupp);
                  fprintf(fichier, "-%d |%s\n", elementsupp.id, elementsupp.CHEMIN);
            }
      }
      else
      {
            *erreur = 7;
      }
      fclose(fichier);
}

//____________________________________________
// EMPILE LEs DESCRIPTEUR AUDIO AVEC leur ID DANS UNE PILE
//____________________________________________
PILE_audio base_descript_empiler_audio(PILE_audio dscr_audio, int *erreur, int *erreur_audio, CONFIG config)
{
      int ligne;
      FILE *ptr_fic = NULL;
      ELEMENT_audio element_temp;
      char CHEMIN[100] = "../liste_base/liste_base_audio";
      char cheminfichier[200];
      ptr_fic = fopen(CHEMIN, "r");
      if (ptr_fic != NULL)
      {
            fscanf(ptr_fic, "%d | %s\n", &element_temp.id, cheminfichier);
            ligne = getligne(cheminfichier, erreur);
            printf("ca fonctionne ? \n");
            fflush(stdout);
            element_temp.descripteur = Descripteur_audio(config.Nb_Fenetre, config.Intervale, cheminfichier, element_temp.descripteur, erreur_audio, ligne);
            printf("ca fonctionne ? \n");
            fflush(stdout);
            if (*erreur_audio == 0)
            {
                  dscr_audio = emPILE_audio(dscr_audio, element_temp);

                  while (!feof(ptr_fic))
                  {
                        fscanf(ptr_fic, "%d | %s", &element_temp.id, cheminfichier);
                        ligne = getligne(cheminfichier, erreur);
                        element_temp.descripteur = Descripteur_audio(config.Nb_Fenetre, config.Intervale, cheminfichier, element_temp.descripteur, erreur_audio, ligne);
                        if (*erreur_audio == 0)
                        {
                              dscr_audio = emPILE_audio(dscr_audio, element_temp);
                        }
                  }
            }
                        printf("ca fonctionne ? \n");
            fflush(stdout);
            fclose(ptr_fic);
      }
      else
      {
            *erreur = 7;
      }
      return dscr_audio;
}

//____________________________________________
// DEPILE LES DESCRIPTEURS AUDIO DANS LE FICHIER BASE_DESCRIPTEUR
//____________________________________________
void depiler_descripteur_audio(PILE_audio dscr_audio, int *erreur, int erreur_audio)
{
      ELEMENT_audio elementsupp;
      FILE *fichier = NULL;
      fichier = fopen("../base_descripteur/base_descripteur_audio", "w");
      if (erreur_audio == 0)
      {
            if (fichier != NULL)
            {

                  while (dscr_audio != NULL)
                  {
                        for (unsigned i = 0; i < dscr_audio->element.descripteur.ligne; ++i)
                        {
                              for (unsigned j = 0; j < dscr_audio->element.descripteur.colonne; ++j)
                              {

                                    printf("%d  ",i);
                                    printf(" %d =",j);
                                    printf(" %d \n",dscr_audio->element.descripteur.tab[i][j]);
                                    fflush(stdout);
                                    //fprintf(fichier, " |%3d| ", dscr_audio->element.descripteur.tab[i][j]);
                              }
                        }
                        dscr_audio = dePILE_audio(dscr_audio, &elementsupp);


                                  for (unsigned i = 542; i < 546; ++i)
    {
            for (unsigned j = 0; j < 32; ++j)
            {

                printf("descripteur : %d  ",i);
                printf(" %d =",j);
                printf(" %d \n",dscr_audio->element.descripteur.tab[i][j]);
                fflush(stdout);
                //fprintf(fichier, " |%3d| ", dscr_audio->element.descripteur.tab[i][j]);
            }
    }

                        //______________________________
                        // AFFICHAGE ELEMENT DANS FICHIER
                        //_______________________________
                                                  printf("test 86 \n");
                        fflush(stdout);
                        fprintf(fichier, "%d %d\n", elementsupp.id, elementsupp.descripteur.ligne);
                        printf("nbr ligne : %d \n",elementsupp.descripteur.colonne);
                        fflush(stdout);
                        for (unsigned i = 0; i < elementsupp.descripteur.ligne; ++i)
                        {
                              for (unsigned j = 0; j < elementsupp.descripteur.colonne; ++j)
                              {

                                    printf("%d  ",i);
                                    printf(" %d =",j);
                                    printf(" %d \n",elementsupp.descripteur.tab[i][j]);
                                    fflush(stdout);
                                    fprintf(fichier, " |%3d| ", elementsupp.descripteur.tab[i][j]);
                              }
                              fprintf(fichier, "\r\n");
                        }
                        printf("test 86 \n");
                        fflush(stdout);
                  }
            }
            else
            {
                  *erreur = 7;
            }
      }
      fclose(fichier);
}

//____________________________________________
// EMPILE LEs DESCRIPTEUR AUDIO AVEC leur ID DANS UNE PILE
//____________________________________________
PILE_image base_descript_empiler_image(PILE_image dscr_image, int *erreur, int *erreur_image, CONFIG config)
{
      FILE *ptr_fic = NULL;
      ELEMENT_image element_temp;
      char CHEMIN[100] = "../liste_base/liste_base_image";
      char cheminfichier[200];

      ptr_fic = fopen(CHEMIN, "r");

      if (ptr_fic != NULL)
      {
            fscanf(ptr_fic, "%d | %s\n", &element_temp.id, cheminfichier);

            element_temp.descripteur_image = Pack_Descripteur_image(erreur_image, cheminfichier, config.Nb_Bit_Fort);
            if (*erreur_image == 0)
            {
                  dscr_image = emPILE_image(dscr_image, element_temp);
                  
                  while (!feof(ptr_fic))
                  {
                        fscanf(ptr_fic, "%d | %s\n", &element_temp.id, cheminfichier);
                        element_temp.descripteur_image = Pack_Descripteur_image(erreur_image, cheminfichier, config.Nb_Bit_Fort);
                        if (*erreur_image == 0)
                        {
                              dscr_image = emPILE_image(dscr_image, element_temp);
                        }
                        else
                              break;
                  }
            }
      }
      else
      {
            *erreur = 7;
      }
      fclose(ptr_fic);
      return dscr_image;
}

//____________________________________________
// DEPILE LES DESCRIPTEURS AUDIO DANS LE FICHIER BASE_DESCRIPTEUR
//____________________________________________
void depiler_descripteur_image(PILE_image dscr_image, int erreur_image, int *erreur)
{
      ELEMENT_image elementsupp;
      FILE *fichier = NULL;
      fichier = fopen("../base_descripteur/base_descripteur_image", "w");
      int total = 0;
      if (erreur_image == 0)
      {
            if (fichier != NULL)
            {
                  while (dscr_image != NULL)
                  {
                        dscr_image = dePILE_image(dscr_image, &elementsupp);
                        //______________________________
                        // AFFICHAGE ELEMENT DANS FICHIER
                        //________________________________
                        fprintf(fichier, "\n%d\n", elementsupp.id);
                        for (int i = 0; i < elementsupp.descripteur_image.Nb_Ligne; i++)
                        {
                              // Permet d'afficher q'un certain nombre de valeur
                              fprintf(fichier, "Val n %d = %d Quantity = %d\n", i, elementsupp.descripteur_image.Bilan[i][0], elementsupp.descripteur_image.Bilan[i][1]);

                              total = total + elementsupp.descripteur_image.Bilan[i][1];
                        }
                        fprintf(fichier, "\nTotal de valeur = %d\n", total);
                  }
            }
            else
            {
                  *erreur = 7;
            }
      }

      fclose(fichier);
}

//____________________________________________
// EMPILE LEs DESCRIPTEUR AUDIO AVEC leur ID DANS UNE PILE
//____________________________________________
PILE_texte base_descript_empiler_texte(PILE_texte dscr_texte, int *erreur, CONFIG config)
{

      int Erreur = 0;
      FILE *ptr_fic = NULL;
      ELEMENT_texte element_temp;
      IMAGE img;
      char CHEMIN[100] = "../liste_base/liste_base_texte";
      char cheminfichier[200];

      ptr_fic = fopen(CHEMIN, "r");

      if (ptr_fic != NULL)
      {
            fscanf(ptr_fic, "%d | %s\n", &element_temp.id, cheminfichier);
            element_temp.descripteur_texte = descripteur_texte_finale(cheminfichier, config.Nb_Mots_Cle, element_temp.descripteur_texte);

            dscr_texte = emPILE_texte(dscr_texte, element_temp);

            while (!feof(ptr_fic))
            {
                  fscanf(ptr_fic, "%d | %s\n", &element_temp.id, cheminfichier);
                  element_temp.descripteur_texte = descripteur_texte_finale(cheminfichier, config.Nb_Mots_Cle, element_temp.descripteur_texte);
                  dscr_texte = emPILE_texte(dscr_texte, element_temp);
            }
      }
      else
      {
            *erreur = 7;
      }
      fclose(ptr_fic);
      return dscr_texte;
}

//____________________________________________
// DEPILE LES DESCRIPTEURS AUDIO DANS LE FICHIER BASE_DESCRIPTEUR
//____________________________________________
void depiler_descripteur_texte(PILE_texte dscr_texte, int *erreur, CONFIG config)
{
      ELEMENT_texte elementsupp;
      FILE *fichier = NULL;
      fichier = fopen("../base_descripteur/base_descripteur_texte", "w");
      int total = 0;
      if (fichier != NULL)
      {
            while (dscr_texte != NULL)
            {
                  dscr_texte = dePILE_texte(dscr_texte, &elementsupp);
                  //______________________________
                  // AFFICHAGE ELEMENT DANS FICHIER
                  //________________________________
                  fprintf(fichier, "%d\n", elementsupp.id);
                  // affichage descripteur
                  for (int x = 0; x < config.Nb_Mots_Cle; x++)
                  {
                        fprintf(fichier, "%s    |    %d\n", elementsupp.descripteur_texte.tab_mot[x], elementsupp.descripteur_texte.tab_app[x]);
                  }
            }
      }
      else
      {
            *erreur = 7;
      }
      fclose(fichier);
}

//____________________________________________
// Recupere le chemin de tous les fichiers audio, image, texte et le depile dans les fichiers liste_base_audio/image/texte
//____________________________________________
void recuperer_path_tous_fichiers(int *Erreurtexte, int *Erreuraudio, int *Erreurimage)
{
      PILE piletexte_path = init_PILE();
      PILE pileimage_path = init_PILE();
      PILE pileaudio_path = init_PILE();
      String commande;
      String path;
      int deb = 0;
      //_________________
      // TEXTE
      //_________________
      strcpy(path, "../DATA_FIL_ROUGE_DEV/Textes/");
      recup_path(&piletexte_path, deb, path, "texte", Erreurtexte);
      depiler_path(&piletexte_path, "../liste_base/liste_base_texte", Erreurtexte);

      strcpy(commande, "cp ../liste_base/liste_base_texte ../OLD_liste_base/liste_base_old_texte");
      printf("COMMANDE : %s\n",commande);
      system(commande);

      //_________________
      // AUDIO
      //_________________
      strcpy(path, "../DATA_FIL_ROUGE_DEV/IMG_et_AUDIO/TEST_SON/");
      recup_path(&pileaudio_path, deb, path, "audio", Erreuraudio);
      depiler_path(&pileaudio_path, "../liste_base/liste_base_audio", Erreuraudio);

      strcpy(commande, "cp ../liste_base/liste_base_audio ../OLD_liste_base/liste_base_old_audio");
      printf("COMMANDE : %s",commande);
      system(commande);

      //_________________
      // IMAGE
      //_________________
      strcpy(path, "../DATA_FIL_ROUGE_DEV/IMG_et_AUDIO/TEST_RGB/");
      recup_path(&pileimage_path, deb, path, "image", Erreurimage);
      deb = (pileimage_path->element.id) + 1;
      strcpy(path, "../DATA_FIL_ROUGE_DEV/IMG_et_AUDIO/TEST_NB/");
      recup_path(&pileimage_path, deb, path, "image", Erreurimage);
      depiler_path(&pileimage_path, "../liste_base/liste_base_image", Erreurimage);
      strcpy(commande, "cp ../liste_base/liste_base_image ../OLD_liste_base/liste_base_old_image");
      printf("COMMANDE : %s",commande);
      system(commande);
}
//
// Recuperer le nombre de ligne dans un fichier __ utlise dans le descripteur audio
//
int getligne(char *path, int *erreur)
{

      char commande[500];
      int ligne;

      strcpy(commande, "wc -l ");
      strcat(commande, path);
      strcat(commande, " > getligne_temp");
      system(commande);

      FILE *fichier = NULL;
      fichier = fopen("getligne_temp", "r"); // Ouverture du texte à traiter
      if (fichier == NULL)
      {
            // printf("Erreur lors de l'ouverture d'un fichier");
            // exit(1);
            *erreur = 7;
      }

      fscanf(fichier, "%d", &ligne);

      fclose(fichier);

      strcpy(commande, "rm ");
      strcat(commande, "getligne_temp");
      system(commande);

      return ligne;
}

void indexation_generale_ferme(CONFIG config, int *Erreurimage, int *Erreuraudio, int *Erreurtexte, int *Erreur)
{

      recuperer_path_tous_fichiers(Erreurtexte, Erreuraudio, Erreurimage);

      PILE_image pileimage = NULL;
      pileimage = base_descript_empiler_image(pileimage, Erreur, Erreurimage, config);
      depiler_descripteur_image(pileimage, *Erreurimage, Erreur);

      printf("APRES IMAGE ET AVANT AUDIO \n");
      fflush(stdout);
      PILE_audio descripteur_audio = NULL;
      descripteur_audio = base_descript_empiler_audio(descripteur_audio, Erreur, Erreuraudio, config);
      printf("test 2165 \n");
            fflush(stdout);
      depiler_descripteur_audio(descripteur_audio, Erreur, *Erreuraudio);

                                          printf("test audio \n");
            fflush(stdout);
                  printf("test ? \n");
            fflush(stdout);

      PILE_texte piletexte = NULL;
      piletexte = base_descript_empiler_texte(piletexte, Erreurtexte, config);
      depiler_descripteur_texte(piletexte, Erreurtexte, config);
}

void indexation_generale_ouverte(CONFIG config, int *Erreurimage, int *Erreuraudio, int *Erreurtexte, int *Erreur)
{

}

