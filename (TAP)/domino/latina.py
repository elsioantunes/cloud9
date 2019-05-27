A = [
    [0, 1, 0, 0, 0],
    [0, 0, 1, 1, 0],
    [1, 0, 0, 0, 1],
    [0, 0, 1, 0, 1],
    [1, 0, 0, 0, 0]
]

B = [
    [0, 0, 0, 0, 0],
    [0, 0, 0, 0, 0],
    [0, 0, 0, 0, 0],
    [0, 0, 0, 0, 0],
    [0, 0, 0, 0, 0]
]

C = [
    [0, 0, 0, 0, 0],
    [0, 0, 0, 0, 0],
    [0, 0, 0, 0, 0],
    [0, 0, 0, 0, 0],
    [0, 0, 0, 0, 0]
]




def opera(A, B):
    n = len(A)
    for k in range(n):
        for i in range(n):
            for j in range(n):
                A[i][j] = max(A[i][k], A[i][k] * A[k][j])
                

opera(A, B)
opera(A, B)



'''
n = len(A)            
for k in range(n):
    for i in range(n):
        for j in range(n):
            C[i][j] += B[i][k] * A[k][j]
'''            

n = len(A)            
for i in range(n):
    for j in range(n):
        print A[i][j], '\t',
    print






'''

for i in A:
    for j in i:
        print j, '\t',
    print



str = ["A","B","C","D","E"]
for i, it in enumerate(A):
    for j, jt in enumerate(it):
        if jt:
            print str[i],str[j],"\t",
        else: 
            print ".","\t ",
    print
'''