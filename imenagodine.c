#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void opcija_y(int *ind, char **ime, int g, int br)
{
  for(int i=0; i<br; i++){
    ind[i] /= 1000;
    if(ind[i] == g){
      printf("%s ", ime[i]);
    }
  }
  printf("\n\n");
}

void opcija_n(int ind[], char *ime[], char * x, int br)
{
  for(int i=0; i<br; i++){
    if(strcmp(ime[i], x) == 0){
      printf("%d ", ind[i]/1000);
    }
  }
  printf("\n\n");
}


int main(){

  printf("unesite broj studenata...\n");

  int n;
  scanf("%d", &n);

  int niz_ind[n];
  char * niz_ime[n];

  for(int i = 0; i < n; i++)
    {
      printf("\n unesite ime i indeks studenta... (%d komada)\n", n-i);
      niz_ime[i] = malloc(sizeof(char)*30);

      scanf("%d %s", &niz_ind[i], niz_ime[i]);
    }

  for(int i = 0; i < n; i++)
    printf("index: %d \t ime: %s\n", niz_ind[i], niz_ime[i]);

  char * opcija = "-n";
  char * x = "ana";
  int god = 2011;

  if(opcija[1] == 'y')
  {
    opcija_y(niz_ind, niz_ime, god, n);
  }

  if(opcija[1] == 'n')
  {
    opcija_n(niz_ind, niz_ime, x, n);
  }

  return 0;
}

