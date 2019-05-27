#include <iostream>
using namespace std;

int n = 56, k = 5;
  unsigned long c,  r;
  unsigned long N = 1L << n;
  unsigned long a = (1L << k) - 1;


void printb(int a){
    unsigned long b = N >> 1;
    for (int i = 0; i < n; i ++) {
      if (a & b) cout << "# ";
      else cout << ". ";
      b = b >> 1;
    }
    cout << endl;
}


int main() {

  while (a < N) {    
    printb(a);

    // Gosper’s hack, uh!!
    c = (a & -a);
    r = a + c;
    a = (((r ^ a) >> 2) / c) | r;
  }
  return 0;
}
