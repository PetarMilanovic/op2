#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int prebrojavanje(char *str){
  char *string;
  string = malloc(sizeof(char)*30);
  int offset;
  int brojac = 0;
  
  while(sscanf(str, "%s%n", string, &offset)==1){
    str += offset;
    brojac++;
  }
  
  return brojac;
}

int br_rec(char * name)
{
  FILE * ulaz = fopen(name, "r");

  int br = 0;
  char niz[30];
  while(!feof(ulaz))
    {
      fgets(niz, 30, ulaz);
      br+=1;
    }
  
  return br-1;
}

char ** ucitaj(char * name)
{
  FILE * ulaz = fopen(name, "r");

  int n1 = br_rec(name);
  char **r1;
  r1 = malloc(sizeof(char *)*n1);

  int i = 0;
  while(!feof(ulaz))
    {
      r1[i] = malloc(200);
      fgets(r1[i], 200, ulaz);
      i+=1;
    }
  return r1;
}

void provjeri(char * s1, char * s2)
{
  FILE * izlaz = fopen("izlaz.txt", "a");
  int n1 = prebrojavanje(s1);
  int n2 = prebrojavanje(s2);

  float max = n1 * 0.7;
  if(n2 > n1)
    max = n2 * 0.7;

  printf("n1: %d - n2: %d - max: %.2f\n", n1, n2, max);

  if(n1 > max && n2 > max)
  {
    fputs(s1, izlaz);
    fputs(s2, izlaz);
    fputs("\n", izlaz);
  }
  fclose(izlaz);
}


int main()
{
  int n1 = br_rec("u1.txt");
  int n2 = br_rec("u2.txt");


  char **r1 = ucitaj("u1.txt");
  char **r2 = ucitaj("u2.txt");

  for(int i = 0; i < n1; i++)
    {
      for(int j = 0; j < n2; j++)
        {
          provjeri(r1[i], r2[j]);
        }
    }

  return 0;
}