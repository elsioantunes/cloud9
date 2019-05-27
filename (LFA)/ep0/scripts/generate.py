#!/usr/bin/python3
# -*- encoding: utf-8 -*-


from random import *
import sys

seed()


def print_help():
    print("Modo de usar:")
    print("============:\n")
    print("prompt> generate.py [num. estados] [num. símbolos] [num. palavras] [compr. max]\n")
    print("""
todos os argumentos são opcionais, 
mas se um argumento não está presente, 
os que seguem, na ordem, também 
devem ser omitidos.""")



if len(sys.argv) > 1:
    if "".join(sys.argv).lower().find("help") >= 0:
        print_help()
        sys.exit(0)
    n = int(sys.argv[1])
else:
    n = randint(1, 100000)

if len(sys.argv) > 2:
    k = int(sys.argv[2])
else:
    k = randint(1, randint(1, 26))

accepting = []

print(n, k)
for i in range(n):
    for j in range(k):
        print(randint(0, n - 1), end=" ")
    print()
    if randint(0, 2) == 1:
        accepting.append(i)

print(len(accepting))
for i in accepting:
    print(i, end=" ")
print()

t = randint(1000, 100000)

if len(sys.argv) > 3:
    m = int(sys.argv[3])
else:
    m = 5 + randint(1, 995)

print(m)

if len(sys.argv) > 4:
    maxl = int(sys.argv[4])
else:
    maxl = t // m

for i in range(m):
    l = randint(0, maxl)
    for j in range(l):
        print(chr(ord('a') + randint(0, k - 1)), end="")
    print()
