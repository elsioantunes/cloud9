def table():
    for j in range(h):
        for i in range(w):
            print (buf[w*j+i], end='\t')
        print('\n')
