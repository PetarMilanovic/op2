#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct Lopta{
  float poluprecnik;
  char boja[8];
  struct Lopta * sljedeci;
}Lopta;

char * strcpynas(char * izvor, char * destinacija)
{
  int duzina = strlen(izvor)+1;
  int i;
  for(i = 0; i < duzina; i++)
    destinacija[i] = izvor[i];

  destinacija[i+1] = '\0';
  return destinacija;
}

void dodaj(Lopta **l, float pp, char *b){
  if(*l==NULL){
    *l=(Lopta*)malloc(sizeof(Lopta));
    (*l)->poluprecnik=pp;
    strcpy((*l)->boja, b);
    (*l)->sljedeci=NULL;
  }
  else{
    Lopta * posljednji = *l;
    
    while(posljednji->sljedeci != NULL){
      posljednji = posljednji -> sljedeci;
    }

    posljednji->sljedeci = (Lopta*)malloc(sizeof(Lopta));

    Lopta * novi = posljednji->sljedeci;

    novi->poluprecnik = pp;
    strcpy(novi->boja, b);
    novi->sljedeci = NULL;
    
  }
  
}

void ispis(Lopta* l){
  while(l!=NULL){
    printf("Poluprecnik: %.2f\n",l->poluprecnik);
    printf("Boja: %s\n",l->boja);
    l=l->sljedeci;
    }
}

float zapremina(Lopta* s, char* b)
{
  float suma = 0;

  while(s != NULL){
    if(strcmp(b, s->boja) == 0){
      printf("%s - %s", s->boja, b);
      float zapr = (4/3) * 3.14 * (s->poluprecnik) * (s->poluprecnik) * (s->poluprecnik);
      suma += zapr; 
    }
    s = s->sljedeci;
  }

  return suma;
}


void boji(Lopta * s, int i, char* b)
{
  int index = 0;
  while(s!=NULL && index < i){
    index+=1;
    s=s->sljedeci;
  }
  
  strcpy(s->boja, "");
  strcpy(s->boja, b);
  
}

int main(int argc, char* argv[]) {

  FILE * f = fopen("ulaz.txt", "r");

  Lopta *l = NULL;
 
  float pp;
  char *b;
  
  while(!feof(f)){
    b = (char *)malloc(sizeof(char)*8);
    fscanf(f, "%f %s", &pp, b);
    dodaj(&l,pp,b);
  }
  ispis(l);
  boji(l, 1, "zuta");
  printf("\n\n\n");
  ispis(l);
  float gn = zapremina(l, "plava");
  printf("\n\n\n %.2f\n", gn);
  ispis(l);

  
  return 0;
}
