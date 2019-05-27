def anag(n):
    if n:
        for i in "elsi":
            if ocr[i]:
                S[n-1] = i
                ocr[i] -= 1
                anag(n-1)
                ocr[i] += 1
    else:
        print S

S = [0]*4


palavra = "elsii"

ocr = {}
for i in palavra:
    ocr[i] = 0 

for i in palavra:
    ocr[i] += 1 

for i in ocr:
    print i,
print

for i in ocr:
    print ocr[i],
print

anag(4)




