#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h> 

int main(int argc, char const *argv[]){

	//---------- Supprimer le fichiers fifo existants ----------
	remove("guiCalcul.fifo");
	remove("calcul-gui.fifo");
	remove("calcul-trace.fifo");

	if(fork() == 0) // gui process
	{
		char *args[]={"./trace",NULL};
		execvp(args[0], args);
	}
	else
	{
		if (fork() == 0) // calcul process
		{
			char *args[]={"./calcul",NULL};
			execvp(args[0], args);
		}
		else
		{
			char *args[]={"./guiGTK",NULL};
			execvp(args[0], args);

		}
	}

 	return 0;
}
