class fila():
    def __init__(self):
        self.list = []
    
    def __getitem__(self,i):
        return self.list[i]
    
    def push(self, item):
        self.list.append(item)
    
    def insert(self, item):
        self.list.insert(0,item)
    
    def pop(self):
        return self.list.pop()
    
    def isEmpty(self):
        return len(self.list) == 0
    
    def sort(self):
        return self.list.sort()
        
        
    

f = fila()

f.push(1)
f.push(2)
f.push(3)
f.push(4)
f.insert(5)

print f[0]



