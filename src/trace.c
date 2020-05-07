#include <stdio.h>
#include "trace.h"
#include <string.h>

#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>

void savop(char op, int opg, int opd, long int res);

void savop(char op, int opg, int opd, long int res){
    FILE* f; 
    operation lop;
    f=fopen("track.trc","a+b");
    lop.o=op;
    lop.g=opg;
    lop.d=opd;
    lop.r=res;
    fwrite(&lop,sizeof(operation),1,f);
    fclose(f);
}

void saveFact(char op, int opg, long int res)
{
    FILE* f; 
    operation lop;
    f=fopen("track.trc","a+b");
    lop.o=op;
    lop.g=opg;
    lop.d=0;
    lop.r=res;
    fwrite(&lop,sizeof(operation),1,f);
    fclose(f);
}

int main(int argc, char const *argv[])
{
    int sortieTube;
    char chaineALire[20];
    operation op;
    int commande, op1, op2, resultat;

    while(1)
    {
        while((sortieTube = open ("calcul-trace.fifo", O_RDONLY)) == -1)
        {
            usleep(20000);
        }

        read(sortieTube, chaineALire, 20);
        remove("calcul-trace.fifo");

        if(chaineALire[0] == '0')
        {
            return 0;
        }
        else if(chaineALire[0] == '3')
        {
            sscanf(chaineALire, "%d %d %d", &commande, &op1, &resultat);
            saveFact(3, op1, resultat);
        }
        else
        {
            sscanf(chaineALire, "%d %d %d %d", &commande, &op1, &op2, &resultat);
            savop(commande, op1, op2, resultat);
        }
    }
    return 0;
}
