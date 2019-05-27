#include <stdio.h>

void enum_subsets(int n)
{
  long N = 1 << n;

  for (long l = 0; l < N; l ++) {
    int mask = 1;
    for (int i = 0; i < n; i ++) {
      if (l & mask)
	printf("1");
      else
	printf("0");
      mask = mask << 1;
    }
    printf("\n");
  }
}

int main() {
  int n;
  
  if (scanf("%d", &n) != 1) {
    fprintf(stderr, "Erro: entrada incorreta.\n");
    return 1;
  }

  if (n > 63) {
    fprintf(stderr, "Impossível enumerar.\n");
    return 1;
  }
  
  enum_subsets(n);
  return 0;
}
