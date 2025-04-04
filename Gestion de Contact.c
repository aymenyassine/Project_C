
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100
//variable global
int choix;
char nom[MAX], prenom[MAX], mail[MAX];
double num;
char nom_specifie[MAX], groupe[MAX];
//structure
typedef struct contact{
    char nom[MAX], prenom[MAX], mail[MAX], groupe[MAX];
    double num;
    struct contact *suivant, *precedant;
} contact;


//creer un noeud
contact* creation(contact *nv, char *nom, char *prenom, char *mail, double num, char *groupe){
    nv = malloc(sizeof(contact));
    if(nv == NULL){
        printf("erreur memoire\n");
        exit(1);
    } else {
        strcpy(nv->nom, nom);
        strcpy(nv->prenom, prenom);
        strcpy(nv->mail, mail);
        nv->num = num;
        strcpy(nv->groupe, groupe);
        nv->suivant = nv->precedant = nv;
    }
    return nv;
}

// Fonction d'ajout d'un contact au debut de la liste
contact* ajout_au_debut(contact *tete, contact *nv) {
    if (tete == NULL) {
        tete = nv;
    } else {
        nv->suivant = tete;
        tete->precedant = nv;
        tete = nv;
    }
    printf("Contact ajoute au debut de la liste\n");
    return tete;
}


//ajouter au fin
contact *ajouter_au_fin(contact *tete, contact *nv){
    if(tete == NULL){
        tete = nv;
    } else {
        contact *ptr = tete;
        nv->suivant = tete;
        nv->precedant = tete->precedant;
        ptr->precedant = nv;
        ptr->precedant->suivant = nv;
    }
    printf("Contact ajoute a la fin de la liste\n");
    return tete;
}

//Ajout apres un contact specifique
contact *ajouter_au_millieu(contact *tete, contact *nv, char *nom){
    contact *ptr = tete;
    if(tete == NULL){
        printf("Liste de contact est vide\n");
        printf("Vous voulez ajouter ou Non\n");
        printf("1.Oui\n");
        printf("2.Nom\n");
        scanf("%d", &choix);
        switch (choix){
            case 1:
            
                tete = ajout_au_debut(tete, nv);
                break;
            case 2:
                exit(1);
                break;
            default:
                printf("Choix invalide\n");
                exit(1);
                break;
        }
    } else if(tete->suivant == tete && strcmp(tete->nom, nom) == 0){
        tete = ajouter_au_fin(tete, nv);
    } else {
          do{
            if(strcmp(ptr->nom, nom) == 0){
                nv->suivant = ptr->suivant;
                nv->precedant = ptr;
                nv->suivant->precedant = nv;
                ptr->suivant = nv;
            }
           ptr = ptr->suivant;
        }while(ptr->suivant != tete);
    }
    printf("Contact ajoute apres un contact specifique\n");
    return tete;
}

//recherhce d'un contact par nom et prenom
void recherche_par_nom(contact *tete, char *nom_r, char *prenom_r){
    int trouve = 0;
    contact *ptr = tete;
    if(tete == NULL){
        printf("Liste Vide\n");
        exit(1);
    } else {
         do{
            if(strcmp(ptr->nom, nom_r) == 0 && strcmp(ptr->prenom, prenom_r) == 0){
                printf("+------------------------+------------------------+------------------------+------------------------+------------------------+\n");
                printf("|          Nom           |         Prenom         |  Numero de telephone   |         E-mail         |         Groupe         |\n");
                printf("+------------------------+------------------------+------------------------+------------------------+------------------------+\n");
                printf("|%23s |%23s |%23.0lf |%23s |%23s |\n", ptr->nom, ptr->prenom, ptr->num, ptr->mail, ptr->groupe);
                printf("+------------------------+------------------------+------------------------+------------------------+------------------------+\n");
                trouve = 1;
            }
           ptr = ptr->suivant;
        }while(ptr->suivant != tete);
    }
    if(trouve == 0){
        printf("Il y a aucun contact nomme par : %s %s\n", nom_r, prenom_r);
        exit(1);
    }
}

