#include <stdio.h>
#include <string.h>
#define LENGTH 1024

int n;
unsigned char palavra[LENGTH], *p = palavra;
int ocorrencias[256] = {0}, *oc = ocorrencias;
int nld; 
unsigned char letra[256], *l = letra;
int ocorrencias_letra[256], *ocl = ocorrencias_letra;
unsigned char v[LENGTH];

void print_anag() {
  for (int i = 0; i < n; i ++)
    printf("%c ", (char) v[i]);
  printf("\n");
}

void enum_anag(int i){
  if (i == n) {
    print_anag();
    return;
  }

  for (int j = 0; j < nld; j ++) 
    if (ocl[j]) {
      v[i] = l[j];
      ocl[j] --;
      enum_anag(i + 1);
      ocl[j] ++;
    }
}

int main() {
  if (scanf("%s", p) <= 0) {
    fprintf(stderr, "Erro: entrada incorreta.\n");
    return 1;
  }

  n = strlen((char *) p);

  for (int i = 0; i < n; i ++)
    oc[(int) p[i]] ++;

  nld = 0;
  for (int i = 0; i < 256; i ++)
    if (oc[i] != 0) {
      l[nld] = (unsigned char) i;
      ocl[nld] = oc[i];
      nld ++;
    }
  
  printf("\n#%s#\n", l);

  enum_anag(0);
  return 0;
}
