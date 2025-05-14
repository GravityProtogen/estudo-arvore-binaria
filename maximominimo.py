# Achar o Máximo e o Minimo de uma arvore binária
from collections import deque

class No:
    def __init__(self, valor):
        self.left=None
        self.right=None
        self.val=valor

def acharMaximo(root):
    if (root == None):
        return float('-inf')
    
    res = root.val
    lres = acharMaximo(root.left)
    rres = acharMaximo(root.right)


    # 3 Valores em seguida
    # 1 - Valor da raiz
    # 2 - Maximo da esquerda
    # 3 - Maximo da direita
    if (lres > res):
        res = lres
    if (rres > res):
        res = rres
    return res

if __name__ == '__main__':
    root = No(2)
    root.left = No(7)
    root.right = No(5)
    root.left.right = No(6)
    root.left.right.left = No(1)
    root.left.right.right = No(11)
    root.right.right = No(9)
    root.right.right.left = No(4)
 
    # Function call
    print("Maximum element is",
          acharMaximo(root))