from combinations import C, id2seq, conta, seq2id
import random
print random.random()
print

#print conta(PEOES, CASAS)
#print id2seq(540897279, PEOES, CASAS)
#print seq2id([24, 24, 24, 24, 52], PEOES, CASAS)

'''
primeiro resultado do tab5x8 vem para a = 9834496
comb total 550731776 100000110100111000000000000000
comb unic    5461512

 550731775 = [55, 55, 55, 55, 55]
 515685208 = [24, 24, 24, 24, 52]
 
 C(20, 1) * C(2, 0) = 20      * 1   = 20     (a, a, a)  
 C(20, 2) * C(2, 1) = 190     * 2   = 390    (a, a, b) (a, b, b)  
 C(20, 3) * C(2, 2) = 1140    * 1   = 1140   (a, b, c)

 C(56, 1) * C(4, 0) = 56      * 1  = 56        (a, a, a, a, a)   
 C(56, 2) * C(4, 1) = 1540    * 4  = 6160      (a, b, b, b, b) (a, a, b, b, b) (a, a, a, b, b) (a, a, a, a, b)
 C(56, 3) * C(4, 2) = 27720   * 6  = 166320    (a, a, a, b, c) (a, b, b, b, c) (a, b, c, c, c) (a, a, b, b, c) (a, a, b, c, c) (a, b, b, c, c) 
 C(56, 4) * C(4, 3) = 367290  * 4  = 1469160   (a, a, b, c, d) (a, b, b, c, d) (a, b, c, c, d) (a, b, c, d, d) 
 C(56, 5) * C(4, 4) = 3819816 * 1  = 3819816   (a, b, c, d, e)

'''
W = 3872894697
W = 5461512
PEOES = 3
CASAS = 5
comb = C(CASAS,2)*2


def printk(n):
    L = []
    for i in range(comb):
        s = n % 2
        if s: L += [i]
        n = (n-s)/2
    return L

s = 0
for i in range(PEOES):
    n = C(PEOES-1, i) * C(comb, i+1)
    
    print "----------------------------------"
    #print i, n
    
    for j in range(C(PEOES-1, i)): 
        # Gosper’s hack, uh!!
        a = (1 << (i+1)) - 1
        for k in range(C(comb, i+1)):
            print printk(a),
            c = (a & -a)
            r = a + c
            a = (((r ^ a) >> 2) / c) | r
        print
    print

    s += n
print 














'''
k = 0;
for i in range(20*20):
    n = i
    ok = 1
    r = -1
    L = []
    for j in range(2):
        s = n % 20
        if s <= r:
            ok = 0
            break
        n = (n - s)/20
        L = [s] + L
        r = s
    
    if ok:
        #print k, ":", i, "\t", 
        #for j in L:
        #    print j, " ",
        print L[1], " ",
        #print
        k += 1



'''
