#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct Lopta{ 
  float poluprecnik;
  char boja[7];
  struct Lopta * sljedeci;
}Lopta;

void dodaj(Lopta ** l, float pp, char * boja)
{
  if(*l == NULL)
  {
    *l = malloc(sizeof(Lopta));
    (**l).poluprecnik = pp;
    strcpy((**l).boja, boja);
    (**l).sljedeci = NULL;
  }
  else
  {
    Lopta * temp = *l;
    while(temp->sljedeci)
      temp = temp->sljedeci;

    temp->sljedeci = malloc(sizeof(Lopta));
    Lopta * novi = temp->sljedeci;
    novi->poluprecnik = pp;
    strcpy(novi->boja, boja);
    novi->sljedeci = NULL;
  }
}

int provjera(char * s)
{
  if(strcmp(s, "plava") == 0 || strcmp(s, "zuta") == 0 || strcmp(s, "crvena") == 0 || strcmp(s, "zelena") == 0 || strcmp(s, "maki<3") == 0)
    return 1;
  return 0;   
}



void ispis(Lopta *l)
{
  while(l)
    {
      printf("%s - %.2f\n", l->boja, l->poluprecnik);
      l = l->sljedeci;
    }
  printf("\n\n");
}

float zapremina(Lopta* s, char* b)
{
  float zapremina = 0;
  while(s)
    {
      if(strcmp(s->boja, b)==0)
      {
        printf("%s - %f \n", s->boja, s->poluprecnik);
        zapremina += ((s->poluprecnik)*(s->poluprecnik)*(s->poluprecnik))* 3.14 * (float)4/3;
      }
      s = s->sljedeci;
    }
  return zapremina;
}

void boji(Lopta * s, int i, char* b)
{
  int ind = 0;
  while(s && ind < i)
    {
      ind++;
      s = s->sljedeci; 
    }
  strcpy(s->boja, "");
  strcpy(s->boja, b);
  
}

int main(){
  
  FILE * f = fopen("ulaz.txt", "r");
  
  Lopta *l = NULL;
  
  float br;
  int ind = 0;
  while(!feof(f))
    {
      char * s = malloc(10);
      fscanf(f, "%f %s", &br, s);
      if(provjera(s)==0)
        continue;
      dodaj(&l, br, s);
        
    }
  
  ispis(l);
  printf("zapremina: %f\n\n", zapremina(l, "zuta"));
  boji(l, 3, "bebitza");
  ispis(l);
}
