#include <stdio.h>

int n;
int *v;

void print_subset()
{
  for (int i = 0; i < n; i ++)
    printf("%d", v[i]);
  printf("\n");  
}

void enum_subsets(int n)
{
  if (n > 0) {
    v[-- n] = 0;
    enum_subsets(n);
    v[n] = 1;
    enum_subsets(n);
  } else {
    print_subset();
  }  
}

int main() {
  if (scanf("%d", &n) != 1) {
    fprintf(stderr, "Erro: entrada incorreta.\n");
    return 1;
  }

  int vetor[n];
  v = vetor;

  enum_subsets(n);
  return 0;
}
