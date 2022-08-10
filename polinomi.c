#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct koeficijenti
{
  float vrijednost;
  struct koeficijenti * sljedeci;
}Koeficijenti;

typedef struct polinom
{
  int stepen;
  Koeficijenti * niz;
}Polinom;


void dodaj_u_listu(Koeficijenti** l, float a)
{
    if(*l==NULL){
        *l = (Koeficijenti*)malloc(sizeof(Koeficijenti));
        (**l).vrijednost = a;
        //(*l)->broj = a; // ili (**l).broj = a;
        (*l)->sljedeci = NULL;
    }
    else
    {
        Koeficijenti* posljednji = *l;
        while(posljednji->sljedeci != NULL)
            posljednji = posljednji->sljedeci;

        posljednji->sljedeci = (Koeficijenti*)malloc(sizeof(Koeficijenti));

        Koeficijenti* novi = posljednji->sljedeci;

        novi->vrijednost = a;
        novi->sljedeci = NULL;
    }
}


void printc(Koeficijenti *k)
{
  if(k == NULL)
  {
    printf("{}");
  }else{
    printf("{");
    
    while(k -> sljedeci != NULL){
      printf("%.2f, ", k -> vrijednost);
      k = k -> sljedeci;
    }

    printf("%.2f}\n", k -> vrijednost);
  }
}


Polinom * integral(Polinom pl, float C)
{

  Polinom *p = &pl;
  
  int st = p->stepen;

  for(int i=0; i<=st; i++){
    float vr = p->niz->vrijednost;
    //printf("%f\n", vr);
    
    float integral = (vr/(i+1));
     //printf("%f\n\n", integral);

    if(p->niz == NULL)
      printf("null");
  
    dodaj_u_listu(&p->niz, integral);
    
    p->niz = p->niz->sljedeci;
  }

  return p;
}


void ispis(Polinom p)
{
  //1.00 + 3.00x^2 + 1.00x^3

  printf("\n%.2f", p.niz->vrijednost);
  p.niz = p.niz->sljedeci;

  int j = 1;
  for(int i = 0; i < p.stepen; i++)
    {
      if(p.niz->vrijednost == 0)
        continue;
      if(p.niz->vrijednost > 0)
        printf("+");
      else
        printf("-");
      printf("%.2f x^%d", p.niz->vrijednost, j);
      p.niz = p.niz->sljedeci;
      j++;
    }
  
}


void koliko_stepeni(char *s, Koeficijenti ** p)
{
  int br = 0;
  float fnum;
  while(*s != '\n')
    {
      if(*s!=' ')
      {
        fnum = atof(s);
        if (fnum < 0) 
        {
          s++;
        }
        else
        { 
            br+=1; 
        }
        dodaj_u_listu(p, fnum);      
      }
      s++;            
    }
  //p.stepen = br-1;
  //p->niz = p->niz->sljedeci;

}


int main() {
  FILE *ulaz = fopen("ulaz.txt", "r");

  if(ulaz == NULL){
    printf("polinom schmolinom ne radi uwu\n");
    return -1;
  }

  int n;
  fscanf(ulaz, "%d", &n);

  Polinom * niz_p = (Polinom*)malloc(sizeof(Polinom)*n);

  niz_p->niz = (Koeficijenti*)malloc(sizeof(Koeficijenti)*n);

  for(int i = 0; i < n; i++)
    {
      niz_p[i].niz = NULL;
    }


  

  int ind = 0;
  char *stringic = (char*)malloc(sizeof(char)*50);

  Koeficijenti proba[n];

  Polinom *p;

  int brs[n];
  while(fgets(stringic, 50, ulaz)!=NULL)
    {
      printf("%s\n", stringic);
      koliko_stepeni(stringic, &proba[ind]);
      ind++;
    }

  fclose(ulaz);

 for(int i = 1; i <= n; i++)
    {
      printc(proba);
    }

  
  int stepen = 3;
  Koeficijenti *k = NULL;
  /*for(int i = 0; i < stepen+1;i++)
     {
       dodaj_u_listu(&k, i+2);
     }*/

  Polinom neki = {stepen, k};

  ispis(neki);

  /*printc(k);

  Polinom * novi = integral(neki, 5);

  printc(novi->niz);*/
  
  return 0;
}



