#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h> // Usar o bool padrão

// =====================
// Definições do Grafo e Lista de Adjacência
// =====================
typedef int TIPOPESO;

typedef struct adjacencia {
    int vertice;
    TIPOPESO peso;
    struct adjacencia *prox;
} ADJACENCIA;

typedef struct vertice {
    /* outros dados aqui*/
    ADJACENCIA *cab;
} VERTICE;

typedef struct grafo {
    int vertices;
    int arestas;
    VERTICE *adj;
} GRAFO;

// =====================
// Código super longo pra fila
// =====================
typedef int TIPOCHAVE;
typedef struct {
    TIPOCHAVE chave;
} REGISTRO;

typedef struct aux {
    REGISTRO reg;
    struct aux* prox;
} ELEMENTO, *PONT;

typedef struct fila {
    PONT inicio;
    PONT fim;
} FILA;
typedef struct noArvore{
    int chave;
    struct noArvore *esquerda; //Filho na esquerda
    struct noArvore *direita; //Irmãos na direita
} NOARVORE;
// =====================
// Prototipação das Funções
// =====================
NOARVORE* largura(GRAFO *g);
NOARVORE* visitaL(GRAFO *g, int s, bool expl[]);
void inicializarFila(FILA *f);
void inserirNaFila(FILA *f, REGISTRO *r);
void excluirDaFila(FILA *f, REGISTRO **r);

// =====================
// Inicializa a fila
// =====================
void inicializarFila(FILA *f) {
    f->inicio = NULL;
    f->fim = NULL;
}

// =====================
// Insere elemento na fila
// =====================
void inserirNaFila(FILA *f, REGISTRO *r) {
    PONT novo = (PONT) malloc(sizeof(ELEMENTO));
    if (!novo) return;
    novo->reg = *r;
    novo->prox = NULL;
    if (f->fim)
        f->fim->prox = novo;
    else
        f->inicio = novo;
    f->fim = novo;
}

// =====================
// Exclui elemento da fila
// =====================
void excluirDaFila(FILA *f, REGISTRO **r) {
    if (!f->inicio) return;
    PONT temp = f->inicio;
    *r = (REGISTRO *) malloc(sizeof(REGISTRO));
    **r = temp->reg;
    f->inicio = f->inicio->prox;
    if (!f->inicio) f->fim = NULL;
    free(temp);
}

// =====================
// Cria o Arranjo pra dizer se ele foi visitado ou nao
// =====================
NOARVORE* largura(GRAFO *g) {
    bool expl[g->vertices];
    for (int u = 0; u < g->vertices; u++)
        expl[u] = false;

    // Aqui, só fazemos uma árvore a partir do primeiro componente conectado
    for (int u = 0; u < g->vertices; u++)
        if (!expl[u])
            return visitaL(g, u, expl);

    return NULL;
}

// criar arvore antes do visital
NOARVORE* criaNaArvore(int chave) {
    NOARVORE* novo = (NOARVORE*) malloc(sizeof(NOARVORE));
    novo->chave = chave;
    novo->esquerda = NULL;
    novo->direita = NULL;
    return novo;
}

// =====================
// O visitaL, basicamente a busca com as regras para o DFS
// =====================
NOARVORE* visitaL(GRAFO *g, int s, bool expl[]) {
    FILA f;
    inicializarFila(&f);
    expl[s] = true;

    NOARVORE* raiz = criaNaArvore(s);
    NOARVORE* posicoes[g->vertices];
    for (int i = 0; i < g->vertices; i++) {
        posicoes[i] = NULL;
        posicoes[s] = raiz;
    }

    REGISTRO *inicio = (REGISTRO *) malloc(sizeof(REGISTRO));
    inicio->chave = s;
    inserirNaFila(&f, inicio);
    free(inicio);

    REGISTRO *u;
    while (f.inicio) {
        excluirDaFila(&f, &u);
        ADJACENCIA *v = g->adj[u->chave].cab;

        NOARVORE* pai = posicoes[u->chave];
        NOARVORE* ultimoFilho = NULL;

        while (v) {
            if (!expl[v->vertice]) {
                expl[v->vertice] = true;
                REGISTRO *novo = (REGISTRO *) malloc(sizeof(REGISTRO));
                novo->chave = v->vertice;
                inserirNaFila(&f, novo);
                free(novo);

                NOARVORE* filho = criaNaArvore(v->vertice);
                posicoes[v->vertice] = filho;

                if (!pai->esquerda) {
                    pai->esquerda = filho;
                } else {
                    ultimoFilho->direita = filho;
                }
                ultimoFilho = filho;
            }
            v = v->prox;
        }
        free(u);
    }

    return raiz;
}
void imprimirArvore(NOARVORE *raiz, int nivel) {
    if (raiz == NULL) return;
    for (int i = 0; i < nivel; i++) printf("  ");
    printf("%d\n", raiz->chave);
    imprimirArvore(raiz->esquerda, nivel + 1); // filho
    imprimirArvore(raiz->direita, nivel);      // irmão
}


// A PARTIR DAQUI É TESTE
// Função para criar um grafo com N vértices
GRAFO *criarGrafo(int vertices) {
    GRAFO *g = (GRAFO *) malloc(sizeof(GRAFO));
    g->vertices = vertices;
    g->arestas = 0;
    g->adj = (VERTICE *) malloc(vertices * sizeof(VERTICE));
    for (int i = 0; i < vertices; i++)
        g->adj[i].cab = NULL;
    return g;
}

// Função para inserir aresta no grafo (não direcionado)
bool inserirAresta(GRAFO *g, int origem, int destino, TIPOPESO peso) {
    if (!g || origem < 0 || destino < 0 || origem >= g->vertices || destino >= g->vertices)
        return false;
    ADJACENCIA *novo = (ADJACENCIA *) malloc(sizeof(ADJACENCIA));
    novo->vertice = destino;
    novo->peso = peso;
    novo->prox = g->adj[origem].cab;
    g->adj[origem].cab = novo;

    // Como o grafo é não-direcionado, adiciona a volta também
    ADJACENCIA *volta = (ADJACENCIA *) malloc(sizeof(ADJACENCIA));
    volta->vertice = origem;
    volta->peso = peso;
    volta->prox = g->adj[destino].cab;
    g->adj[destino].cab = volta;

    g->arestas++;
    return true;
}

// Função main para testar
int main() {
    GRAFO *g = criarGrafo(6); // 6 vértices: 0 a 5

    inserirAresta(g, 0, 1, 1);
    inserirAresta(g, 0, 2, 1);
    inserirAresta(g, 1, 3, 1);
    inserirAresta(g, 1, 4, 1);
    inserirAresta(g, 2, 5, 1);

    NOARVORE *arvore = largura(g);

    printf("Árvore gerada pela BFS:\n");
    imprimirArvore(arvore, 0);

    return 0;
}

