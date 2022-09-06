#include <stdio.h>
#include <stdio.h>


typedef struct cvor{
  int br;
  
  struct cvor * sljedeci;
}cvor;

typedef struct lista_susjeda
{
  cvor * u;
}lista_susjeda;

typedef struct {
  int n;
  lista_susjeda * sus;
}graf;

int duzina_l(cvor * l)
{
  int br;
  while(l!=NULL)
    {
      l+=1;
      l = l->sljedeci;
    }
  return br;
}

void dodaj(cvor **cv, int b)
{
  if(*cv == NULL)
  {
    *cv = (cvor*)malloc(sizeof(cvor));
    (*cv)->br = b;
    (**cv).sljedeci = NULL;
  }
  else
  {
    cvor * temp = *cv;
    while(temp->sljedeci != NULL)
      temp = temp->sljedeci;

    temp->sljedeci = malloc(sizeof(cvor));
    cvor * novi = temp->sljedeci;
    novi->br = b;
    novi->sljedeci = NULL;
  }
  
}

graf * grafic()
{
  FILE * f = fopen("graf.txt", "r");

  graf * g = (graf*)malloc(sizeof(graf));
  fscanf(f, "%d", &g->n);

  g->sus = calloc(g->n, sizeof(lista_susjeda));
  
  int v = 0;
  while(!feof(f))
    {
      int temp;
      fscanf(f, "%d", &temp);
      if(temp!=-1)
        dodaj(&g->sus[v].u, temp);
      else
        v++;
    }
  fclose(f);
  
  return g;
}

cvor * listica()
{
  FILE * f = fopen("lista.txt", "r");

  cvor * lista = NULL;
  while(!feof(f))
    {
      int temp;
      fscanf(f, "%d", &temp);
      if(temp!=-1)
        dodaj(&lista, temp);
    }
  fclose(f);
  
  return lista;
}

void printc(cvor * cv)
{
  printf("{");
  while(cv->sljedeci!= NULL)
    {
      printf("%d, ", cv->br);
      cv = cv->sljedeci;
    }
  printf("%d}\n\n", cv->br);
}

void printg(graf * g)
{
  for(int i = 0; i < g->n; i++)
    {
      printf("indeks cv: %d ", i);
      printc(g->sus[i].u);
    }
  
}


int u = 1;
int * putic(graf *g, cvor * l, int dub, int * put, int * obidjeni)
{
  cvor * tr = l;
  obidjeni[tr->br] = 1;
  cvor * s = g->sus[tr->br].u;
 if(dub>1)
 {
     while(s!=NULL)
    {
      if(s->br == tr->sljedeci->br && obidjeni[s->br]==0)
      {
        obidjeni[s->br]=1;
        put[u] = s->br;
        u++;
        putic(g, l->sljedeci, dub-1, put, obidjeni);
       
      }  
      s = s->sljedeci;
    }
 }

  return put;
}

int main(void) {
  graf * g = grafic();

  cvor * lista = listica();
  printc(lista);
  
  printg(g);

  int *obidjeni = calloc(g->n, sizeof(int));
  int *put = calloc(duzina_l(lista), sizeof(int));

  int * puti = putic(g, lista, 4,  put, obidjeni);
  
  puti[0] = lista->br;
  for(int i = 0; i < 4; i++)
    {
      printf("%d - ", puti[i]);
    }
  
  return 0;
}




