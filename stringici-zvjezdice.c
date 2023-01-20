#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 1000


void funkcija(char *niska,const char *stara,const char *nova)
{
    char *poz, temp[MAX];
    int indeks = 0;
    int duzina;
    duzina= strlen(stara);

    while ((poz=strstr(niska, stara))!=NULL)
    {

        strcpy(temp,niska);
        indeks = poz-niska;
        niska[indeks]='\0';
        strcat(niska,nova);
        strcat(niska,temp+indeks+duzina);
    }
}


int main(int argc, char *argv[])
{

    FILE *f1;
    FILE *f2;
    char bafer[MAX];
    char stara[100], nova[100];

    f1 = fopen(argv[1],"r");
    if(f1 == NULL) {
      perror("Greska u f1");
      return(-1);
    }

    f2 = fopen(argv[2],"w");
    if(f2 == NULL) {
      perror("Greska u f2");
      return(-1);
    }

    strcpy(stara,argv[3]);

    int m=strlen(stara);
    for(int i=0;i<m;i++){
        nova[i]='*';
    }

    if (f1==NULL || f2==NULL)
    {
        printf("Greska u unosu datoteke.\n");
        return (-1);
    }

    while ((fgets(bafer,MAX,f1))!=NULL)
    {

        funkcija(bafer,stara,nova);
        fputs(bafer, f2);
    }

    fclose(f1);
    fclose(f2);

    printf("Uspjesno zamijenili nisku '%s' sa'%s'.", stara, nova);

    return 0;
}
