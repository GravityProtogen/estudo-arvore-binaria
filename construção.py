# Construindo uma arvore binária a partir de um vetor
class No:
    def __init__(self, valor):
        self.left=None
        self.right=None
        self.val=valor

def inserirEmOrdem(arr,i,n):
    root = None
    if i < n:
        root = No(arr[i])
        root.left = inserirEmOrdem(arr,2*i+1,n)
        root.right = inserirEmOrdem(arr,2*i+2,n)
    return root

def dfs_em_ordem(no):
    if no is None:
        return
    dfs_em_ordem(no.left)
    print(no.val, end=' ')
    dfs_em_ordem(no.right)
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

if __name__ == '__main__':
    arr = [1,2,3,4,5,6,6,6,6]
    n = len(arr)
    root = None
    root = inserirEmOrdem(arr,0,n)
    dfs_em_ordem(root)
    print()
    bfs(root)