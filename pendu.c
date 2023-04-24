#include <stdio.h>


void init_game(char *mot, int *nb_carac_mot, int *nb_essais, char *coeurs,char *essai){
    mot = malloc(5*sizeof(char));
    essai = malloc(5*sizeof(char)); 
    // image_pendu = malloc(73*sizeof(char));
    nb_essais = malloc(sizeof(int));
    nb_carac_mot = malloc(sizeof(int));
    *nb_essais = 5;
    coeurs = malloc(*nb_essais*sizeof(char));
    coeurs = "♥♥♥♥♥";
    mot = "maison";
    *nb_carac_mot = 6;
    
    // printf("%s\n", image_pendu);

    for(int i = 0; i < *nb_carac_mot; i++){
        essai[i] = '_';
    }
    
}





void fin_du_game(char *message_fin, int resultat){
    message_fin = malloc(sizeof(char)*18);

    if(resultat){
        message_fin = "Fin du jeu, GAGNE\n";
    } else{
        message_fin = "Fin du jeu, PERDU\n";
    }
}

