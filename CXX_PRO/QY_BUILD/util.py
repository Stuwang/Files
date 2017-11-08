# some useful data struct

class Stack(object):

    def __init__(self):
        self.stack=[]

    def empty(self):
        return len(self.stack) == 0;

    def push(self,item):
        self.stack.append(item);

    def pop(self):
        if self.empty():
            raise IndexError('pop from empty stack')
        return self.stack.pop()

    def top(self):
        return self.stack[-1]

    def size(self):
        return len(self.stack)