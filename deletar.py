from collections import deque
class No:
    def __init__(self, valor):
        self.left=None
        self.right=None
        self.val=valor
#Declarando valor dos nós
primeiroNo=No(2)
segundoNo=No(3)
terceiroNo=No(4)
quartoNo=No(5)

#Ligando os nós
primeiroNo.left=segundoNo
primeiroNo.right=terceiroNo
segundoNo.left=quartoNo

# Deletar o nó que o usuario deu pela chave
def delete(self, key):
    if key < self.val:
        if self.left:
            self.left = self.left.delete(key)
    elif key > self.val:
        if self.right:
            self.right = self.right.delete(key)
    else:
        # Nó somente com um filho ou sem filhos
        if self.left is None:
            return self.right
        elif self.right is None:
            return self.left
        # Nó com dois filhos
        temp = self.right
        while temp.left:
            temp = temp.left
        self.val = temp.val
        self.right = self.right.delete(temp.val)
    return self
delete(primeiroNo, 5)
print(primeiroNo)
print(segundoNo)
print(terceiroNo)
print(quartoNo)