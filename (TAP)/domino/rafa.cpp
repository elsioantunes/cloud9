/**
 * @author Rafael Cardoso da Silva 21048012
 * Tecnicas Avancadas de Programacao – 2018.Q1
 * Projeto 2: Domino
 *
 * Compile com C++ 11:
 *   g++ rafaelcardoso_tap02.cpp -o rafaelcardoso_tap02.exe -std=c++11
 */

#include <iostream>
#include <vector>

#define V true
#define PECA_NAO_USADA  0
#define PECA_USADA      1

struct peca_t {
    int a, b, used;
};

int N, K;
//std::vector<peca_t> PECAS;
peca_t *PECAS;
//std::vector<peca_t> *FITA;
peca_t *FITA;
std::vector<std::vector<peca_t> > RESULTADOS;

void print_pecas() {
    fprintf(stderr, "\nPrint Pecas:\n" );
    for ( int i = 0; i < N; ++i ) {
        peca_t p = PECAS[ i ];
        fprintf(stderr, "  %d - %d\n", p.a, p.b );
    }
}

void backtrack( int tamanho, int last_peca ) {
    // fprintf(stderr, "  backtrack( %d,%d )\n", tamanho, last_peca );
    if ( tamanho ) {
        for ( int pos = 0; pos < N; ++pos ) { // pos in 0..N
            peca_t peca = PECAS[ pos ];
            int peca_a = peca.a;
            int peca_b = peca.b;
            int p = peca.used;
            for ( int lado = 0; lado < 2; ++lado ) {
                if (( peca.used == PECA_NAO_USADA ) &&
                    ( peca_a == last_peca || tamanho == K )) {
                    FITA[ ( tamanho - 1 ) ] = { peca_a, peca_b, -1 };
                    PECAS[ pos ].used = PECA_USADA;
                    backtrack( tamanho - 1, peca_b );
                    PECAS[ pos ].used = PECA_NAO_USADA;
                }
                std::swap( peca_a, peca_b );
            }
        }
    } else {
        std::vector<peca_t> resp;
        for ( int i = 0; i < K; i++ )
            resp.push_back(( peca_t ) { FITA[ i ].b, FITA[ i ].a, 0 } );
        RESULTADOS.push_back( resp );
    }
}

void print_resultado() {
    // fprintf(stderr, "|RESULTADOS|: %d\n", RESULTADOS.size() );
    for ( int resp = 0; resp < RESULTADOS.size(); ++resp ) {
        // fprintf(stderr, "  %d: ", resp );
        for ( int k = 0; k < K; ++k ) {
            // fprintf(stderr, "%d %d ", RESULTADOS[ resp ][ k ].a, RESULTADOS[ resp ][ k ].b );
            fprintf(stdout, "%d %d ", RESULTADOS[ resp ][ k ].a, RESULTADOS[ resp ][ k ].b );
        }
        // fprintf(stderr, "\n" );
        fprintf(stdout, "\n" );
    }
}

int main() {
    // fprintf(stderr, "Rafael Cardoso da Silva 21048012\n" );

    // Ler a quantidade de Pecas e de slots da Fita
    fscanf(stdin, "%d %d", &N, &K );
    // fprintf(stderr, "N: %d  K: %d\n", N, K );

    peca_t fita[K];
    FITA = fita;
    peca_t pecas[K];
    PECAS = pecas;

    // Ler todas as PECAS de Domino
    for ( int i = 0; i < N; ++i ) {
        int a, b;
        fscanf(stdin, "%d %d", &a, &b );
        PECAS[ i ] = { a, b, PECA_NAO_USADA };
    }

    // print_pecas();
    backtrack( K, 0 );
    print_resultado();
}

/*
 4 3
 1 4
 2 3
 2 1
 5 1

 (a)
 5 1 1 2 2 3

 (c)
 4 1 1 2 2 3 -ok
 3 2 2 1 1 4 -ok
 3 2 2 1 1 5 -ok
 5 1 1 2 2 3 -ok

 */


