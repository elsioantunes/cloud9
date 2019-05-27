#!/usr/bin/python
import sys
c = ""
code = ""

#########################################################

def getchar():
    global c
    c = sys.stdin.read(1)

def matchar(cod):
    global c, code
    code = cod
    getchar()

def check(cod):
    global code
    return code == cod

def match(cod):
    global code
    if code == cod:
        gettoken()
        return 1
    return 0

def match2(code1, code2):
    if check(code1) or check(code2):
        gettoken()
        return 1
    return 0

#########################################################

def gettoken():
    if c.isupper(): matchar("LETRAMAIUSCULA")
    elif c == "": matchar("EOF")
    elif c == "\n": matchar("EOL")
    elif c == "<": matchar("SINALMENOR")
    elif c == ">": matchar("SINALMAIOR")
    elif c in [' ', '\t']:
        getchar()
        gettoken()
    elif c == "-":
        matchar("TERMINAL")
        if c == "-":
            matchar("TERMINAL")
            if c == ">":
                matchar("FLECHA")
    else:
        matchar("TERMINAL")

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
#########################################################

def ID():
    if match("TERMINAL"):
        ID()
        return 1
    return 0

def variavel():
    if match("LETRAMAIUSCULA"): return 1
    return match("SINALMENOR") and ID() and match("SINALMAIOR")

def elemento():
    if match("TERMINAL"): return 1
    return variavel()

def sentenca(): 
    while elemento(): pass
    return 1

def regra():
    return elemento() and sentenca() and match("FLECHA") and sentenca() and match2("EOL", "EOF")

def gramatica():
    if regra(): 
        return gramatica()
    elif match("EOF"):
        return 1
    return 0
        
#########################################################

getchar()
gettoken()




#print regra()
#print regra()
#print elemento()
#print sentenca()


#'''
if gramatica(): print "CORRETO 3"
else: print "ERRO"
#'''


