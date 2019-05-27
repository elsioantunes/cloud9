class Node:
    def __init__(self, data):
        self.data = data
        self.prox = None

class LinkedList:
    def __init__(self):
        self.head = None

    def sortedInsert(self, new_data):
        new_node = Node(new_data)

        if self.head is None:
            new_node.prox = self.head
            self.head = new_node

        elif self.head.data <= new_node.data:
            new_node.prox = self.head
            self.head = new_node

        else :
            current = self.head
            while(current.prox is not None and
                 current.prox.data > new_node.data):
                current = current.prox

            new_node.prox = current.prox
            current.prox = new_node

    def pop(self):
        val = self.head.data
        self.head = self.head.prox
        return val

    def printList(self):
        temp = self.head
        while(temp):
            print(temp.data),
            temp = temp.prox







llist = LinkedList()

llist.sortedInsert(5)
llist.sortedInsert(1)
llist.sortedInsert(7)
llist.sortedInsert(3)
llist.sortedInsert(10)
llist.sortedInsert(9)

print("Create Linked List")
llist.printList()


b = 1.0/2
c = 1.0/2

print 
print b, c
print b > c