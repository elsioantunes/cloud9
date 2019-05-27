#!/usr/bin/python 
import sys
''' 
    BLOCOS
    Problema 1331 do URI
    https://www.urionlinejudge.com.br/judge/pt/problems/view/1331
    licenca: kkk
'''
def input(t):
    a = sys.stdin.readline()
    if t: return [i for i in a.split()]
    return int(a)

def entrada():
    ''' 
        Compacta entrada!
        Funcionou sem isso. Ate passou no uri
        To fazendo pra melhorar o tempo.
    '''
    _ = input(0)
    B = input(1) + ['Elsio']
    b = []
    blocks = []
    for i in range(len(B)-1):
        b += [B[i]]
        if B[i] != B[i+1] : 
            blocks += [(len(b), b[0])]
            b = []
    return blocks + ['Antunes']

def solve(l, r, k):
    # programacao dinamica
    if (l, r, k) in buf: return buf[(l, r, k)]

    # condicoes de parada
    if l > r: return 0
    
    # caso 1: intervalo nada a ver com o resto
    m = blocks[l][0] + k
    M = m*m + solve(l+1, r, 0)
    
    # caso 2: intervalo coincide com algo la dentro
    for i in range(l+1, r+1):
        if blocks[i][1] == blocks[l][1]:
            M = max(M, solve(l+1, i-1, 0) + solve(i, r, blocks[l][0]+k)) 
    
    # M contem a resposta
    buf[(l, r, k)] = M
    return M

case = 0
cases = input(0)
while case < cases:
    case += 1
    blocks = entrada()
    buf = {}
    print "Case {0}: {1}".format(case, solve(0, len(blocks)-2, 0))


    
#################################################################
# ..e foi assim que ficou, depois de retirados todos os andaimes. 
'''
#####################################################
### Resumo sem redondilhas, pra entender o codigo ###
#####################################################

def solve(l, r, n):
    if l > r: return 0
    M = n*n + solve(l+1, r, 1)
    for i in range(l+1, r+1):
        if blocks[i] == blocks[l]:
            a = solve(l+1, i-1, 1)
            b = solve(i, r, n+1)
            M = max(M, a + b) 
    return M

blocks = [1,2,2,2,2,3,3,3,1]
print blocks, solve(0, len(blocks)-1, 1)

####################################################

    * O codigo acima resolve instancias pequenas *

    Ou seja: 
    funcao recursiva que conta os pontos quadrados 
    de cada instancia quebrando em problemas menores 
    maximizando pontos.

    caracteristica do problema: 
    problema recursivo que faz calculos repetidos.

    * Proximos passos *

    - Um dict buf na func rec solve para guardar 
    a saida M nos parametros de entrada (l, r, c)
    
    - Uma forma de comprimir a entrada sem comprometer a saida:
    trocar [1,1,2,2,2,3,3,3] por [(1,1),(3,2),(3,3)] acelera
    o processo em troca de um pouco de complicacao no codigo
    
    
    
    

####################################################

'''


    
