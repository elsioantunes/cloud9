#!/usr/bin/python
#https://docs.python.org/2.7/reference/ 

def qsort(list):
    if list == []:
        return []
    p = list[0]
    l = qsort([x for x in list if x < p])
    u = qsort([x for x in list[1:] if x >= p])
    return l + [p] + u


print qsort([9,8,7,6,5,4,3,2,1,2,3,4,5,

6,7,8,9])

