def permuta(i, n, S):
    if i < n:
        for j in range(n):
            S[i], S[j] = S[j], S[i]
            permuta(i+1, n, S)
            S[i], S[j] = S[j], S[i]
    else:
        print S

permuta(0, 3, [1,2,3])