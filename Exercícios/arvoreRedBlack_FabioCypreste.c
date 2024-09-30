#include <stdio.h>
#include <stdlib.h>

// Definição dos possíveis valores de cor
#define VERMELHO 0
#define PRETO 1

// Definição da estrutura de um nó da árvore Red-Black
struct No
{
    int valor;
    int cor;
    struct No *esquerda, *direita, *pai;
};

typedef struct No No;

// Função para criar um novo nó
No *criarNo(int valor)
{
    No *novoNo = (No *)malloc(sizeof(No));
    if (novoNo == NULL) {
        printf("Erro de alocação de memória.\n");
        exit(1);
    }
    novoNo->valor = valor;
    novoNo->cor = VERMELHO;
    novoNo->esquerda = novoNo->direita = novoNo->pai = NULL;
    return novoNo;
}

// Função para fazer a rotação à esquerda
void rotacaoEsquerda(No **raiz, No *x)
{
    No *y = x->direita;
    x->direita = y->esquerda;
    
    if (y->esquerda != NULL){
        y->esquerda->pai = x;
    }
    
    y->pai = x->pai;
    
    if (x->pai == NULL){
        *raiz = y;
    }
    else if (x == x->pai->esquerda){
        x->pai->esquerda = y;
    }
    else{
        x->pai->direita = y;
    }
    
    y->esquerda = x;
    x->pai = y;
}

// Função para fazer a rotação à direita
void rotacaoDireita(No **raiz, No *x)
{
    No *y = x->esquerda;
    x->esquerda = y->direita;
    
    if (y->direita != NULL){
        y->direita->pai = x;
    }
    y->pai = x->pai;
    
    if (x->pai == NULL){
        *raiz = y;
    }
    else if (x == x->pai->direita){
        x->pai->direita = y;
    }
    else{
        x->pai->esquerda = y;
    }
    
    y->direita = x;
    x->pai = y;
}

// Função para balancear a árvore após a inserção de um nó
void corrigirViolacoes(No **raiz, No *no) {
    while (no != *raiz && no->pai->cor == VERMELHO) {
        No *tio;

        if (no->pai == no->pai->pai->esquerda) {
            tio = no->pai->pai->direita;
            
            // Caso 1: O tio é vermelho
            if (tio != NULL && tio->cor == VERMELHO) {
                no->pai->cor = PRETO;
                tio->cor = PRETO;
                no->pai->pai->cor = VERMELHO;
                no = no->pai->pai;
            } else {
                // Caso 2: no é filho direito
                if (no == no->pai->direita) {
                    no = no->pai;
                    rotacaoEsquerda(raiz, no);
                }
                
                // Caso 3: no é filho esquerdo
                no->pai->cor = PRETO;
                no->pai->pai->cor = VERMELHO;
                rotacaoDireita(raiz, no->pai->pai);
            }
        } else {
            tio = no->pai->pai->esquerda;
            
            // Caso 1: O tio é vermelho
            if (tio != NULL && tio->cor == VERMELHO) {
                no->pai->cor = PRETO;
                tio->cor = PRETO;
                no->pai->pai->cor = VERMELHO;
                no = no->pai->pai;
            } else {
                // Caso 2: no é filho esquerdo
                if (no == no->pai->esquerda) {
                    no = no->pai;
                    rotacaoDireita(raiz, no);
                }
                
                // Caso 3: no é filho direito
                no->pai->cor = PRETO;
                no->pai->pai->cor = VERMELHO;
                rotacaoEsquerda(raiz, no->pai->pai);
            }
        }
    }
    (*raiz)->cor = PRETO;  // A raiz deve sempre ser preta
}

// Função para inserir um novo nó na árvore Red-Black
void inserir(No **raiz, int valor)
{
    No *z = criarNo(valor);
    No *y = NULL;
    No *x = *raiz;

    while (x != NULL){
        y = x;
        if (z->valor < x->valor){
            x = x->esquerda;
        }
        else{
            x = x->direita;
        }
    }
    
    z->pai = y;
    
    if (y == NULL){
        *raiz = z;
    }
    else if (z->valor < y->valor){
        y->esquerda = z;
    }
    else{
        y->direita = z;
    }
    
    corrigirViolacoes(raiz, z);
}

// Função para imprimir a árvore de acordo com o formato esquerda-raiz-direita segundo Sedgewick
void imprimeArvore(No *raiz, int nivel){
  if (raiz == NULL) return;

  imprimeArvore(raiz->direita, nivel + 1);

  for (int i = 0; i < nivel; i++) printf("   ");
  printf("%d(%s)\n", raiz->valor, raiz->cor == VERMELHO ? "V" : "P");

  imprimeArvore(raiz->esquerda, nivel + 1);
}

No* buscar(No *raiz, int valor) {
    while (raiz != NULL && valor != raiz->valor) {
        if (valor < raiz->valor) {
            raiz = raiz->esquerda;
        } else {
            raiz = raiz->direita;
        }
    }
    return raiz;
}

int main()
{
    struct No *raiz = NULL;
    
    // Exemplo de inserção de valores na árvore Red-Black
    inserir(&raiz, 10);
    inserir(&raiz, 22);
    inserir(&raiz, 46);
    inserir(&raiz, 13);
    inserir(&raiz, 12);
    inserir(&raiz, 2);
    
    printf("Árvore Red-Black: \n");
    imprimeArvore(raiz, 1);
    
    int valorBuscado = 59;
    No *resultado = buscar(raiz, valorBuscado);
    
    if (resultado != NULL) {
        printf("Valor %d encontrado, cor: %s\n", resultado->valor, resultado->cor == VERMELHO ? "Vermelho" : "Preto");
    } else {
        printf("Valor %d não encontrado.\n", valorBuscado);
    }

    return 0;
}
