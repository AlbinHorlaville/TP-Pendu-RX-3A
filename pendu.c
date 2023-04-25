#include <stdio.h>
#include <stdlib.h>
#include <string.h>



char* init_mot(){
    char *mot = "maison";
    return mot;
}

void init_game_test(char *mot_a_trouver){
    char *mot = init_mot();
    strcpy(mot_a_trouver,mot);
}

void init_game(char *mot, int *nb_carac_mot, int *nb_essais, char *coeurs,char *essai, char *image_pendu){

    strcpy(mot,init_mot());

    *nb_carac_mot = strlen(mot);

    *nb_essais = 5;
    
    for(int i = 0; i < *nb_carac_mot; i++){
        coeurs[i] = 'O';
    }

    for(int i = 0; i < *nb_carac_mot; i++){
        essai[i] = '_';
    }
    strcpy(image_pendu, "Jeu du Pendu\n———————\n|————ı\n|    !\n|    O\n|   /|\\ \n|\\  / \\ \n| \\ \n———————\n");
}

void fin_du_game(char *message_fin, int resultat){
    if(resultat){
       strcpy(message_fin, "Fin du jeu, GAGNE\n");
    } else{
        strcpy(message_fin, "Fin du jeu, PERDU\n");
    }
}





// int main(){
//     char mot[100];
//     int nb_carac_mot,nb_essai;
//     char essais[20];
//     char coeurs[20];    
//     char message_fin[18];

//     init_game(mot,&nb_carac_mot,&nb_essai,coeurs,essais);
//     printf("Le mot est : %s\n",mot);
//     printf("Il y a %d lettre dans le mot \n",nb_carac_mot);
//     printf("Il a y %d essais pour trouver le mot\n",nb_essai);
//     printf("Voici la liste de coeurs : %s\n",coeurs);
//     printf("Voici le mot sans les lettres %s\n",essais);

//     fin_du_game(message_fin,1);
//     printf("Le message de fin est : %s",message_fin);



//     return 0;
// }