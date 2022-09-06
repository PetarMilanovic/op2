#include <stdio.h>
#include <stdlib.h>
#include <string.h>


//gas gas


int provjera(char *s1){
  if(s1[1] == 'x'){
    return 1;
  }else{
    return 0;
  }
}


int main()
{
  FILE *f = fopen("u2.txt", "r");

  char *lijevi[6];
  char *desni[6];
  int i = 0;

  while(!feof(f)){
    lijevi[i] = malloc(10);
    desni[i] = malloc(10);
    
    fscanf(f, "%s %s", lijevi[i], desni[i]);
    
    i++;
    
  }

  char *broj;
  for(int j = 0; j < i; j++)
    {
      if(provjera(lijevi[j])==0)
        broj = lijevi[j];
      for(int k = 0; k < i; k++)
        {
          if(strcmp(desni[j], lijevi[k])==0)
            printf("broj:%s \t adresa %s\n", broj, desni[k]);
        }
      
    }
  
  return 0;
}