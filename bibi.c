#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct Auto{
  char marka[10];
  int zapremina;
  float konjska_snaga;
  int cijena;
  struct Auto *sljedeci;
  struct Auto *prethodni;
}Auto;


void dodaj(Auto **a, Auto **e, char * mar, int zapr, float snaga, int pare){
  if(*a == NULL){
    *a = malloc(sizeof(Auto));

    strcpy((*a)->marka, mar);
    (*a)->zapremina = zapr;
    (*a)->konjska_snaga = snaga;
    (*a)->cijena = pare;
    (*a)->sljedeci = NULL;
    (*a)->prethodni = NULL;
    *e = *a;
  }
  else{
    Auto *stari_kraj = *e;
    stari_kraj->sljedeci = malloc(sizeof(Auto));
    *e = stari_kraj->sljedeci;
    (*e)->prethodni = stari_kraj;

    strcpy((*e)->marka, mar);
    (*e)->zapremina = zapr;
    (*e)->konjska_snaga = snaga;
    (*e)->cijena = pare;

  }
}

void ispis(Auto *a){
  while(a){
    printf("%s %d %.2f %d\n", a->marka, a->zapremina, a->konjska_snaga, a->cijena);
    a = a->sljedeci;
  }
  printf("\n");
  
}

void izOpsega(Auto* s, int c_od, int c_do)
{
  while(s != NULL){
    if(s->cijena >= c_od && s->cijena <= c_do){
      printf("%s %d %.2f %d\n", s->marka, s->zapremina, s->konjska_snaga, s->cijena);
    }
      s = s->sljedeci;
  }
}

void obrisi(Auto ** s, Auto ** end, float ks)
{
  if((*s)==NULL)
    return;
  else if((*s)->konjska_snaga == ks)
  {
    Auto * temp = *s;
    *s = (*s)->sljedeci;
    free(temp);
  }
  else if((*end)->konjska_snaga == ks)
  {
    Auto * temp = *end;
    *end = (*end)->prethodni;
    (*end)->sljedeci = NULL;
    free(temp);
  }
  else
  {
    Auto * temp = *s;
    while(temp->sljedeci!=NULL)
      {
        if(temp->sljedeci->konjska_snaga == ks)
        {
          Auto * brishi = temp->sljedeci;
          temp->sljedeci = temp->sljedeci->sljedeci;
          temp->sljedeci->prethodni = temp;
          free(brishi);
        }
        else
          temp = temp->sljedeci;
      }
    
  }
}

int main(){
  FILE *f = fopen("ulaz.txt", "r");

  char marka[10];
  int zapremina;
  float konjska_snaga;
  int cijena;

  Auto * lista = NULL;
  Auto * kraj = NULL;
  
  while(!feof(f)){
    fscanf(f, "%s %d %f %d", marka, &zapremina, &konjska_snaga, &cijena);
    dodaj(&lista, &kraj, marka, zapremina, konjska_snaga, cijena);
  }
  ispis(lista);

  //izOpsega(lista, 2000, 7000);
  obrisi(&lista, &kraj, 90);
  ispis(lista);
  obrisi(&lista, &kraj, 43.50);
  ispis(lista);
  obrisi(&lista, &kraj, 69.00);
  ispis(lista);
  
}
