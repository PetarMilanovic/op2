#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct Grad{
  char grad[15];
  int temperatura[13];
  struct Grad * sljedeci;
  struct Grad * prethodni;
}Grad;

void nizcpy(int * gdje, int * koga)
{
  gdje[0] = 69;
  for(int i = 1; i < 13; i++)
    {
      gdje[i] = koga[i];
    }
}

void dodaj(Grad **g, Grad **p, char grad[], int temperatura[]){
  if(*g == NULL){
    *g = malloc(sizeof(Grad));

    strcpy((*g)->grad, grad);
    nizcpy((*g)->temperatura, temperatura);
    (*g)->sljedeci = NULL;
    (*g)->prethodni = NULL;

    *p = *g;
  }
  else{
    Grad *stari_kraj = *p;
    
    stari_kraj->sljedeci = malloc(sizeof(Grad));
    *p = stari_kraj->sljedeci;
    
    strcpy((*p)->grad, grad);
    nizcpy((*p)->temperatura, temperatura);
    
    (*p)->sljedeci = NULL;
    (*p)->prethodni = stari_kraj;
  }
  
}


void naj_grad(Grad *l, int index)
{
  int i = 0;
  
  while(i<index)
    {
      i+=1;
      l = l->sljedeci;
    }
  printf("grad sa najhladnijom temp u trazenom mjesecu je: %s \n\n",l->grad);
}


void najhladniji(Grad *l, int mjesec)
{
  Grad * kopija = l;
  int ind = 0;
  int index = 0;
  int min = 420;
  while(l!=NULL)
    {
      if(l->temperatura[mjesec] < min)
      {
        min = l->temperatura[mjesec];
        index = ind;
      }
      ind++;
      l = l ->sljedeci;
    }
  naj_grad(kopija, index);
}

int provjera(int * niz, int temperatura){

  for(int i=1; i<13; i++){
    if(niz[i] == temperatura){
      return 1;
    }
  }
  return -1; 
}

void obrisi(Grad ** l, Grad ** kraj, int temperatura)
{
  if(provjera((*l)->temperatura, temperatura) == 1){
    Grad *temp = *l;
    (*l) = (*l)->sljedeci;
    free(temp);
  }
  else if(provjera((*kraj)->temperatura, temperatura) == 1){
    Grad *temp = *kraj;
    (*kraj) = (*kraj)->prethodni;
    (*kraj)->sljedeci = NULL;
    free(temp);
  }
  else{
    Grad *komso = *l;
    // 1, 2, 3, 4, 5, 6, 5
    // komso = 2
    // komso->sljedeci = 3
    // temp = 3
    // komso->sljedeci = komso->sljedeci->sljedeci; 3 = 4
    // komso->sljedeci->prethodni = komso; 4->prethodni = 2

    while(komso->sljedeci != NULL){
      if(provjera(komso->sljedeci->temperatura, temperatura) == 1){
        Grad *temp = komso->sljedeci;
        komso->sljedeci = komso->sljedeci->sljedeci;
        komso->sljedeci->prethodni = komso;
        free(temp);
      }
      else
        komso = komso->sljedeci;
    }
  }
  
}

void printniz(int * niz)
{
  printf("[");
  for(int i = 1; i < 12; i++)
    printf("%d, ", niz[i]);
  printf("%d]\n\n\n", niz[12]);
}

void print(Grad * l)
{
  while(l)
    {
      printf("Naziv grada: %s\nTemperatura:\n", l->grad);
      printniz(l->temperatura);
      l = l->sljedeci;
    }
}


int * parsiraj(char * str)
{
  int *niz = (int *)malloc(sizeof(int)*13);
  niz[0] = 69;
  int offset;
  int broj;
  int ind = 1;
  while(sscanf(str, "%d%n", &broj, &offset)==1)
    {
      niz[ind] = broj;
      str+=offset;
      ind++;
    }
  return niz;
}


int main() {

  FILE *f = fopen("ulaz.txt", "r"); 


  Grad *g = NULL;
  Grad *p = NULL;

  char* ime = malloc(sizeof(char)*30);
  char* temp = malloc(sizeof(char)*40);
  
  while(!feof(f)){
    fgets(ime, 30, f);
    fgets(temp, 40, f);
    int * niz = parsiraj(temp);
    dodaj(&g, &p, ime, niz);
  }
  //print(g);
  //najhladniji(g, 4);
  obrisi(&g, &p, 3);
  print(g);
  return 0;
}