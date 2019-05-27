def prt():
    print "\x1b[0;33m"
    for i, it in enumerate(N):
        print i%10,
    print 
    for i, it in enumerate(N):
        for j, jt in enumerate(N):
            if i <= j:
                if N[j][1] == i:
                    #if N[j][2]:
                    if d[j]:
                        print '\x1b[0;31m#',
                    else:
                        print '\x1b[0;33m#',
                else:
                    print '\x1b[0;35m.',
            else:
                print " ",
        print "\x1b[0;33m", i 
    print 




def Pai(c):
    N[c][2] = 1-N[c][2]
    if N[c][1] != c:
        Pai(N[c][1])


a = input()
b = [int(i) for i in raw_input().split()]
c = [1 if int(i) > 0 else 0 for i in raw_input().split()]
d = [1]*int(a)

N = [(1,1,1,1)]*len(b)
for i, it in enumerate(b):
    N[i] = (i, b[i], c[i])
    d[it] = 0
    


print N



prt()










