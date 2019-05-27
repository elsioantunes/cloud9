import numpy as np
#import pandas as pd
from sklearn.neighbors import KNeighborsClassifier 
from sklearn.metrics import accuracy_score
from sklearn.metrics import confusion_matrix
from sklearn.neighbors import KNeighborsClassifier 
from sklearn.cross_validation import train_test_split as tts

def chebyshev(x1, y1, x2, y2):
  return max(abs((int)(x1-x2)),abs((int)(y1-y2)))

def anticheb(x1, y1, x2, y2):
  return min(abs((int)(x1-x2)),abs((int)(y1-y2)))

def descricao_de_empate(xWK, yWK, xWR, yWR, xBK, yBK):
  ataque = chebyshev(xBK, yBK, xWR, yWR) == 1
  naodefesa = chebyshev(xWK, yWK, xWR, yWR) > 1
  nocanto = xBK == 0 and yBK == 0
  afogamento = nocanto and yWR == 1 and ((xWK == 2 and yWK == 0) or xWR == 1)
  return naodefesa and ataque or afogamento



lines = [line.strip() for line in open('krk_database.txt')]
#data = [i.split(',') for i in lines]
#data = [i.split(',') for _, i in zip(range(10), lines)]
data = [[int(j) for j in i.split(',')] for i in lines]




X = []
y = []
for xWK, yWK, xWR, yWR, xBK, yBK, Classe in data:
    X.append([xWK, yWK, xWR, yWR, xBK, yBK])
    y.append(Classe)

x_train, x_test, y_train, y_test = tts(X, y, test_size=.25, random_state=888)
alg = KNeighborsClassifier(7, weights='distance')
#alg.fit(x_train, y_train)
alg.fit(X,y)
print alg.score(x_test, y_test);



