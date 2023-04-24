/******************************************************************************/
/*			Application: Le Pendu					*/
/******************************************************************************/
/*									      */
/*			 programme  CLIENT				      */
/*									      */
/******************************************************************************/
/*									      */
/*		Auteurs : Albin Horlaville, Gregory Pittito & Louane Lesur 		   	*/
/*									      */
/******************************************************************************/	

	
#include <stdio.h>
#include <curses.h> 		/* Primitives de gestion d'ecran */
#include <sys/signal.h>
#include <sys/wait.h>
#include<stdlib.h>

#include "fon.h"   		/* primitives de la boite a outils */
// #include "echo.c"

#define SERVICE_DEFAUT "1111"
#define SERVEUR_DEFAUT "127.0.0.1"
#define BUFFER_SIZE 80

char *buffer;


char* read_line(int fd) {
    //initialise buffer
  buffer = malloc(BUFFER_SIZE);

  char* str;
  int len = 0;
  char ch;
  do
  {
    if (len >= BUFFER_SIZE)
    break;

    if(read(fd,&ch,1) != 1){
      if (len == 0){
        return NULL;
      }
    }
    *(buffer + len) = ch;
    len ++;
  } while (ch != '\n');
    

  len--;
  *(buffer + len) = '\0';

  str = malloc(len+1);
  for(int i = 0; i<= len; i++){
    *(str + i) = *(buffer + i);
  }
  return str;
  
}

void client_appli (char *serveur, char *service);




/*****************************************************************************/
/*--------------- programme client -----------------------*/

int main(int argc, char *argv[])
{

	char *serveur= SERVEUR_DEFAUT; /* serveur par defaut */
	char *service= SERVICE_DEFAUT; /* numero de service par defaut (no de port) */


	/* Permet de passer un nombre de parametre variable a l'executable */
	switch(argc)
	{
 	case 1 :		/* arguments par defaut */
		  printf("serveur par defaut: %s\n",serveur);
		  printf("service par defaut: %s\n",service);
		  break;
  	case 2 :		/* serveur renseigne  */
		  serveur=argv[1];
		  printf("service par defaut: %s\n",service);
		  break;
  	case 3 :		/* serveur, service renseignes */
		  serveur=argv[1];
		  service=argv[2];
		  break;
    default:
		  printf("Usage:client serveur(nom ou @IP)  service (nom ou port) \n");
		  exit(1);
	}

	/* serveur est le nom (ou l'adresse IP) auquel le client va acceder */
	/* service le numero de port sur le serveur correspondant au  */
	/* service desire par le client */
	
	client_appli(serveur,service);
}

/*****************************************************************************/
void client_appli (char *serveur,char *service)

/* procedure correspondant au traitement du client de votre application */

{
  /* ♥♥♥♥♥♥♥♥♥♥♥ */
/* a completer .....  */
//  Premier message : 1 paquet de 110 caractères
//  Buffer / Tampon : nb_carac_mot | mot | coeurs | end
//  Dernier message : 1 paquet de 18 caractères

 /* Initialisation de la connexion au serveur */
	int socket = h_socket(AF_INET, SOCK_STREAM);
	struct sockaddr_in *p_adr_serv = malloc(sizeof(struct sockaddr_in));
	adr_socket(service, serveur, SOCK_STREAM, &p_adr_serv);
	h_connect(socket, p_adr_serv);

	/* Affectation d'un tampon */
	char *tampon = malloc(sizeof(tampon));

	/* Affichage message début */
	int end = 0;
	int nb_octets;
	h_reads(socket, tampon, 110);
	printf("\033[32m%s\033[00m", tampon);


	char* mot, *coeurs;

	/* Boucle de gameplay, se termine quand le joueur a gagné ou perdu */
	while(!end){
		char tampon[1];
		// Récupération du nombre de caractère du mot
		h_reads(socket,tampon, 1);
		nb_octets = atoi(tampon);

		// Récupération du mot
		char mot[nb_octets];
		h_reads(socket, mot, nb_octets);
		
		printf("mot : %s\n", mot);
		// Récupération des coeurs (5)
		char tampon3[5];
		h_reads(socket, tampon3, 5);
		coeurs = tampon3;
		printf("%s\n", coeurs);


		// Ecriture / Proposition d'une lettre

		char carac[100];
		int c;
		c = getc(stdin);
		while(c == '\n'){
			c = getc(stdin);
		}
		carac[0] = c;
		h_writes(socket, carac, 1);

		printf("Récupération de end\n");
		// Récupération de l'octet end
		h_reads(socket, tampon, 1);
		end = atoi(tampon);
		

	}

	/* Affichage message fin */
	h_reads(socket, tampon, 18);
	printf("%s", tampon);
	h_close(socket);
}

/*****************************************************************************/

