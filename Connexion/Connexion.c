#include "../Connexion/Connexion.h"

bool seconnecter (lesLogins tablogin, LOGIN newlogin, int *erreur)
{   int i ;
    newlogin=saisir_login();
    lire_fichier_login(tablogin,erreur);
    if(*erreur!=0 || *erreur!=7){
     for(i=0; i<5;i++)
      {

          if (!strcmp(tablogin[i].id,newlogin.id) & !strcmp(tablogin[i].mdp,newlogin.mdp) )
            { 
              return true;
            }
      }
      return false;}
    else{
      //erreur
    }

}