#include <stdio.h>
#include <string.h>


int broj(char * naziv)
{
  FILE * ulaz1 = fopen(naziv, "r");
  char buf[200];

  int br1 = 0;
  while(fgets(buf, 200, ulaz1)!=NULL)
    {
      //puts(buf);
      br1+=1;
    }
  fclose(ulaz1);
  return br1;
}

int br_rijeci(char * rec)
{
  int br = 1;
  int b = strlen(rec);

  char * recenica = rec;
  
  if(recenica[0] == ' ')
        br-=1;
  for(int i = 0; *recenica != '\0'; i++)
    {
      if(*(recenica) == ' ')
      {
        br+=1;
        while(*(recenica++)== ' ')
      
          recenica++;
      }
      recenica++;
    }
  
  if(rec[b-2] == ' ')
    br-=1;

  return br;
}

void poredi(char * rec1, char * rec2)
{
  int br1 = br_rijeci(rec1);
  int br2 = br_rijeci(rec2);


  FILE * izlaz = fopen("skoro_iste.txt", "a");
  int min = br1;
  if(br2 < min)
    min = br2;

  min = 0.7 * min;


  if(br1 > min && br2 > min)
  {
    fputs(rec1, izlaz);
    fputs("\n", izlaz);
    fputs(rec2, izlaz);
    fputs("\n\n\n", izlaz);
  }
}

int main(int argc, char* argv[]) {

  FILE *ulaz1, *ulaz2, *izlaz;

  ulaz1 = fopen("dat1.txt", "r");
  ulaz2 = fopen("dat2.txt", "r");

  int br1 = broj("dat1.txt");
  
  char *nizs[br1];
  int i = 0;
  char buf[200];
  while(fgets(buf, 200, ulaz1)!=NULL)
    {
      nizs[i] = (char*)malloc(sizeof(char)*200);
      strcpy(nizs[i], buf);
      i+=1;
    }

  fclose(ulaz1);

  
  int br2 = broj("dat2.txt");
  
  char *nizs2[br2];
  int m = 0;
  char buf2[200];
  while(fgets(buf2, 200, ulaz2)!=NULL)
    {
      nizs2[m] = (char*)malloc(sizeof(char)*200);
      strcpy(nizs2[m], buf2);
      m+=1;
    }

  fclose(ulaz2);

  printf("br rijeci: %d", br_rijeci(nizs2[0]));
  printf("\n%s", nizs2[0]);

  for(int k = 0; k < br1; k++)
    {
      for(int l = 0; l < br2; l++)
        {
          poredi(nizs[k], nizs2[l]);
        }
    }


    return 0;
}