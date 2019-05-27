#!/usr/bin/python
'''
    sudo apt-get update
    sudo apt-get install python-sklearn
    #pip install -U scikit-learn

'''
#import pandas as pd
import numpy as np
from sklearn.neighbors import KNeighborsClassifier 
from sklearn.metrics import accuracy_score
from sklearn.metrics import confusion_matrix
from sklearn.neighbors import KNeighborsClassifier 
#from sklearn.model_selection import train_test_split as tts
from sklearn.cross_validation import train_test_split as tts

lines = [line.strip() for line in open('krk_database.txt')]
data = [i.split(',') for _, i in zip(range(10), lines)]

for i in data:
    print i
    


print np.array([1,2,3,4,67,90,21])