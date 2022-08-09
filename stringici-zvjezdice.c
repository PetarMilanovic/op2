#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void zvjezdice(char *str, char *stringic) {
  int n = strlen(stringic);

  char novi[n];

  for (int i = 0; i < n; i++) {
    novi[i] = '*';
  }

  strncpy(str, novi, n);
}

void sve(char *rijec, char *stringic) {

  while (*rijec != '\n') {
    char *podstring = strstr(rijec, stringic);

    if (podstring != NULL) {
      zvjezdice(podstring, stringic);
    }
    rijec++;
  }
}

void zamijeni(char *argv[]) {
  FILE *ulaz = fopen(argv[1], "r");
  FILE *izlaz = fopen(argv[2], "w");

  char * stringic = argv[3];

  if (ulaz == NULL)
    printf("upsic.\n");

  char *rijeci = (char *)malloc(sizeof(char) * 100);

  while (fgets(rijeci, 100, ulaz) != NULL) {

    sve(rijeci, stringic);
    fputs(rijeci, izlaz);
  }

  fclose(ulaz);
  fclose(izlaz);
}

int main(int argc, char * argv[]) {

  printf("naziv programa: %s\n", argv[0]);

  zamijeni(argv);

  return 0;
}