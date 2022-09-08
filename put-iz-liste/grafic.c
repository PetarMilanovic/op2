#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct cvor
{
  int broj;
  struct cvor * sljedeci;
}cvor;

typedef struct ls
{
  cvor * komsho;
}lista_susjeda;

typedef struct graf
{
  int n;
  lista_susjeda * sus;
}graf;

void dodaj(cvor ** c, int br)
{
  if(*c == NULL)
  {
    *c = malloc(sizeof(cvor));
    (*c)->broj = br;
    (*c)->sljedeci = NULL;
  }
  else
  {
    cvor * krajic = *c;
    while(krajic->sljedeci != NULL)
      krajic = krajic->sljedeci;

    krajic->sljedeci = malloc(sizeof(cvor));
    cvor * novi = krajic->sljedeci;
    novi->broj = br;
    novi->sljedeci = NULL;
  }
}

graf * create_graph(char * lokacija)
{
  FILE * f = fopen(lokacija, "r");
  graf * g = malloc(sizeof(graf));
  
  fscanf(f, "%d", &g->n);

  g->sus = malloc(sizeof(lista_susjeda)*g->n);
  for(int i = 0; i < g->n; i++)
    g->sus[i].komsho = NULL;

  int u = 0;
  int br;
  while(!feof(f))
    {
      fscanf(f, "%d", &br);
      if(br!=-1)
        dodaj(&g->sus[u].komsho, br);
      else
        u++;
    }
 
  fclose(f);
 
  return g;
}

void ispis(cvor * c)
{
  if(c == NULL)
    printf("{}\n\n");
  else{
  printf("{");
  while(c->sljedeci)
    {
      printf("%d, ", c->broj);
      c = c->sljedeci;
    }
  printf("%d}\n\n\n", c->broj);
    }
}

void print(graf * g)
{
  for(int i = 0; i < g->n; i++)
    {
      printf("index: %d\nlista susjeda:\n", i);
      ispis(g->sus[i].komsho);
    }
}


cvor * create_lista(char * lokacija)
{
  FILE * f = fopen(lokacija, "r");
  cvor *l = NULL;
  
  int br;
  while(!feof(f))
    {
      fscanf(f, "%d", &br);
      if(br!=-1)
        dodaj(&l, br);
      else
        break;
    }
 
  fclose(f);
 
  return l;
}

void izbaci(cvor ** lista)
{
  cvor * temp =  *lista;
  *lista = (*lista)->sljedeci;
  free(temp);
}

cvor * kopiraj(cvor * lista)
{
  cvor * kopija = NULL;
  while(lista)
    {
      dodaj(&kopija, lista->broj);
      lista = lista->sljedeci;
    }
  return kopija;
}

int duzina(cvor * lista)
{
  int br = 0;
  while(lista)
    {
      br+=1;
      lista = lista->sljedeci;
    }
  return br;
}

int u_listi(cvor *lista, int trazeni)
{
  while(lista)
    {
      if(lista->broj == trazeni)
        return 1;
      lista = lista->sljedeci;
    }
  return -1;
}


int provjeri(graf *g, cvor ** lista, int dubina, int duzina, int obidjeni[], int put[])
{
  if(dubina == 0 && *lista == NULL)
    return 1;

  int trenutni = (*lista)->broj;
  izbaci(lista);
  cvor * komso = g->sus[trenutni].komsho;
  while(komso)
    {
      if(obidjeni[komso->broj]==0 && u_listi(*lista, komso->broj)==1)
      {
        obidjeni[komso->broj] = 1;
        put[duzina-dubina] = komso->broj;
        provjeri(g, lista, dubina-1, duzina, obidjeni, put);
      }
      komso = komso->sljedeci;
    }
  
}

int vrati(cvor *l, int ind)
{
  int i = 0;
  while(l != NULL && i < ind)
    l = l->sljedeci;
  return l->broj;
}

int main()
{
  graf *g = create_graph("ulaz.txt");
  print(g);
  cvor * l = create_lista("lista.txt");
  ispis(l);


  for(int i = 0; i < duzina(l);i++)
    {
      cvor * kopija = kopiraj(l);
    
      int *obidjeni = (int*)calloc(10, sizeof(int));
      int *put = (int*)calloc(5, sizeof(int));
    
      obidjeni[vrati(kopija, i)] = 1;
      put[0] = vrati(kopija, i);
      
      //izbaci(kopija, vrati(kopija, i));
      int br = provjeri(g, &l, 4, 5, obidjeni, put);
      printf("put u grafu g... %d\n\n", br);
      for(int i = 0; i < 5; i++)
      printf("%d - ", put[i]);
    }
  
  return 0;
}