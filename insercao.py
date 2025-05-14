#Inserção utiliza do mesmo codigo de BFS, porém adiciona:
#- Se o filho esquerdo for None, insere o novo no left
#- Se o filho direito for None, insere o novo no right

from collections import deque
class No:
    def __init__(self, valor):
        self.left=None
        self.right=None
        self.val=valor

def inserir(root,chave):
    if root is None:
        return No(chave)
    
    queue = deque([root])
    
    while queue:
        temp = queue.popleft()
        
        if temp.left is None:
            temp.left = No(chave)
            break
        else:
            queue.append(temp.left)
        
        if temp.right is None:
            temp.right = No(chave)
            break
        else:
            queue.append(temp.right)
                    
    return root

#DFS EM ORDEM
def dfs_em_ordem(no):
    if no is None:
        return
    dfs_em_ordem(no.left)
    print(no.val, end=' ')
    dfs_em_ordem(no.right)
    
if __name__ == "__main__":
    raiz = No(2)
    raiz.left = No(3)
    raiz.right = No(4)
    raiz.left.left = No(5)
    
    print("Em Ordem antes de inserir ", end="")
    dfs_em_ordem(raiz)
    print()
    
    chave = 6
    raiz = inserir(raiz, chave)
    
    print("Em Ordem depois de inserir ", end="")
    dfs_em_ordem(raiz)
    print()