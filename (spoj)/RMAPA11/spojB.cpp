#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <set>
using namespace std;

#define MAX_VERTICES 600
#define INF  (MAX_VERTICES * 510)

typedef struct No No;
struct No {
    int u, c;
    No (int _u, int _c) {
        u = _u;
        c = _c;
    }
    No(){}
};

bool operator< (const No &n1, const No &n2) {
    if (n1.c != n2.c)
        return n1.c < n2.c;
    return n1.u < n2.u;
}

int G[MAX_VERTICES][MAX_VERTICES], usado[MAX_VERTICES], N, M;

int prim () {
    int v, ret = 0;
    No no;
    set <No> V;

    memset (usado, 0, sizeof (usado));
    V.insert (No (0, 0));

    while (V.size () > 0) {
        no = *V.begin();
        V.erase(V.begin());
        if (usado[no.u])
            continue;

        usado[no.u] = 1;
        ret += no.c;

        for (v = 0; v < N; v++)
            if (!usado[v] && G[no.u][v] != INF)
                V.insert (No (v, G[no.u][v]));
    }
    return ret;
}


int main () {
    int i, u, v, c;

    scanf ("%d %d", &N, &M);

    for (u = 0; u < N; u++)
        for (v = 0; v < N; v++)
            G[u][v] = INF;

    for (i = 0; i < M; i++) {
        scanf ("%d %d %d", &u, &v, &c);
        u--;v--;G[u][v] = G[v][u] = c;
    }
    printf ("%d\n", prim ());
    return 0;
}
