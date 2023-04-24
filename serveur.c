/******************************************************************************/
/*			Application: ....			              */
/******************************************************************************/
/*									      */
/*			 programme  SERVEUR 				      */
/*									      */
/******************************************************************************/
/*									      */
/*		Auteurs :  ....						      */
/*		Date :  ....						      */
/*									      */
/******************************************************************************/

#include <stdio.h>
#include <curses.h>

#include <sys/signal.h>
#include <sys/wait.h>
#include <stdlib.h>

#include "fon.h" /* Primitives de la boite a outils */
#include "string.c"
#include "pendu.c"

#define SERVICE_DEFAUT "1111"

void serveur_appli(char *service); /* programme serveur */

/******************************************************************************/
/*---------------- programme serveur ------------------------------*/

int main(int argc, char *argv[])
{

	char *service = SERVICE_DEFAUT; /* numero de service par defaut */

	/* Permet de passer un nombre de parametre variable a l'executable */
	switch (argc)
	{
	case 1:
		printf("defaut service = %s\n", service);
		break;
	case 2:
		service = argv[1];
		break;

	default:
		printf("Usage:serveur service (nom ou port) \n");
		exit(1);
	}

	/* service est le service (ou numero de port) auquel sera affecte
	ce serveur*/

	serveur_appli(service);
}

/******************************************************************************/
void serveur_appli(char *service)

/* Procedure correspondant au traitemnt du serveur de votre application */

{

	// Création d'une socket / Socket PASSIVE
	int socket = h_socket(AF_INET, SOCK_STREAM);

	// Renseignement de la structure sockaddr_in
	struct sockaddr_in *p_adr_client = malloc(sizeof(struct sockaddr_in));

	// Association à la socket
	adr_socket(service, NULL, SOCK_STREAM, &p_adr_client);
	h_bind(socket, p_adr_client);

	// Mise en écoute de la socket
	h_listen(socket, SOMAXCONN);

	// Récupération de la socket de communication avec un client  /  Socket ACTIVE
	int socket_client = h_accept(socket, p_adr_client);

	// Initialisation des variables

	int end, offset;

	char* mot, *message_fin;
	int nb_carac_mot, nb_essais;
	int nb_coeur;
	
	char coeurs[5] = "OOOOO";
    mot = "maison";
    nb_carac_mot = 6;
	nb_essais = 5;
	char essai[nb_carac_mot];
	for(int i = 0; i < nb_carac_mot; i++){
        essai[i] = '_';
    }
	char *image_pendu =  "Jeu du Pendu\n———————\n|————ı\n|    !\n|    O\n|   /|\\ \n|\\  / \\ \n| \\ \n———————\n";
	nb_coeur = nb_essais;
	
	// Envoie des paquets

	h_writes(socket_client, image_pendu, 110);
	end = 0;
	while (!end)
	{
		// Envoie du nombre de carac du mot à trouver
		char p[5];
		sprintf(p,"%d",nb_carac_mot);

		h_writes(socket_client,p,1);
		// Envoie du mot a trouver
		printf("Envoie du mot a trouver\n");
		h_writes(socket_client, essai, nb_carac_mot);

		// Envoie du nombre d'essais
		printf("Envoie du nombre d'essais\n");
		h_writes(socket_client, coeurs, nb_essais);

		// Réception du caractère envoyé
		/* Affectation d'un tampon */
		char *carac_recu = malloc(sizeof(carac_recu));
		h_reads(socket_client, carac_recu, 1);

		int existe = 0;
		offset = 0; // je mets la position à 0
		// On cherche toutes postions du caratère dans le mot pour remplacer les tirets
		while (offset != -1)
		{
			offset = string_index_of(mot, offset, carac_recu[0]);
			if (offset != -1)
			{
				essai[offset] = mot[offset];
				offset++;
				existe = 1;
			}
		}
		printf("EXISTE : %d\n", existe);
		if (!existe)
		{ // On met à jour le tableau de coeur si erreur
			printf("Je suis rentré ici\n");

			coeurs[nb_coeur - 1] = 'X';
			//*(coeurs + nb_coeur -1) = "X";
			nb_coeur--;
		}
		if (nb_coeur == 0)
		{ // Si plus de coeurs alors perdu
			printf("je suis rentré la\n");
			end = 1;
			//fin_du_game(message_fin, 0);
			message_fin = "Fin du jeu, PERDU\n";
		}
		if (string_cmp(mot, essai)==0) // retourne 0 si identique
		{ // Si mot trouvé alors gagné
			end = 1;
			// fin_du_game(message_fin, 1);
        	message_fin = "Fin du jeu, GAGNE\n";
			printf("YOUHOU\n");
		}
		printf("LALALALALLALALA\n");
		// Paramètre end qui est à 1 tant que la partie n'est pas finie
		char itos[2];
		sprintf(itos,"%d", end);

		// Envoie du paramètre end
		printf("Envoie du paramètre end\n");
		h_writes(socket_client, itos, 1);

		
		printf("mot = essai : %d\n", string_cmp(mot, essai));
		printf("nb_coeur : %d\n", nb_coeur);
		printf("end : %d\n", end);

	}
	printf("FIN\n");
	h_writes(socket_client, message_fin, 18);
	h_close(socket_client); // fermeture socket active car le père ne s'en sert pas

	/* A completer ... */
}

/******************************************************************************/
