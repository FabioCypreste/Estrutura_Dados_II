#include <stdio.h>
#include <stdlib.h>

#define MAX_GRAU 3

typedef struct No {
    int valor;
    int numChaves;
    int chaves[MAX_GRAU - 1];
    struct No* filhos[MAX_GRAU];
} No;

No* criarNo(int valor) {
    No* novoNo = (No*)malloc(sizeof(No));
    if (novoNo == NULL) {
        printf("Erro de alocação de memória!\n");
        exit(1);
    }
    novoNo->valor = valor;
    novoNo->numChaves = 0;
    for (int i = 0; i < MAX_GRAU; i++) {
        novoNo->filhos[i] = NULL;
    }
    return novoNo;
}

void dividirFilho(No* pai, int indice) {
    No* filho = pai->filhos[indice];
    No* novoNo = criarNo(filho->valor);

    for (int j = MAX_GRAU / 2; j < MAX_GRAU - 1; j++) {
        novoNo->chaves[j - MAX_GRAU / 2] = filho->chaves[j];
    }

    if (!filho->valor) {
        for (int j = MAX_GRAU / 2; j < MAX_GRAU; j++) {
            novoNo->filhos[j - MAX_GRAU / 2] = filho->filhos[j];
        }
    }

    filho->numChaves = MAX_GRAU / 2 - 1;
    novoNo->numChaves = MAX_GRAU / 2 - 1;

    for (int j = pai->numChaves; j > indice; j--) {
        pai->filhos[j + 1] = pai->filhos[j];
    }
    pai->filhos[indice + 1] = novoNo;

    for (int j = pai->numChaves - 1; j >= indice; j--) {
        pai->chaves[j + 1] = pai->chaves[j];
    }
    pai->chaves[indice] = filho->chaves[MAX_GRAU / 2 - 1];
    pai->numChaves++;
}

void inserirNaoCheio(No* no, int chave) {
    int i = no->numChaves;
    if (no->valor) {
        while (i > 0 && chave < no->chaves[i - 1]) {
            no->chaves[i] = no->chaves[i - 1];
            i--;
        }
        no->chaves[i] = chave;
        no->numChaves++;
    } else {
        while (i > 0 && chave < no->chaves[i - 1]) {
            i--;
        }

        if (no->filhos[i]->numChaves == MAX_GRAU - 1) {
            dividirFilho(no, i);
            if (chave > no->chaves[i]) {
                i++;
            }
        }
        inserirNaoCheio(no->filhos[i], chave);
    }
}

No* inserir(No* raiz, int chave) {
    if (raiz == NULL) {
        raiz = criarNo(1);
        raiz->chaves[0] = chave;
        raiz->numChaves = 1;
    } else {
        if (raiz->numChaves == MAX_GRAU - 1) {
            No* novaRaiz = criarNo(0);
            novaRaiz->filhos[0] = raiz;
            dividirFilho(novaRaiz, 0);
            int i = 0;
            if (chave > novaRaiz->chaves[0]) {
                i++;
            }
            inserirNaoCheio(novaRaiz->filhos[i], chave);
            raiz = novaRaiz;
        } else {
            inserirNaoCheio(raiz, chave);
        }
    }
    return raiz;
}

void imprimirArvore(No* no, int nivel) {
    if (no != NULL) {
        for (int i = 0; i < nivel; i++) {
            printf("  ");
        }
        for (int i = 0; i < no->numChaves; i++) {
            printf("%d ", no->chaves[i]);
        }
        printf("\n");

        for (int i = 0; i <= no->numChaves; i++) {
            imprimirArvore(no->filhos[i], nivel + 1);
        }
    }
}

int main() {
    No* raiz = NULL;

    raiz = inserir(raiz, 15);
    raiz = inserir(raiz, 25);
    raiz = inserir(raiz, 8);
    raiz = inserir(raiz, 10);
    raiz = inserir(raiz, 18);
    raiz = inserir(raiz, 40);
    raiz = inserir(raiz, 12);
    raiz = inserir(raiz, 22);

    imprimirArvore(raiz, 0);

    return 0;
}
