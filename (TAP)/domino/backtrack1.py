def backtrack(n, k, S, s):
    if n:
        if n-k:
            S[n-1] = 0
            backtrack(n-1, k, S, s)
        if k:
            #for i in range(3):
            S[n-1] = n
            backtrack(n-1, k-1, S, s)
    else:
        print S, sum(S)


s = [9,8,7,6,5,4,3,2,1]




n = 5
k = 3
backtrack(n, k, [0]*n, s)

print

n = 5
k = 2
backtrack(n, k, [0]*n, s)