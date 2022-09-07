#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Ispit{
  unsigned int indeks;
  double br_poena;
  char ucionica[4];
  struct Ispit *sljedeci;
}Ispit;


void dodaj(Ispit **i, unsigned int ind, double poeni, char ucionica[]){
  if(*i == NULL){
    *i = malloc(sizeof(Ispit));

    (*i)->indeks = ind;
    (*i)->br_poena = poeni;
    strcpy((*i)->ucionica, ucionica);
    (*i)->sljedeci = NULL;
  }
  else{
    Ispit *temp = *i;

    while(temp->sljedeci != NULL){
      temp = temp->sljedeci;
    }

    temp->sljedeci = malloc(sizeof(Ispit));
    Ispit *novi = temp->sljedeci;

    novi->indeks = ind;
    novi->br_poena = poeni;
    strcpy(novi->ucionica, ucionica);
    novi->sljedeci = NULL;
  }
}


void ispis(Ispit *i){

  while(i != NULL){
    printf("%u %.2lf %s\n", i->indeks, i->br_poena, i->ucionica);
    i = i->sljedeci;
  }
  printf("\n\n");
}


int provjeri(unsigned int ind, double poeni, char ucionica[]){
  
  if(ind < 0){
    return -1;
  }
  if(poeni < 0 || poeni > 100){
    return -1;
  }
  if(strcmp(ucionica, "rac") == 0 || strcmp(ucionica, "amf") == 0 || strcmp(ucionica, "3") == 0 || strcmp(ucionica, "4") == 0){
    return 1;
  }
  else{
    return -1;
  }
  
}

void polozili_u_ucionici(Ispit *i, char *ucionica){
  
  while(i != NULL){
    if(i->br_poena > 50.99 && strcmp(i->ucionica, ucionica) == 0){
      printf("%u\n", i->indeks);
    }
    i = i->sljedeci;
  }
}


void obrisi(Ispit **i, int godina_upisa)
{
  
  if(((*i)->indeks / 1000) == godina_upisa){
    Ispit *temp = *i;
    *i = (*i)->sljedeci;
    free(temp);
  }
    Ispit *komso = *i;

    while(komso->sljedeci != NULL){
      if((komso->sljedeci->indeks / 1000) == godina_upisa){
       Ispit *temp = komso->sljedeci;
       komso->sljedeci = komso->sljedeci->sljedeci;
       free(temp); 
      
    }
      else
        komso = komso->sljedeci;
    }
}


int main() {

  FILE *f = fopen("ulaz.txt", "r");

  Ispit *i = NULL;
  unsigned int ind;
  double poeni;
  char ucionica[4];
  
  while(!feof(f)){
    fscanf(f, "%u %lf %s", &ind, &poeni, ucionica);
    if(provjeri(ind, poeni, ucionica) == -1){
      continue;
    }
    dodaj(&i, ind, poeni, ucionica);
  }
  //polozili_u_ucionici(i, "amf");
  ispis(i);
  obrisi(&i, 2016);
  ispis(i);
  
  return 0;
}