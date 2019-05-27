#include <stdio.h>

int n;
int *v;

void print_subset()
{
  for (int i = 0; i < n; i ++)
    printf("%d", v[i]);
  printf("\n");  
}

void enum_subsets(int n, int k)
{
  if (n == 0) {
    print_subset();
    return;
  }

  if (n > k) {
    v[n - 1] = 0;
    enum_subsets(n - 1, k);
  }
  if (k > 0) {
    v[n - 1] = 1;
    enum_subsets(n - 1, k - 1);
  }
}

int main() {
  int k;
  
  if (scanf("%d", &n) != 1) {
    fprintf(stderr, "Erro: entrada incorreta.\n");
    return 1;
  }

  int vetor[n];
  v = vetor;

  if (scanf("%d", &k) != 1) {
    fprintf(stderr, "Erro: entrada incorreta.\n");
    return 1;
  }

  enum_subsets(n, k);
  return 0;
}
