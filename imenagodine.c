#include <stdio.h>

int pomocna_y(char *niska, char *god){
  for(int i=0;i<4;i++){
    if(niska[i]!=god[i])
      return -1;
  }
  return 1;
}


int pomocna_n(char *niska, char *ime){
  for(int i=0;niska[i]!='\0';i++){
    if(niska[i]!=ime[i])
      return -1;
  }
  return 1;
}


void print_y(char *ime[], char *broj[], int n, char *god){
  for(int i=0; i<n; i++){
    if(pomocna_y(broj[i],god)==1)
      printf("-- %s je upisao/la faks %s godine\n", ime[i], god);

  }
  printf("\n");
}

void skrati(char * god)
{
  for(int i = 0; i < 4; i++)
    {
      printf("%c", *(god++));
    }
  printf("\n");
}

void print_n(char *ime[], char *broj[], int n, char *imence){
    for(int i=0; i<n; i++){
      if(pomocna_n(ime[i],imence)==1){
          printf("%s je upisao/la faks godine\n", imence);
        skrati(broj[i]);
        }
  }
  printf("\n");
}




int main(int argc, char *argv[]) {

  int n;

  scanf("%d", &n);
  char *ime[n];
  char *broj[n];


  for(int i=0;i<n;i++){
    ime[i] = (char*)malloc(sizeof(char)*31);
    broj[i] = (char*)malloc(sizeof(char)*8);
    scanf("%s %s", broj[i], ime[i]);
  }

  /*for(int i = 0; i < n ; i++)
    printf("ime: %s \t index: %s\n", ime[i], broj[i]);*/


  /*char * godina = "2010";
  char * imence = "ana";

  print_y(ime, broj, n, godina);
  print_n(ime, broj, n, imence);*/

  if(argv[1][1] == 'y')
  {
    char * godina = argv[2];
    print_y(ime, broj, n, godina);
  }
  else if(argv[1][1] == 'n')
  {
    char * imence = argv[2];
    print_n(ime, broj, n, imence);
  }

  return 0;
}
