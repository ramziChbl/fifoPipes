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
	char chaineResultat[20];
	FILE *f = fopen("tst.val" , "w");

	while(1)
	{
		while((sortieTube = open ("guiCalcul.fifo", O_RDONLY)) == -1)
		{
			usleep(20000);
		}

		read(sortieTube, chaineALire, 20);
		remove("guiCalcul.fifo");

		int commande, op1, op2, resultat;

		//======================== Calcul vers GUI ==========================
		/*remove("calcul-gui.fifo");*/

		int calculGuiTube;
		char nomCalculGuiTUbe[20] = "calcul-gui.fifo";

		mkfifo(nomCalculGuiTUbe, 0644);
		calculGuiTube = open(nomCalculGuiTUbe, O_WRONLY);

		//======================== Calcul vers trace ==========================

		remove("calcul-trace.fifo");
		
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
				write(entreeTube, "0", 20);
				return 0;
			break;
			case '1': // Somme
				sscanf(chaineALire, "%d %d %d", &commande, &op1, &op2);
				resultat = op1 + op2;
				sprintf(chaineAEcrire, "1 %d %d %d\n", op1, op2, resultat);
				sprintf(chaineResultat, "%d", resultat);
				fprintf(f, "%s\n", chaineResultat);
			break;
			case '2': // Produit
				sscanf(chaineALire, "%d %d %d", &commande, &op1, &op2);
				resultat = op1 * op2;
				sprintf(chaineAEcrire, "2 %d %d %d\n", op1, op2, resultat);
				sprintf(chaineResultat, "%d",resultat);
			break;
			case '3': // Factorielle
				sscanf(chaineALire, "%d %d", &commande, &op1);
				resultat = fact(op1);
				sprintf(chaineAEcrire, "3 %d %d\n", op1, resultat);
				sprintf(chaineResultat, "%d",resultat);
			break;
		}

		write(entreeTube, chaineAEcrire, 20); // Send to trace
		write(calculGuiTube, chaineResultat, 20); // Send to GUI
	}
	fclose(f);
	return 0;
}
