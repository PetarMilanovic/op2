#include "graf.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

int prebroj(char lokacija[]) {
  FILE *ulaz = fopen(lokacija, "r");
  if (ulaz == NULL) {
    printf("Greska: neuspesno otvaranje datoteke %s.\n", lokacija);
    return -1;
  }

  int br = 0;
  char buf[10];

  while (!feof(ulaz)) {
    fgets(buf, 10, ulaz);
    br += 1;
  }

  return br;
}


void nadji_naj(graf * g)
{
  float max = -1;
  int indi = -1;
  int ind_i = -1;

  for(int i = 0; i < g->n; i++)
    {
      while(g->sus[i].u!= NULL)
        {
          if(g->sus[i].u->tezina > max)
          {
            max = g->sus[i].u->tezina;
            indi = g->sus[i].u->ind;
            ind_i = i;
          }
          g->sus[i].u = g->sus[i].u->sljedeci;
        }
    }

  printf("Najveca duzina, %.2f, je izmedju cvorova: %d i %d\n", max, ind_i, indi);
}



float jesul_komshe(interval *prvi, interval *drugi) {
  float l1 = prvi->x;
  float r1 = prvi->y;

  float l2 = drugi->x;
  float r2 = drugi->y;

  float tezina = -1;


  if(l1 == l2 && r1 == r2)
    return -1;
  if((l1 >= l2) && (r1 <= r2))
    return fabs(r1-l1);
  if((l2 >= l1) && (r2 <= r1))
    return fabs(r2-l2);
  if((r2 >= l1)&& (l2 <= l1))
    return  fabs(r2-l1);
  if((r1 >= l2)&& (l1 <= l2))
    return  fabs(r1-l2);
  if((l2 <= r1) && (r2 >= r1))
    return fabs(r1-l2);
  if((l1 <= r2) && (r1 >= r2))
    return fabs(r2-l1);

  return tezina;

}

graf *create_graph(char lokacija[]) {

  FILE *ulaz = fopen(lokacija, "r");
  if (ulaz == NULL) {
    printf("Greska: neuspesno otvaranje datoteke %s.\n", lokacija);
    return NULL;
  }

  graf *g = (graf *)malloc(sizeof(graf));

  g->n = prebroj(lokacija);
  g->sus = (lista_susjeda *)malloc(g->n * sizeof(lista_susjeda));

  for (int v = 0; v < g->n; v++) {
    g->sus[v].u = NULL;
    g->sus[v].lista_intervala = NULL;
  }

  int v = 0;
  while (!feof(ulaz)) {
    float lijevi, desni;
    fscanf(ulaz, "%f, %f", &lijevi, &desni);
    add_list_int(&(g->sus[v].lista_intervala), lijevi, desni);
    v++;
  }

  for (int i = 0; i < g->n; i++) {
    for (int j = 0; j < g->n; j++) {
      float tezina =
          jesul_komshe(g->sus[i].lista_intervala, g->sus[j].lista_intervala);
      if (tezina != -1) {
        add_list(&g->sus[i].u, j, tezina);
      }
    }
  }
  fclose(ulaz);

  return g;
}

void printg(graf *g) {
  for (int i = 0; i < g->n; i++) {
    printf("index: %d ", i);
    print(g->sus[i].lista_intervala);
    printc(g->sus[i].u);
  }
}

void print(interval *l) {

  if (l == NULL)
    printf("{}");
  else {
    printf("{");

    while (l->sljedeci != NULL) {
      printf("[%.2f, %.2f],  ", l->x, l->y);
      l = l->sljedeci;
    }
    printf("[%.2f, %.2f]}", l->x, l->y);
  }
  printf("\n");
}

void printc(cvor *l) {

  if (l == NULL)
    printf("{}");
  else {
    printf("{");

    while (l->sljedeci != NULL) {
      printf("[[%d] - %.3f],  ", l->ind, l->tezina);
      l = l->sljedeci;
    }

    printf("[[%d] - %.3f]}", l->ind, l->tezina);
  }
  printf("\n\n");
}

void add_list_int(interval **l, float li, float de) {
  if (*l == NULL) {
    *l = (interval *)malloc(sizeof(interval));
    (**l).x = li;
    (**l).y = de;
    (*l)->sljedeci = NULL;
  } else {
    interval *posljednji = *l;
    while (posljednji->sljedeci != NULL)
      posljednji = posljednji->sljedeci;

    posljednji->sljedeci = (interval *)malloc(sizeof(interval));

    interval *novi = posljednji->sljedeci;

    novi->x = li;
    novi->y = de;
    novi->sljedeci = NULL;
  }
}

void add_list(cvor **l, int in, float tezina) {
  if (*l == NULL) {
    *l = (cvor *)malloc(sizeof(cvor));
    (**l).ind = in;
    (**l).tezina = tezina;
    (*l)->sljedeci = NULL;
  } else {
    cvor *posljednji = *l;
    while (posljednji->sljedeci != NULL)
      posljednji = posljednji->sljedeci;

    posljednji->sljedeci = (cvor *)malloc(sizeof(cvor));

    cvor *novi = posljednji->sljedeci;

    novi->ind = in;
    novi->tezina = tezina;
    novi->sljedeci = NULL;
  }
}