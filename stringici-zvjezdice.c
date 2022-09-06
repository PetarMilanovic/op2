#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void promijeni(char * tren, char * niska)
{
  FILE * izlaz = fopen("izlaz.txt", "a");
  char trenutni[strlen(tren)];

  strcpy(trenutni, tren);
  
  while(strstr(trenutni, niska))
  {
    char * p = strstr(trenutni, niska);
    for(int i = 0; i < strlen(niska); i++)
      p[i] = '*';
  }

  fputs(trenutni, izlaz);
  fclose(izlaz);
}


int main(){
  
  FILE *f = fopen("ulaz.txt", "r");
  
  char * n2 = "burek";
  char buf[80];
  
  while(!feof(f)){
    fgets(buf, 80, f);
    promijeni(buf, n2);
  }
  
  fclose(f);
  
  return 0;
} 