// recherch par mail

void recherche_par_mail(contact *tete, char *mail_r) {
    int trouve = 0;
    contact *ptr = tete;
    if(tete == NULL){
        printf("Liste Vide\n");
        exit(1);
    } else {
        do {
            if(strcmp(ptr->mail, mail_r) == 0){
                printf("+------------------------+------------------------+------------------------+------------------------+------------------------+\n");
                printf("|          Nom           |         Prenom         |  Numero de telephone   |         E-mail         |         Groupe         |\n");
                printf("+------------------------+------------------------+------------------------+------------------------+------------------------+\n");
                printf("|%23s |%23s |%23.0lf |%23s |%23s |\n", ptr->nom, ptr->prenom, ptr->num, ptr->mail, ptr->groupe);
                printf("+------------------------+------------------------+------------------------+------------------------+------------------------+\n");
                trouve = 1;
            }
            ptr = ptr->suivant;
        } while(ptr->suivant != tete);
    }
    if(trouve == 0){
        printf("Il n'y a aucun contact contenant ce mail : %s\n", mail_r);
        exit(1);
    }
}


//recherch par num
void recherche_par_num(contact *tete, double num_r) {
    int trouve = 0;
    contact *ptr = tete;
    if(tete == NULL){
        printf("Liste Vide\n");
        exit(1);
    } else {
        do {
            if(ptr->num == num_r){
                printf("+------------------------+------------------------+------------------------+------------------------+------------------------+\n");
                printf("|          Nom           |         Prenom         |  Numero de telephone   |         E-mail         |         Groupe         |\n");
                printf("+------------------------+------------------------+------------------------+------------------------+------------------------+\n");
                printf("|%23s |%23s |%23.0lf |%23s |%23s |\n", ptr->nom, ptr->prenom, ptr->num, ptr->mail, ptr->groupe);
                printf("+------------------------+------------------------+------------------------+------------------------+------------------------+\n");
                trouve = 1;
            }
            ptr = ptr->suivant;
        } while(ptr->suivant != tete);
    }
    if(trouve == 0){
        printf("Il n'y a aucun contact contenant ce numero : %lf\n", num_r);
        exit(1);
    }
}


//supprimer un contact au debut
contact *supprimer_au_debut(contact *tete){
    if(tete == NULL){
        printf("Liste Vide\n");
        exit(1);
    } else if(tete->suivant == tete){
        free(tete);
        tete = NULL;
    } else {
        contact *ptr = tete;
        ptr->precedant->suivant = ptr->suivant;
        ptr->suivant->precedant = ptr->precedant;
        tete = ptr->suivant;
        free(ptr);
    }
    printf("Contact supprime au debut de la liste\n");
    return tete;
}

//supprimer un contact au fin
contact *supprimer_au_fin(contact *tete){
    if(tete == NULL){
        printf("Liste Vide\n");
        exit(1);
    } else if(tete->suivant == tete){
        free(tete);
        tete = NULL;
    } else {
        contact *ptr = tete->precedant;
        ptr->precedant->suivant = ptr->suivant;
        ptr->suivant->precedant = ptr->precedant;
        free(ptr);
    }
    printf("Contact supprime a la fin de la liste\n");
    return tete;
}

