def backtrack(n, c):
    if n:
        for f, it in enumerate(M):
            i, j, k = it
            if (i == c or n == k) and k:
                S[n-1] = (i, j)
                M[f][2] = 0
                backtrack(n-1, j)
                M[f][2] = 1

            j, i, k = it
            if (i == c or n == k) and k:
                S[n-1] = (i, j)
                M[f][2] = 0
                backtrack(n-1, j)
                M[f][2] = 1

    else:
        print S
        

k = 8

S = [0]*k
#M = [(9, 8),(7, 6),(5, 4),(3, 2)]

ret = [(3, 3),(5, 6),(7, 5),(5, 5),(9, 3),(0, 1),(2, 3),(4, 0),(4, 2),(2, 0),(4, 3),(9, 0),(5, 1),(9, 7),(3, 2),(5, 0),(8, 9),(4, 0)]

print ret

M = [[a,b,1] for a,b in ret]
    

backtrack(k, 0)