#include <stdio.h>
#include <stdlib.h>

// Definição do nó da Treap
typedef struct No {
    struct No* esquerda;
    struct No* direita;
    int valor;
    int peso;
} No;

No* newNo(int valor, int peso) {
    No* no = (No*)malloc(sizeof(No));
    if (node == NULL) {
        printf("Erro ao alocar memória!\n");
        exit(1);
    }
    node->lesquerda = NULL;
    node->direita = NULL;
    node->valor = value;
    node->peso = peso;
    return no;
}

No* Rotatedireita(No* x) {
    No* y = x->esquerda;
    No* T2 = y->direita;
    y->direita = x;
    x->esquerda = T2;
    return y;
}

No* Rotateesquerda(No* x) {
    No* y = x->direita;
    No* T2 = y->esquerda;
    y->esquerda = x;
    x->direita = T2;
    return y;
}

No* Inserir(No* raiz, int valor) {
    if (raiz == NULL)
        return newNo(valor);
  
    if (valor < raiz->valor) {
        raiz->esquerda = inserir(raiz->esquerda, valor);
        if (raiz->esquerda->peso > raiz->peso)
            raiz = rotacionardireita(raiz);
    } else if (valor > raiz->valor) {
        raiz->direita = inserir(raiz->direita, valor);
        if (raiz->direita->peso > raiz->peso)
            raiz = rotacionaresquerda(raiz);
    }
    return raiz;
}

No* Deletar(No* raiz, int valor) {
    if (raiz == NULL)
        return NULL;

    if (valor < raiz->valor)
        raiz->esquerda = deletar(raiz->esquerda, valor);
    else if (valor > raiz->valor)
        raiz->direita = deletar(raiz->direita, valor);
    else {
        if (raiz->esquerda == NULL) {
            No* temp = raiz->direita;
            free(raiz);
            return temp;
        } else if (raiz->direita == NULL) {
            No* temp = raiz->esquerda;
            free(raiz);
            return temp;
        }

        if (raiz->esquerda->peso > raiz->direita->peso) {
            raiz = rotacionarDireita(raiz);
            raiz->direita = deletar(raiz->direita, valor);
        } else {
            raiz = rotacionarEsquerda(raiz);
            raiz->esquerda = deletar(raiz->esquerda, valor);
        }
    }
    return raiz;
}

No* buscar(No* raiz, int valor) {
    if (raiz == NULL || raiz->valor == valor)
        return raiz;

    if (valor < raiz->valor)
        return buscar(raiz->esquerda, valor);
    else
        return buscar(raiz->direita, valor);
}

void exibirEmOrdem(No* raiz) {
    if (raiz != NULL) {
        exibirEmOrdem(raiz->esquerda);
        printf("valor: %d, peso: %d\n", raiz->valor, raiz->peso);
        exibirEmOrdem(raiz->direita);
    }
}

int main()
{
    struct No *raiz = NULL;

    inserir(&raiz, 10);
    inserir(&raiz, 22);
    inserir(&raiz, 46);
    inserir(&raiz, 13);
    inserir(&raiz, 12);
    inserir(&raiz, 2);
    
    printf("Árvore Treap: \n");
    exibirEmOrdem(raiz);
    
    int valorBuscado = 59;
    No *resultado = buscar(raiz, valorBuscado);
    
    if (resultado != NULL) {
        printf("Valor %d encontrado, peso: %s\n", resultado->valor, resultado->peso;
    } else {
        printf("Valor %d não encontrado.\n", valorBuscado);
    }

    return 0;
}
