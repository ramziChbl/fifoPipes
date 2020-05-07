#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>


int fact(int n){
	int r;
	int x = n;
 	if (n <= 1) r = 1;
    else r= n * fact(n-1);
 	return r;
 }

int main(int argc, char const *argv[])
{
	int sortieTube;
	char chaineALire[20];
	char chaineAEcrire[20];
	//printf("Debut prgm calcul\n");

	while(1)
	{

		while((sortieTube = open ("guiCalcul.fifo", O_RDONLY)) == -1)
		{
			usleep(20000);
		}
		//printf("guiCalcul.fifo connecte\n" );

		/*if((sortieTube = open ("guiCalcul.fifo", O_RDONLY)) == -1) 
		{
			fprintf(stderr, "Impossible d'ouvrir la sortie du tube nommé.\n");
			exit(EXIT_FAILURE);
		}*/

		read(sortieTube, chaineALire, 10);
		remove("guiCalcul.fifo");
		int commande, op1, op2, resultat;

		//======================== Calcul to trace ==========================
		if(fopen("calcul-trace.fifo", "r") != NULL)
		{
			remove("calcul-trace.fifo");
		}

		int entreeTube;
		char nomTube[20] = "calcul-trace.fifo";

		if(mkfifo(nomTube, 0644) != 0) 
		{
			fprintf(stderr, "Impossible de créer le tube nommé.\n");
			exit(EXIT_FAILURE);
		}

		if((entreeTube = open(nomTube, O_WRONLY)) == -1) 
		{
			fprintf(stderr, "Impossible d'ouvrir l'entrée du tube nommé.\n");
			exit(EXIT_FAILURE);
		}

		switch(chaineALire[0])
		{
			case '0':
				write(entreeTube, "0", 10);
				return 0;
			break;
			case '1': // Somme
				sscanf(chaineALire, "%d %d %d", &commande, &op1, &op2);
				//printf("1 %d %d %d\n", op1, op2, op1 + op2);
				resultat = op1 + op2;
				sprintf(chaineAEcrire, "1 %d %d %d\n", op1, op2, resultat);
			break;
			case '2': // Produit
				sscanf(chaineALire, "%d %d %d", &commande, &op1, &op2);
				//printf("2 %d %d %d\n", op1, op2, op1 * op2);
				resultat = op1 * op2;
				sprintf(chaineAEcrire, "2 %d %d %d\n", op1, op2, resultat);
			break;
			case '3': // Factorielle
				sscanf(chaineALire, "%d %d", &commande, &op1);
				//printf("3 %d %d\n", op1, fact(op1));
				resultat = fact(op1);
				sprintf(chaineAEcrire, "3 %d %d\n", op1, fact(op1));
			break;
		}
		printf("resultat = %d\n", resultat);
		write(entreeTube, chaineAEcrire, 10); // Send to trace
	}

	return 0;
}
