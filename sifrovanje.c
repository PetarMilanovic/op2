#include <stdio.h>

int duzina(char *s) {
  int i;
  for (i = 0; s[i] != '\0'; i++) {
  }

  return i;
}

char *sifruj(char *s, int n) {
  char *nova = (char *)malloc(sizeof(char) * (duzina(s) + 5));
  char *at = "[AT]";

  int i, j;
  for (i = 0; s[i] != '@'; i++) {
    if ((s[i] >= 'a' && s[i] <= 'z')) {
      nova[i] = s[i] + n;
    }
  }

  for (j = i; j < i + 4; j++)
    nova[j] = *(at++);

  i++;
  for (int k = i; s[k] != '\0'; k++) {
    if ((s[k] >= 'a' && s[k] <= 'z')) {
      nova[j] = s[k] + n;
      j++;
    } else {
      nova[j] = s[k];
      j++;
    }
  }

  return nova;
}

int main(int argc, char *argv[]) {

  int n;

  char mejl[50] = "milanpredojevic@gmail.com";

  char *nova = sifruj(mejl, 3);

  printf("%s - sifrovano", nova);

  return 0;
}