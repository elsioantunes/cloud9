def C(n, k):
	if k > n: return  0
	if k > n / 2: k = n - k
	res = 1
	for i in range(k):
		res *= n - i 
		res /= i + 1 
	return res

def id2seq(id, m, n):
    L = []
    M = C(n,2)*2
    for i in range(m):
        s = id % M
        id = (id - s)/M
        L += [s]
    return L

def seq2id(L, m, n):
    comb = C(n,2)*2
    s = 0
    for i, it in enumerate(L):
        s += it*comb**i
    return s

def conta(m, n):
    S = 0
    comb = C(n,2)*2
    for i in range(m):
        S += C(comb, i+1)*C(m-1,i)
    return S