//Suppression apres un contact specifique
contact* supprimer_apres_contact_specifique(contact *tete, char *nom_r, char *prenom_r){
    int trouve = 0;
    contact *ptr = tete;
    if(tete == NULL){
        printf("Liste Vide\n");
        exit(1);
    } else if(tete->suivant == tete){
            printf("Il y a que un seul contact dans la liste\n");
            exit(1);
    } else {
          do{
            if(strcmp(ptr->nom, nom_r) == 0 && strcmp(ptr->prenom, prenom_r) == 0){
                    ptr->suivant = ptr->suivant->suivant;
                    ptr->suivant->suivant->precedant = ptr;
                trouve = 1;
            }
           ptr = ptr->suivant;
        }while(ptr->suivant != tete);
        if(trouve == 0){
            printf("+------------------------------------------------------------+\n");
            printf("Il y a aucun contact nomme par : %s %s\n", nom_r, prenom_r);
            printf("+------------------------------------------------------------+\n");
            exit(1);
        }
    }
    printf("Contact supprime apres un contact specifique\n");
    return tete;
}
// sauvegarde dans un dossier externe
void sauvegarde_contacts(contact *tete){
    contact *ptr = tete;
    FILE *fichier = fopen("Contact.txt", "a");  // Ouvre le fichier en mode ecriture
    if (fichier == NULL) {
        printf("+------------------------------------------------------------+\n");
                     printf("Erreur lors de l'ouverture du fichier.\n");
        printf("+------------------------------------------------------------+\n");
        exit(0);
    }
    if(ptr == NULL){
        fprintf(fichier,"+------------------------+------------------------+------------------------+------------------------+------------------------+\n");
        fprintf(fichier,"|          Nom           |         Prenom         |  Numero de telephone   |         E-mail         |         Groupe         |\n");
        fprintf(fichier,"+------------------------+------------------------+------------------------+------------------------+------------------------+\n");
        printf("Liste Vide\n");
       exit(1);
    }
    do{
        fprintf(fichier,"|%23s |%23s |if |%23s |%23s |\n", ptr->nom, ptr->prenom, ptr->num, ptr->mail, ptr->groupe);
        fprintf(fichier,"+------------------------+------------------------+------------------------+------------------------+------------------------+\n");
        ptr = ptr->suivant;
    } while(ptr != tete);
    fclose(fichier);  // Ferme le fichier
    printf("+------------------------------------------------------+\n");
    printf("La boucle a ete sauvegardee dans le fichier avec succes.\n");
    printf("+------------------------------------------------------+\n");
}

//modifier nom et prenom de contact
contact *modifier_nom(contact *tete, char *nv_nom, char *nv_prenom){
    int trouve = 0;
    contact *ptr = tete;
    if(tete == NULL){
        printf("Liste Vide\n");
        exit(1);
    } else {
         do{
            if(strcmp(ptr->nom, nv_nom) == 0 && strcmp(ptr->prenom, nv_prenom) == 0){
                printf("+---------------------------+\n");
                  printf("Entrer nouveau nom:\n");
                  scanf("%s",ptr->nom);
                  printf("+-----------------------------+");
                  printf("Entrer nouveau prenom:\n");
                  scanf("%s",ptr->prenom);
                 printf("+------------------------------+");
                    printf("Modifier par succes\n");
                  printf("+------------------------------+");  
                trouve = 1;
            }
           ptr = ptr->suivant;
        }while(ptr->suivant != tete);
    }
    if(trouve == 0){
        printf("+------------------------------------------------------------+\n");
        printf("Il y a aucun contact nomme par : %s %s\n", nv_nom, nv_prenom);
        printf("+------------------------------------------------------------+\n");
        exit(1);
    }
    printf("+---------------------------+\n");
    printf("Modification par succes\n");
    printf("+---------------------------+\n");
    return tete;
}

//modifier mail de contact
contact *modifier_mail(contact *tete, char *nv_nom, char *nv_prenom){
    contact *ptr = tete;
    int trouve = 0;
    if(tete == NULL){
        printf("Liste Vide\n");
        exit(1);
    } else {
          do{
            if(strcmp(ptr->nom, nv_nom) == 0 && strcmp(ptr->prenom, nv_prenom) == 0){ 
                printf("+---------------------------+\n");    
                printf("Entrer nouveau mail:\n");
                gets(ptr->mail);
                printf("+---------------------------+\n");
                printf("Modifier par succes\n");
                printf("+---------------------------+\n");
                trouve = 1;
            }
             ptr = ptr->suivant;
        }while(ptr->suivant != tete);
    }
    if(trouve == 0){
        printf("+------------------------------------------------------------+\n");
        printf("Il y a aucun contact nomme par : %s %s\n", nv_nom, nv_prenom);
        printf("+------------------------------------------------------------+\n");
        exit(1);
    }
    printf("Modification par succes\n");
    return tete;
}

