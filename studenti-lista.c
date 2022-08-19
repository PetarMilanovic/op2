#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Ispit{
  unsigned int indeks_studenta;
  double broj_poena;
  char oznaka[4];
  struct Ispit *sljedeci;
}Ispit;


void ispis_strukture(Ispit *l){

  do{
    printf("broj indeksa: %d\n", l->indeks_studenta);
    printf("broj bodova: %lf\n", l->broj_poena);
    printf("ucionica: %s\n\n", l->oznaka);
    l = l->sljedeci;
  }while(l->sljedeci!=NULL);
  printf("broj indeksa: %d\n", l->indeks_studenta);
    printf("broj bodova: %lf\n", l->broj_poena);
    printf("ucionica: %s\n\n", l->oznaka);
    l = l->sljedeci;
}


void dodaj(Ispit **l, unsigned int ind, double poen, char *ucionica){
  if(*l==NULL){
    *l = (Ispit*)malloc(sizeof(Ispit));
    (*l) -> indeks_studenta = ind;
    (*l) -> broj_poena = poen;
    strcpy((*l)->oznaka, ucionica);
    (*l)->sljedeci = NULL; 
  }
  else
  {
    Ispit * posljednji = *l;

    while(posljednji->sljedeci != NULL)
      {
        posljednji = posljednji->sljedeci;
      }
    
    posljednji->sljedeci = (Ispit*)malloc(sizeof(Ispit));

    Ispit * novi = posljednji->sljedeci;
    novi->broj_poena = poen;
    novi->indeks_studenta = ind;
    strcpy(novi->oznaka, ucionica);
    
    novi->sljedeci = NULL;
    
  }
}


void polozili_u_ucionici(Ispit* s, char* ucionica){
  
  while(s!=NULL){
    if(s->broj_poena>=50.99 && strcmp(s->oznaka,ucionica)==0){
      printf("Polozio student indeksa: %d\n",s->indeks_studenta);
    }
    s = s->sljedeci;
  }

}


void deleteNode(Ispit** s, int godina_upisa)
{
      Ispit *temp;

      if((((*s)->indeks_studenta)/10000) == godina_upisa)
      {
          temp = *s;    
          *s = (*s)->sljedeci;
          free(temp);
      }
      else
      {
          Ispit *posljednji  = *s;
          while(posljednji->sljedeci != NULL)
          {
              if(((posljednji->sljedeci->indeks_studenta)/10000) == godina_upisa)
              {
                  temp = posljednji->sljedeci;
                  posljednji->sljedeci = posljednji->sljedeci->sljedeci;
                  free(temp);
                  break;
              }
              else
                  posljednji = posljednji->sljedeci;
          }
      }
}


int main(int argc, char* argv[]) {

  Ispit *lista = NULL;

  FILE * f = fopen("ulaz.txt", "r"); 
  unsigned int ind = 0;
  double poen;
  char *ucionica;

  while(!feof(f))
    {
      ucionica = malloc(sizeof(4));
      fscanf(f, "%d %lf %s", &ind, &poen, ucionica);
      //printf("%d %lf %s\n", ind, poen, ucionica);
      dodaj(&lista, ind, poen, ucionica);
      
    }

  fclose(f);
  ispis_strukture(lista);
  polozili_u_ucionici(lista, "amf");
  printf("\nobrisano ko fol\n\n");
  deleteNode(&lista, 2017);
  ispis_strukture(lista);


    return 0;
}




