class Node(object):
    def __init__(self):
        self.no = [0]*50
        self.fim = 0
        self.n = 0

class Trie(object):
    def __init__(self):
        self.root = Node()
        self.out = []
        self.compare = ""
    
    def inserir(self, arr):
        atual = self.root
        for i in arr:
            if not atual.no[i]:
                atual.no[i] = Node() 
            atual = atual.no[i]
        atual.fim = 1

    
    def listar(self):
        self.listarRec(self.root, [])

    def listarRec(self, node, arr):
        if node.fim:
            print arr
        
        for i in range(50):
            if node.no[i]:
                self.listarRec(node.no[i], arr + [i])
                


    
t = Trie()
t.inserir([5,3,2,1])
t.inserir([5,4,1,2])
t.inserir([3, 5,14,1,2])
t.inserir([7,3,5,3])
t.listar()
t.listar()



            