//modifier num de contact
contact *modifier_num(contact *tete, char *nv_nom, char *nv_prenom){
    int trouve = 0;
    contact *ptr = tete;
    if(tete == NULL){
        printf("Liste Vide\n");
        exit(1);
    } else {
          do{
            if(strcmp(ptr->nom, nv_nom) == 0 && strcmp(ptr->prenom, nv_prenom) == 0){
                printf("+---------------------------+\n");
                  printf("Entrer nouveau num:\n");
                  scanf("%lf", &ptr->num);
                  printf("+---------------------------+\n");
                    printf("+---------------------------+\n");
                      printf("Modifier par succes\n");
                    printf("+---------------------------+\n");
                trouve = 1;
            }
           ptr = ptr->suivant;
        }while(ptr->suivant != tete);
    }
    if(trouve == 0){
        printf("+------------------------------------------------------------+\n");
        printf("Il y a aucun contact nomme par : %s %s\n", nv_nom, nv_prenom);
        printf("+------------------------------------------------------------+\n");
        exit(1);
    }
    printf("Modification par succes\n");
    return tete;
}

//modifier tous les information
contact *modifier_tous(contact *tete, char *nv_nom, char *nv_prenom){
    int trouve = 0;
    contact *ptr = tete;
    if(tete == NULL){
        printf("+---------------------------+\n");
        printf("Liste Vide\n");
        printf("+---------------------------+\n");
        exit(1);
    } else {
        do{
         
            if(strcmp(ptr->nom, nv_nom) == 0 && strcmp(ptr->prenom, nv_prenom) == 0){
                printf("+---------------------------+\n");
                  printf("Entrer nouveau nom:\n");
                  gets(ptr->nom);
                printf("+---------------------------+\n");
                  printf("Entrer nouveau prenom:\n");
                  gets(ptr->prenom);
                  printf("+---------------------------+\n");
                  printf("Entrer nouveau mail:\n");
                  gets(ptr->mail);
                  printf("+---------------------------+\n");
                  printf("Entrer nouveau num:\n");
                  scanf("%lf", &ptr->num);
                printf("+---------------------------+\n");
                  printf("Modifier par succes\n");
                  printf("+---------------------------+\n");
                trouve = 1;
            }
            ptr = ptr->suivant;
        }while(ptr->suivant != tete);
    }
    if(trouve == 0){
        printf("+------------------------------------------------------------+\n");
        printf("Il y a aucun contact nomme par : %s %s\n", nv_nom, nv_prenom);
        printf("+------------------------------------------------------------+\n");
        exit(1);
    }
    printf("+---------------------------+\n");
    printf("Modification par succes\n");
    printf("+---------------------------+\n");
    return tete;
}

//afficher contact par nom et prenom
void affichage_un_contact(contact *tete, char *nom, char *prenom) {
    int trouve = 0;
    if(tete == NULL){
        printf("Liste Vide\n");
        exit(1);
    } else {
        contact *ptr = tete;
        do {
            if(strcmp(ptr->nom, nom) == 0 && strcmp(ptr->prenom, prenom) == 0){
                printf("+------------------------+------------------------+------------------------+------------------------+------------------------+\n");
                printf("|          Nom           |         Prenom         |  Numero de telephone   |         E-mail         |         Groupe         |\n");
                printf("+------------------------+------------------------+------------------------+------------------------+------------------------+\n");
                printf("|%23s |%23s |%23.0lf |%23s |%23s |\n", ptr->nom, ptr->prenom, ptr->num, ptr->mail, ptr->groupe);
                printf("+------------------------+------------------------+------------------------+------------------------+------------------------+\n");
                trouve = 1;
                break;
            }
            ptr = ptr->suivant;
        } while (ptr != tete);
    }
    if(trouve == 0){
        printf("+------------------------------------------------------------+\n");
        printf("Il n'y a aucun contact nomme : %s %s\n", nom, prenom);
        printf("+------------------------------------------------------------+\n");
        exit(1);
    }
}




