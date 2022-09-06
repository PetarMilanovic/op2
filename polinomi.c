#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct Lista{
  float koeficijent;
  struct Lista *sljedeci;
}Lista;

typedef struct Polinom{
  int stepen;
  Lista *l;
}Polinom;


void dodaj(Lista **l, float br){
  if(*l == NULL){
    *l = malloc(sizeof(Lista));
    (**l).koeficijent = br;
    (**l).sljedeci = NULL;
  }
  else{
    Lista *temp = *l;

    while(temp->sljedeci != NULL){
      temp = temp->sljedeci;
    }
    temp->sljedeci = malloc(sizeof(Lista));

    Lista *novi = temp->sljedeci;

    novi->koeficijent = br;
    novi->sljedeci = NULL;
  }
}

void parsiraj(char *s, Polinom *p)
{
  float f;
  int offset;
  int stepen = 0;

  while(sscanf(s, " %f %n", &f, &offset)==1)
    {
      s += offset;
      stepen+=1;
      dodaj(&p->l, f);
    }
  p->stepen = stepen-1;
}


void printc(Lista * l)
{
  printf("{");
  while(l->sljedeci)
    {
      printf("%.2f, ", l->koeficijent);
      l = l->sljedeci;
    }
  printf("%.2f}", l->koeficijent);
}


void stampaj(Polinom p){
  int ind = 1;

  printf("%.2f", p.l->koeficijent);
  p.l = p.l->sljedeci;

  while(p.l != NULL){
    if(p.l->koeficijent == 0){
      p.l = p.l->sljedeci;
      ind++;
    }
    if(p.l->koeficijent < 0){
      printf(" - %.2fx^%d", fabs(p.l->koeficijent), ind);
    }
    else
    {
      printf(" + %.2fx^%d", p.l->koeficijent, ind); 
    }
    ind++;
    p.l = p.l->sljedeci;
  }
  printf("\n\n");
}


Polinom * integral(Polinom p)
{
  int ind = 1;

  Polinom * novi = malloc(sizeof(Polinom));
  novi->stepen = p.stepen;
  novi->l = NULL;
  
  while(p.l != NULL){
    dodaj(&novi->l, (p.l->koeficijent/ind)); 
    ind++;
    p.l = p.l->sljedeci;
  }
  return novi;
}

int main() {
  FILE *f = fopen("ulaz.txt", "r");

  char * s = malloc(3);
  fgets(s, 3, f);
  int n = atoi(s);
  free(s);

  Polinom * p = (Polinom*)malloc(sizeof(Polinom)*n);
  for(int i = 0; i < n; i++)
    p[i].l = NULL;

  int ind = 0;
  /*while(!feof(f)){
    char * s = malloc(5);
    fscanf(f, "%s[^\n]", s);
      dodaj(&p[ind].l, atof(s));
      ind++;
  }*/


  while(!feof(f)){
    char * s = malloc(30);
    fgets(s, 30, f);
    parsiraj(s, &p[ind]);

    free(s);
    ind++;
  }

  //stampaj(p[1]);
  Polinom * novi  = integral(p[1]);
  stampaj(*novi);
  return 0;
}


