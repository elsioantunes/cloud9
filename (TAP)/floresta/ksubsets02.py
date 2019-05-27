def generate_k_subsets(n,k):
    """
    Generate all k-subsets of an n-set sequentially.
    Reference:
        http://www.math.upenn.edu/~wilf/website/CombinatorialAlgorithms.pdf
        Chapter 3
    """
    m, h  = 0, k
    a = range(k)
    print a
    yield a
    while True:
        if m < n-h: h = 1
        else: h += 1
        m = a[k-h] + 1
        for j in range(h): a[k+j-h] = m + j
        yield a
        if a[0] == n - k:  break




print generate_k_subsets(4,2)
