#!/usr/bin/python
import sys

#########################################################

def getchar():
    global c
    c = sys.stdin.read(1)

def matchar(cod):
    global code
    code = cod
    getchar()

def gettoken():
    while c in [' ', '\t']: getchar()
    if c.isupper(): matchar("LETRAMAIUSCULA")
    elif c == "": matchar("EOF")
    elif c == "\n": matchar("EOL")
    elif c == "<": matchar("SINALMENOR")
    elif c == ">": matchar("SINALMAIOR")
    elif c == "-":
        matchar("TERMINAL")
        if c == "-":
            matchar("TERMINAL")
            if c == ">":
                matchar("FLECHA")
    else:
        matchar("TERMINAL")

#########################################################

def match(cod):
    if code == cod:
        gettoken()
        return 1
    return 0

def ID():
    if match("TERMINAL"):
        ID()
        return 1
    return 0

def variavel():
    if match("LETRAMAIUSCULA"): return 1
    return match("SINALMENOR") and ID() and match("SINALMAIOR")

def elemento():
    if match("TERMINAL"): return 2
    return variavel()

def sentenca1(): 
    while elemento(): 
        classe[2] = 0
        classe[3] = 0
    return 1

def sentenca2(): 
    a = elemento()
    b = elemento()
    while elemento(): classe[3] = 0
    if a < b and a > 0: classe[4] = -1
    if a > b and b > 0: classe[5] = -1
    if classe[4] and classe[5]: classe[3] = 0
    if a and not b: classe[3] = 0
    if a == 0: classe[1] = 0
    return 1

def regra():
    a = elemento()
    if a == 2:
        classe[3] = 0
        classe[2] = 0
    return a and sentenca1() and match("FLECHA") and sentenca2() and match("EOL")

def gramatica():
    if regra(): return gramatica()
    elif match("EOF"): return 1
    return 0
        
#########################################################

c = ""
code = ""
classe = [0,1,2,3,0,0]
getchar()
gettoken()

if gramatica(): print "CORRETO", max(classe)
else: print "ERRO"

#########################################################
'''
<gramatica>  -->  <regra>  (<gramatica> |   EOF)
<regra>      -->  <sentenca1>  FLECHA  <sentenca2>  EOL
<sentenca1>  -->  <elemento>  <sentenca2>
<sentenca2>  -->  <elemento>  <sentenca2> | &
<elemento>   -->  <variavel> | TERMINAL
<variavel>   -->  LETRAMAIUSCULA | SINALMENOR  <id>  SINALMAIOR
<id>         -->  TERMINAL  (<id> | &)
'''
