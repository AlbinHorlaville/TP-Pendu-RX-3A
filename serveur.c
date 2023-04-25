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
#include <time.h>

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
	//h_close(socket);

	// Initialisation des variables

	int end, offset;
	char message_fin[18];
	int nb_carac_mot, nb_essais;
	int nb_coeur;  // Nombre de Points de vie
	char mot[100]; // Mot à deviner

	// Choix d'un mot aléatoire parmis une liste de mot dans le dictionnaire
	char *dictionnaire[10] = {"maison", "albin", "greg", "louane", "voiture", "mario", "bowser"};
	srand(clock());
	int i = rand() % 10;
	string_copy(mot, dictionnaire[i]);
	// longueur du mot
	int len = string_length(mot);
	// Le nombre d'essai correspond à la longueur du mot
	nb_carac_mot = len;

	char essai[nb_carac_mot];
	for (int i = 0; i < nb_carac_mot; i++)
	{
		essai[i] = '_';
	}
	char *image_pendu = "Jeu du Pendu\n———————\n|————ı\n|    !\n|    O\n|   /|\\ \n|\\  / \\ \n| \\ \n———————\n";
	nb_coeur = nb_essais = len;

	// Envoie des paquets

	h_writes(socket_client, image_pendu, 110);

	h_writes(socket_client, "Niveau de difficulte : (1, 2 ou 3)", 35);

	// On remplit la barre de points de vie
	// Un 'O' correspond à un point de vie, un 'X' à un point de vie consommé
	char *difficulte = malloc(sizeof(difficulte));
	char coeurs[10];
	h_reads(socket_client, difficulte, 1);
	int diff = atoi(difficulte);
	switch (diff)
	{
	case 1:
		for (int i = 0; i < len * 2; i++)
		{
			coeurs[i] = 'O';
		}
		break;
	case 2:
		for (int i = 0; i < len; i++)
		{
			coeurs[i] = 'O';
		}
		break;
	case 3:
		for (int i = 0; i < len / 2; i++)
		{
			coeurs[i] = 'O';
		}
		break;
	default:
		for (int i = 0; i < len * 2; i++)
		{
			coeurs[i] = 'O';
		}
		break;
	}
	end = 0;
	while (!end)
	{
		// Envoie du nombre de carac du mot à trouver
		char p[2];
		sprintf(p, "%d", nb_carac_mot);
		h_writes(socket_client, p, 1);

		// Envoie du mot a trouver
		h_writes(socket_client, essai, nb_carac_mot);

		// Envoie des Points de vie
		h_writes(socket_client, coeurs, nb_essais);

		// Réception du caractère envoyé
		/* Affectation d'un tampon */
		char *carac_recu = malloc(sizeof(carac_recu));
		h_reads(socket_client, carac_recu, 1);

		int existe = 0;
		offset = 0; // je mets la position à 0
		// On cherche toutes postions du caratère dans le mot pour remplacer les tiretsclient.c
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
		if (!existe)
		{ // On met à jour le tableau de coeur si erreur
			coeurs[nb_coeur - 1] = 'X';
			nb_coeur--;
		}
		if (nb_coeur == 0)
		{ // Si plus de coeurs alors perdu
			end = 1;
			fin_du_game(message_fin, 0);
		}

		if (!string_cmp(mot, essai)) // retourne 0 si identique
		{							 // Si mot trouvé alors gagné
			end = 1;
			fin_du_game(message_fin, 1);
		}
		// Paramètre end qui est à 0 tant que la partie n'est pas finie
		char itos[2];
		sprintf(itos, "%d", end);
		// Envoie du paramètre end
		h_writes(socket_client, itos, 1);
	}
	printf("\033[35mFIN, Fermeture de la connexion.\033[00m\n");
	h_writes(socket_client, message_fin, 18);
	h_close(socket_client); // fermeture socket active car le père ne s'en sert pas
/* A completer ... */
}

/******************************************************************************/
