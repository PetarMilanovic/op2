#include <stdio.h>
#include <string.h>

int jesul_isti(char *god, char *godn) {
  for (int i = 0; i < 4; i++) {
    if (godn[i] != god[i])
      return -1;
  }
  return 1;
}

int duzina(char *ime) {
  int br = 0;
  while (*ime != '\0')
    br += 1;
  return br;
}

int strcmp_nas(char *ime, char *imena) {
  int br = duzina(ime);
  for (int i = 0; i < br; i++) {
    if (imena[i] != ime[i])
      return -1;
  }
  return 1;
}

void nadji_sa_godinom(char *god, int n, char *godine[], char *imena[]) {
  for (int i = 0; i < n; i++) {
    if (jesul_isti(god, godine[i]) == 1) {
      printf("ime sa godinom: %s, ", imena[i]);
    }
  }
}

void skrati(char *godine) {
  for (int i = 0; i < 4; i++) {
    printf("%c", godine[i]);
  }
  printf("\n");
}

void nadji_sa_imenom(char *ime, int n, char *godine[], char *imena[]) {
  printf("\n");
  for (int i = 0; i < n; i++) {
    if (strcmp(ime, imena[i]) == 0) {
      printf("ime se pojavilo godine: ");
      skrati(godine[i]);
    }
  }
  printf("\n");
}

int main(int argc, char *argv[]) {

  printf("naziv programa: %s\n", argv[0]);

  char *god;
  char *ime;

  int n;
  printf("unesite koliko zelite stud:\n");
  scanf("%d", &n);

  char *veliki_god[n];
  char *veliki_ime[n];

  for (int i = 0; i < n; i++) {
    veliki_god[i] = malloc(10 * sizeof(char));
    veliki_ime[i] = malloc(30 * sizeof(char));

    scanf("%s %s", veliki_god[i], veliki_ime[i]);
  }

  if (argv[1][1] == 'y') {
    god = argv[2];
    nadji_sa_godinom(god, n, veliki_god, veliki_ime);
  } else if (argv[1][1] == 'n') {
    ime = argv[2];
    nadji_sa_imenom(ime, n, veliki_god, veliki_ime);
  }

  return 0;
}