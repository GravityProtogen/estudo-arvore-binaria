# -----------------------#
# Implementação de uma árvore binária
# Cria uma arvore com quatro nós=
# Contémos os seguintes métodos:
# - DFS em ordem
# - DFS pré ordem
# - DFS pós ordem
# - BFS
# -----------------------#




#Criando uma arvore
#            2
#          /   \
#         3     4
#        /
#       5
# Declaração os nós
class No:
    def __init__(self, valor):
        self.left=None
        self.right=None
        self.val=valor

# DFS EM ORDEM
# Resultado: 5 3 2 4
def dfs_em_ordem(no):
    if no is None:
        return
    dfs_em_ordem(no.left)
    print(no.val, end=' ')
    dfs_em_ordem(no.right)
# DFS PRE ORDEM
# Resultado: 2 3 5 4
def dfs_pre_ordem(no):
    if no is None:
        return
    print(no.val, end=' ')
    dfs_pre_ordem(no.left)
    dfs_pre_ordem(no.right)

# DFS POS ORDEM
# Resultado: 5 4 3 2
def dfs_pos_ordem(no):
    if no is None:
        return
    dfs_pos_ordem(no.left)
    dfs_pos_ordem(no.right)
    print(no.val, end=' ')

# BFS
# Resultado: 2 3 4 5
def bfs(root):
    if root is None:
        return
    queue = [root]
    while queue:
        no = queue.pop(0)
        print(no.val, end=' ')
        if no.left:
            queue.append(no.left)
        if no.right:
            queue.append(no.right)

#Declarando valor dos nós
primeiroNo=No(2)
segundoNo=No(3)
terceiroNo=No(4)
quartoNo=No(5)

#Ligando os nós
primeiroNo.left=segundoNo
primeiroNo.right=terceiroNo
segundoNo.left=quartoNo

print("In-order DFS: ", end='')
dfs_em_ordem(primeiroNo)
print("\nPre-order DFS: ", end='')
dfs_pre_ordem(primeiroNo)
print("\nPost-order DFS: ", end='')
dfs_pos_ordem(primeiroNo)
print("\nLevel order: ", end='')
bfs(primeiroNo)