//Affichage de tous les contacts
void affichage_tous(contact *tete) {
    if(tete == NULL){
        printf("Liste Vide\n");
        exit(1);
    } else {
        printf("\nLISTE DE CONTACTS:\n");
        printf("+------------------------+------------------------+------------------------+------------------------+------------------------+\n");
        printf("|          Nom           |         Prenom         |  Numero de telephone   |         E-mail         |         Groupe         |\n");
        printf("+------------------------+------------------------+------------------------+------------------------+------------------------+\n");

        contact *ptr = tete;
        do {
            printf("|%23s |%23s |%23.0lf |%23s |%23s |\n", ptr->nom, ptr->prenom, ptr->num, ptr->mail, ptr->groupe);
            printf("+------------------------+------------------------+------------------------+------------------------+------------------------+\n");
            ptr = ptr->suivant;
        } while (ptr != tete);
    }
}


//Programme Principal
int main(){
    contact *tete=NULL;
    contact *nv=NULL;
               
do{

    printf("+---------------------------+\n");
        printf("\tMenu Principale\n");
    printf("+---------------------------+\n");
        printf("1.Gestion des contacts\n");
    printf("+---------------------------+\n");
        printf("0.Quitter\n");
    printf("+---------------------------+\n");
    printf("\tChoix:..");
    scanf("%d",&choix);
        switch (choix)
        {
        case 1:
                    printf("\n+----------------------------------------+\n");
                    printf("1.Ajout un contact\n+----------------------------------------+\n2.Modification d un contact\n+----------------------------------------+\n3.Suppression d un contact\n+----------------------------------------+\n4.Recherche d un contact\n+----------------------------------------+\n5.Afficher un contact\n+----------------------------------------+\n6.Sauvegarder les contacts\n+----------------------------------------+\n7.Retour menu principal\n+----------------------------------------+\n\t\tChoix:...");
                    scanf("%d",&choix);
                            switch (choix)
                            {
                            case 1:
                                    printf("1.Ajout au debut\n+----------------------------------------+\n2.Ajout a la fin\n+----------------------------------------+\n3.Ajout apres un contact specifique\n+----------------------------------------+\n\tChoix:..");
                                    scanf("%d",&choix);
                                        switch (choix)
                                        {
                                        case 1:
                                                        printf("+---------------------------+\n");
                                                        printf("Nom: ");
                                                        scanf("%s", nom);
                                                        printf("+---------------------------+\n");
                                                        printf("Prenom: ");
                                                        scanf("%s", prenom);
                                                        printf("+---------------------------+\n");
                                                        printf("Mail: ");
                                                        scanf("%s", mail);
                                                        printf("+---------------------------+\n");
                                                        printf("Numero: ");
                                                        scanf("%lf", &num);
                                                        printf("+---------------------------+\n");
                                                        printf("Choisir le groupe\n+---------------------------+\n1.Famille\n+---------------------------+\n2.Amis\n+---------------------------+\n3.Travail\n+---------------------------+\n\tChoix: ");
                                                        scanf("%d", &choix);
                                                        switch (choix) {
                                                            case 1:
                                                                strcpy(groupe, "Famille");
                                                                break;
                                                            case 2:
                                                                strcpy(groupe, "Amis");
                                                                break;
                                                            case 3:
                                                                strcpy(groupe, "Travail");
                                                                break;
                                                            default:
                                                                printf("Choix invalide\n");
                                                                exit(1);
                                                                break;
                                                        }
                                                    nv = creation(nv, nom, prenom, mail, num, groupe);
                                                    tete=ajout_au_debut(tete,nv);
                                                    
                                            break;
                                        case 2:
                                                        printf("+---------------------------+\n");
                                                        printf("Nom: ");
                                                        scanf("%s", nom);
                                                        printf("+---------------------------+\n");
                                                        printf("Prenom: ");
                                                        scanf("%s", prenom);
                                                        printf("+---------------------------+\n");
                                                        printf("Mail: ");
                                                        scanf("%s", mail);
                                                        printf("+---------------------------+\n");
                                                        printf("Numero: ");
                                                        scanf("%lf", &num);
                                                        printf("+---------------------------+\n");
                                                        printf("Choisir le groupe\n+---------------------------+\n1.Famille\n+---------------------------+\n2.Amis\n+---------------------------+\n3.Travail\n+---------------------------+\n\tChoix: ");
                                                        scanf("%d", &choix);
                                                        switch (choix) {
                                                            case 1:
                                                                strcpy(groupe, "Famille");
                                                                break;
                                                            case 2:
                                                                strcpy(groupe, "Amis");
                                                                break;
                                                            case 3:
                                                                strcpy(groupe, "Travail");
                                                                break;
                                                            default:
                                                                printf("Choix invalide\n");
                                                                exit(1);
                                                                break;
                                                        }
                                                    nv = creation(nv, nom, prenom, mail, num, groupe);
                                                    tete=ajouter_au_fin(tete,nv);
                                            break;
                                        case 3:
                                                        printf("+---------------------------+\n");
                                                        printf("Nom: ");
                                                        scanf("%s", nom);
                                                        printf("+---------------------------+\n");
                                                        printf("Prenom: ");
                                                        scanf("%s", prenom);
                                                        printf("+---------------------------+\n");
                                                        printf("Mail: ");
                                                        scanf("%s", mail);
                                                        printf("+---------------------------+\n");
                                                        printf("Numero: ");
                                                        scanf("%lf", &num);
                                                        printf("+---------------------------+\n");
                                                        printf("Choisir le groupe\n+---------------------------+\n1.Famille\n+---------------------------+\n2.Amis\n+---------------------------+\n3.Travail\n+---------------------------+\n\tChoix: ");
                                                        scanf("%d", &choix);
                                                        switch (choix) {
                                                            case 1:
                                                                strcpy(groupe, "Famille");
                                                                break;
                                                            case 2:
                                                                strcpy(groupe, "Amis");
                                                                break;
                                                            case 3:
                                                                strcpy(groupe, "Travail");
                                                                break;
                                                            default:
                                                                printf("Choix invalide\n");
                                                                exit(1);
                                                                break;
                                                        }
                                                    nv = creation(nv, nom, prenom, mail, num, groupe);
                                            printf("------------------------------------------------------------\n");
                                            printf("Entre le nom specifie\n");
                                            gets(nom_specifie);
                                            printf("------------------------------------------------------------\n");
                                            tete=ajouter_au_millieu(tete,nv,nom_specifie);
                                            break;
                                        default:
                                            printf("Choix invalid\n");
                                            break;
                                    }
                                break;
                            case 2:
                                printf("------------------------------------------------------------\n");
                                printf("Entre le nom et prenom de contact qui veux modifier\n");
                                printf("------------------------------------------------------------\n");
                                printf("Nom:");
                                scanf("%s",nom);  
                                printf("------------------------------------------------------------\n");
                                printf("\nPrenom:");
                                scanf("%s",prenom);                  
                                printf("------------------------------------------------------------\n");
                                printf("+---------------------------+\n");
                                    printf("1.Modifier nom et prenom\n+---------------------------+\n2.Modifier mail\n+---------------------------+\n3.Modifier num\n+---------------------------+\n4.Modifier tous les information\n+---------------------------+\n\tChoix:..");
                                    scanf("%d",&choix);
                                        switch (choix)
                                        {
                                        case 1:
                                            tete=modifier_nom(tete,nom,prenom);
                                            break;
                                        case 2:
                                            tete=modifier_mail(tete,nom,prenom);
                                            break;
                                        case 3:  
                                            tete=modifier_num(tete,nom,prenom);
                                            break;
                                        case 4:
                                            tete=modifier_tous(tete,nom,prenom);
                                            break;
                                        default:
                                            printf("Choix invalid\n");
                                            break;
                                        }
                                break;
                            case 3:
                                    printf("------------------------------------------------------------\n");
                                    printf("1.Suppression au debut\n+----------------------------------------+\n2.Suppressiont a la fin\n+----------------------------------------+\n3.Suppression apres un contact specifique\n+----------------------------------------+\n4.Retour\n+----------------------------------------+\n\tChoix:..");
                                    scanf("%d",&choix);
                                        switch (choix)
                                        {
                                        case 1:
                                            tete=supprimer_au_debut(tete);
                                            break;
                                        case 2:
                                            tete=supprimer_au_fin(tete);
                                            break;
                                        case 3:
                                            printf("+---------------------------+\n");
                                            printf("Entre le nom specifie\n");
                                            gets(nom);
                                            printf("+---------------------------+\n");
                                            printf("Entre prenom specifie\n");
                                            gets(prenom);
                                            printf("+---------------------------+\n");
                                            tete=supprimer_apres_contact_specifique(tete,nom,prenom);
                                            break;
                                        case 4:

                                            break;
                                        default:
                                            printf("Choix invalid\n");
                                            break;
                                        }
                                break;
                            
                            case 4:
                                    printf("+---------------------------+\n");
                                    printf("1.Recherche par nom et prenom\n+---------------------------+\n2.Recherche par mail\n+---------------------------+\n3.Recherche par num\n+---------------------------+\n4.retour\n+---------------------------+\n\tChoix:...");
                                    scanf("%d",&choix);
                                            switch (choix)
                                        {
                                        case 1:
                                        printf("+---------------------------+\n");
                                            printf("Nom:\n");
                                            scanf("%s",nom);   
                                            printf("+---------------------------+\n");  
                                            printf("\nPrenom:\n");
                                            scanf("%s",prenom);   
                                            printf("+---------------------------+\n");
                                            recherche_par_nom(tete,nom,prenom);
                                            break;
                                        case 2:
                                        printf("+---------------------------+\n");
                                            printf("Entre le mail:\n");
                                            scanf("%s",mail);
                                            printf("+---------------------------+\n");
                                            recherche_par_mail(tete,mail);
                                            break;
                                        case 3:
                                        printf("+---------------------------+\n");
                                            printf("Entre num:\n");
                                            scanf("%lf",&num);
                                            printf("+---------------------------+\n");
                                            recherche_par_num(tete,num);
                                            break;
                                        case 4:

                                            break;
                                        default:
                                        printf("+---------------------------+\n");
                                            printf("Choix invalid\n");
                                        printf("+---------------------------+\n");
                                            break;
                                        }
                                break;
                            case 5:
                            printf("+---------------------------+\n");
                                    printf("1.Afficher un contact\n+---------------------------+\n2.Afficher tous les contacts\n+---------------------------+\n3.Retour\n+---------------------------+\n\tChoix:..");
                                    scanf("%d",&choix);
                                        switch (choix)
                                        {
                                        case 1:
                                        printf("+---------------------------+\n");
                                                printf("Nom:\n");
                                                scanf("%s",nom);     
                                            printf("+---------------------------+\n");
                                                printf("\nPrenom:\n");
                                                scanf("%s",prenom); 
                                                printf("+---------------------------+\n");
                                                affichage_un_contact(tete,nom,prenom);
                                            break;
                                        case 2:
                                                affichage_tous(tete);
                                            break;
                                        case 3:

                                            break;
                                        default:
                                                printf("Choix invalid\n");
                                            break;
                                        }
                             
                            case 6:
                                    sauvegarde_contacts(tete);
                                break;
                            case 7:
                                
                                break;
                            default:
                                break;
                        }
            break;
        case 0:
                printf("+---------------------------+\n");
                    printf("Au revoir!\n");
                    printf("+---------------------------+\n");
                    exit(0);
            break;
        default:
        printf("+---------------------------+\n");
                printf("Choix invalid\n");
                printf("+---------------------------+\n");
                    exit(1);
            break;
        }
    }while(choix!=0);
    
    return 0;
}