#include"descripteur_audio.h"

int main()
{
  int erreur;
  descri_audio tableau;

    tableau=Descripteur_audio(4096,32,"../DATA_FIL_ROUGE_DEV/IMG_et_AUDIO/TEST_SON/jingle_fi.txt",tableau,&erreur);
    //printf("%d",erreur);
    
    for (unsigned i = 0; i < tableau.ligne; ++i)
    {
        for (unsigned j = 0; j < tableau.colonne; ++j)
        {
            printf(" |%3d| ",tableau.tab[i][j]);
        }
        printf("\r\n");
    }

    for (int i = 0; i < tableau.ligne; i++)//creation des colonne du tableau
    {
        free(tableau.tab[i]);
       //tableau.tab[i] = malloc(intervalle * sizeof(**desci.tab));
        //if(desci.tab[i]!=NULL)
        //{
         //   *erreur=1;//erreur malloc
        //}
    }
    free(tableau.tab);
}