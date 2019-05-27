#include <stdio.h>
#include <assert.h>
#include <string.h>

#define MAX_VERTICES 600
#define INF          (MAX_VERTICES * 510)

int G[MAX_VERTICES][MAX_VERTICES],
    usado[MAX_VERTICES],
    custo[MAX_VERTICES],
    N, M;

int
prim () {
    int i, u, v, cnt, ret = 0;

    for (i = 0; i < N; i++) {
        usado[i] = 0;
        custo[i] = INF;
    }

    custo[0] = 0;

    for (cnt = 0; cnt < N; cnt++) {
        u = -1;
        for (v = 0; v < N; v++)
            if (!usado[v] && (u == -1 || custo[v] < custo[u]))
                u = v;

        assert (custo[u] < INF);
        usado[u] = 1;
        ret += custo[u];

        for (v = 0; v < N; v++)
            if (custo[v] > G[u][v])
                custo[v] = G[u][v];
    }
    return ret;
}


int
main () {
    int i, u, v, c;

    scanf ("%d %d", &N, &M);

    for (u = 0; u < N; u++)
        for (v = 0; v < N; v++)
            G[u][v] = INF;

    for (i = 0; i < M; i++) {
        scanf ("%d %d %d", &u, &v, &c);
        u--;
        v--;
        G[u][v] = G[v][u] = c;
    }
    printf ("%d\n", prim ());
    return 0;
}
