#include "../head/Login.h"

//affiche utl et mdp 
void afficher_un_login (lesLogins tablogin, int i)
{
        printf("ID : %s\n",tablogin[i].id);
        printf("Mot de passe : %s\n",tablogin[i].mdp);
}
// afficher tous les logins
void afficher_les_login (lesLogins tablogin)
{    int i;
    for(i=0; i<5;i++)
    {
        afficher_un_login (tablogin,i);
    }
}


// entrer id
LOGIN saisir_login()
{   LOGIN login;
    printf("Enter ID : ");
    scanf(" %[^\n]", login.id);
    viderBuffer();
    printf("Enter mot de passe : ");
    scanf(" %[^\n]", login.mdp);
    viderBuffer();
    return login;
}

// importe id et mdp du fichier texte a la structure
void lire_fichier_login (lesLogins tablogin, String * erreur)
{   
    FILE *fichier = NULL;
    fichier = fopen("../Login.txt", "r");
    if (fichier != NULL)
    {
        strcpy(*erreur,"Erreur : NULL");
        fscanf(fichier, "[0] id : %s\nmdp : %s\n[1] id : %s\nmdp : %s\n[2] id : %s\nmdp : %s\n[3] id : %s\nmdp : %s\n[4] id : %s\nmdp : %s\n",tablogin[0].id,(tablogin[0].mdp),(tablogin[1].id),(tablogin[1].mdp),(tablogin[2].id),(tablogin[2].mdp),(tablogin[3].id),(tablogin[3].mdp),(tablogin[4].id),(tablogin[4].mdp) );
    }
    else
    {
        strcpy(*erreur,"Erreur : Fichier login introuvable");
    }
    fclose(fichier); 
}


/* // remplie le fichier texte avec la structure 
void remplir_fichier_login (lesLogins tablogin, String *erreur)
{
    FILE *fichier =NULL;
    fichier = fopen("../Login.txt","w");
    if (fichier != NULL)
    {
        strcpy(*erreur,"Erreur : NULL");
        fprintf(fichier, "[0] id : %c\nmdp : %c\n[1] id : %c\nmdp : %c\n[2] id : %c\nmdp : %c\n[3] id : %c\nmdp : %c\n[4] id : %c\nmdp : %c\n",tablogin[0].id,tablogin[0].mdp,tablogin[1].id,tablogin[1].mdp,(tablogin[2].id),(tablogin[2].mdp),(tablogin[3].id),(tablogin[3].mdp),tablogin[4].id,(tablogin[4].mdp) );
    }
    else
    {
        strcpy(*erreur,"Erreur : Fichier login introuvable");
    }
} */
