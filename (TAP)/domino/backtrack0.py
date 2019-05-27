def backtrack(n, k):
    if n:
        if k:
            S[n-1] = 1
            backtrack(n-1, k-1)
            S[n-1] = 2
            backtrack(n-1, k-1)
        if n-k:
            S[n-1] = 0
            backtrack(n-1, k)
    else:
        print S, ":",
        for pos, flip in enumerate(S):
            if flip: print pos, flip, " ",
        print
            
            
S = [0]*4
backtrack(4,3)