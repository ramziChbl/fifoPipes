#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
//#include "trace.h"

typedef struct 
{ char o;
  int g;
  int d;
  long int r;
} operation;


int affichmenu();
void execomnd(int com);
//void affichtable(tabl t);
void affichtable(operation t[10], int n);

int main(int argc, char const *argv[]){
	remove("guiCalcul.fifo");
	remove("calcul-trace.fifo");

	int choix = 1;
	while(choix)
	{
    	remove("guiCalcul.fifo");
		remove("calcul-trace.fifo");
		remove("calcul-gui.fifo");
    	choix = affichmenu();
    	execomnd(choix);
    }
 	return 0;
}

int affichmenu(){
	int chx;
	printf("\n\n\n-----------------\n");
	printf("0: Quitter\n");
	printf("1: Somme\n");
	printf("2: Produit\n");
	printf("3: Factoriel\n");
	printf("4: Trace\n");
	printf("-----------------\n");

	scanf("%d",&chx);
  	return chx;
}

void execomnd(int com)
{
    
    int a,b;
    char chaineAEcrire[10];
    int entreeTube;
	char nomTube[20] = "guiCalcul.fifo";

 	switch (com)
 	{
	 	case 0:
 		{
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
			write(entreeTube, "0", 10);
 			break;
 		}
	 	
	 	case 1:
	      printf("introduire les nombre :\n");
	      scanf("%d %d",&a,&b);
	      printf("Operandes saisies\n");
          sprintf(chaineAEcrire, "1 %d %d",a,b); 
          break;

	 	case 2: 
	      	printf("introduire les nombre :\n");
	      	scanf("%d %d",&a,&b);
	      	printf("Operandes saisies\n");
          	sprintf(chaineAEcrire, "2 %d %d",a,b); 
          	break;
          	
	 	case 3:
	 		printf("introduire le nombre :\n");
	      	scanf("%d", &a);
	      	printf("Operandes saisies\n");
          	sprintf(chaineAEcrire, "3 %d",a);
	      	break;

		case 4:
		{
        	FILE *ftrack;
        	operation ops[10];
		    
		    ftrack = fopen("track.trc","r+b");
		    if (ftrack == NULL)
		    	break;

		    int nops = fread(ops,sizeof(operation),10,ftrack);
		    fclose(ftrack);
          	affichtable(ops, nops);
          	break;
        }
	}

	if(com <= 3 )
	{
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
		write(entreeTube, chaineAEcrire, 10);
	}
}	 


void affichtable(operation t[], int n){
    printf("operation ! operande G ! operande D ! resultat !\n");
    printf("------------------------------------------------\n"); 

    for (int i=0; i<n; i++)
	{ 
		printf(" %5d    ! %6d     ! %6d     !  %6ld  !\n",t[i].o, t[i].g, t[i].d, t[i].r);
		printf("----------!------------!------------!----------!\n");

	}	

}
 
