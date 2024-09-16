#include <stdio.h>
#include <stdlib.h>

//Definição da estrutura de um nó da árvore AVL;
typedef struct NoAVL
{
    int dado;
    struct NoAVL *esquerda;
    struct NoAVL *direita;
    int altura;
} NoAVL;

//Função que realiza a criação de um nó
NoAVL *criarNo(int dado){
    NoAVL *newNo = (NoAVL*)malloc(sizeof(NoAVL));
    if (newNo == NULL){
        printf("Erro: Falha ao alocar memória para o novo nó.\n");
        exit(-1);
    }
    newNo->dado = dado;
    newNo->direita = NULL;
    newNo->esquerda = NULL;
    newNo->altura = 0;
    return newNo;
}

//Função que verifica a altura de um nó;
int altura(NoAVL *no){
    if (no == NULL){
        return -1;
    }
    return no->altura;
}

//Função que verifica o fator de balanceamento de um nó na arvore;
int fatorBalanceamento(NoAVL *no){
    return no ? altura(no->esquerda) - altura(no->direita) : 0;
}

NoAVL *rotacaoDireita(struct NoAVL *no)
{
    NoAVL *novaRaiz = no->esquerda;
    NoAVL *subArvore = novaRaiz->direita;

    // Realiza a rotação
    novaRaiz->direita = no;
    no->esquerda = subArvore;
    
    no->altura = 1 + (altura(no->esquerda) > altura(no->direita) ? altura(no->esquerda) : altura(no->direita));
    novaRaiz->altura = 1 + (altura(novaRaiz->esquerda) > altura(novaRaiz->direita) ? altura(novaRaiz->esquerda) : altura(novaRaiz->direita));
    
    return novaRaiz;
}

struct NoAVL *rotacaoEsquerda(struct NoAVL *no)
{
    struct NoAVL *novaRaiz = no->direita;         // Define a nova raiz como o nó à direita
    struct NoAVL *subArvore = novaRaiz->esquerda; // Define a subárvore como a subárvore esquerda da nova raiz

    // Realiza a rotação
    novaRaiz->esquerda = no; // Define o nó como filho esquerdo da nova raiz
    no->direita = subArvore; // Define a subárvore esquerda da nova raiz como filho direito do nó

    // Atualiza as alturas
    no->altura = 1 + (altura(no->esquerda) > altura(no->direita) ? altura(no->esquerda) : altura(no->direita));
    novaRaiz->altura = 1 + (altura(novaRaiz->esquerda) > altura(novaRaiz->direita) ? altura(novaRaiz->esquerda) : altura(novaRaiz->direita));

    return novaRaiz; // Retorna a nova raiz após a rotação
}

NoAVL *balanceamento(struct NoAVL *raiz, int dado)
{
    if (raiz == NULL)
    {
        return raiz;
    }
    
    raiz->altura = 1 + (altura(raiz->esquerda) > altura(raiz->direita) ? altura(raiz->esquerda) : altura(raiz->direita));

    // Calcula o fator de balanceamento deste nó para verificar se ele se tornou desbalanceado
    int balanceamento = fatorBalanceamento(raiz);

    // Caso de desbalanceamento à esquerda-esquerda
    if (balanceamento > 1 && dado < raiz->esquerda->dado) // Se o fator de balanceamento for maior que 1 e o dado for menor que o dado da subárvore esquerda
        return rotacaoDireita(raiz);                      // Realiza rotação simples à direita

    // Caso de desbalanceamento à direita-direita
    if (balanceamento < -1 && dado > raiz->direita->dado) // Se o fator de balanceamento for menor que -1 e o dado for maior que o dado da subárvore direita
        return rotacaoEsquerda(raiz);                     // Realiza rotação simples à esquerda

    // Caso de desbalanceamento à esquerda-direita
    if (balanceamento > 1 && dado > raiz->esquerda->dado) // Se o fator de balanceamento for maior que 1 e o dado for maior que o dado da subárvore esquerda
    {
        raiz->esquerda = rotacaoEsquerda(raiz->esquerda); // Realiza rotação dupla à esquerda
        return rotacaoDireita(raiz);
    }

    // Caso de desbalanceamento à direita-esquerda
    if (balanceamento < -1 && dado < raiz->direita->dado) // Se o fator de balanceamento for menor que -1 e o dado for menor que o dado da subárvore direita
    {
        raiz->direita = rotacaoDireita(raiz->direita); // Realiza rotação dupla à direita
        return rotacaoEsquerda(raiz);
    }

    // Retorna a raiz inalterada
    return raiz; // Retorna a raiz após o balanceamento
}

// Função para inserir um novo nó na árvore AVL
struct NoAVL *inserir(struct NoAVL *raiz, int dado)
{
    // Verifica se a raiz é nula, indicando que estamos em uma folha da árvore ou que a árvore está vazia
    if (raiz == NULL)
    {
        // Se a raiz for nula, cria um novo nó com o dado fornecido e o retorna como a nova raiz da árvore
        return criarNo(dado);
    }

    // Se o dado a ser inserido for menor que o valor da raiz atual, insere recursivamente na subárvore esquerda
    if (dado < raiz->dado)
    {
        raiz->esquerda = inserir(raiz->esquerda, dado);
    }
    // Se o dado for maior que o valor da raiz atual, insere recursivamente na subárvore direita
    else if (dado > raiz->dado)
    {
        raiz->direita = inserir(raiz->direita, dado);
    }
    else
    {
        // Se o dado for igual ao valor da raiz atual, não faz nada (dados iguais não são permitidos na árvore AVL)
        return raiz;
    }

    // Após a inserção, chama a função de balanceamento para garantir que a árvore permaneça balanceada
    return balanceamento(raiz, dado);
}

struct NoAVL* encontrarMaximo(struct NoAVL* no) {
    if (no == NULL)
        return NULL;
    while (no->direita != NULL){
        no = no->direita;
    }
    return no;
}

struct NoAVL *encontrarMinimo(struct NoAVL *no)
{
    struct NoAVL *atual = no;
    while (atual && atual->esquerda != NULL)
        atual = atual->esquerda;
    return atual;
}

struct NoAVL *excluir(struct NoAVL *raiz, int valor) {
    if (raiz == NULL)
    {
        return raiz;
    }

    if (valor < raiz->dado)
    {
        raiz->esquerda = excluir(raiz->esquerda, valor);
    }
    else if (valor > raiz->dado)
    {
        raiz->direita = excluir(raiz->direita, valor);
    }
    else
    {
        
        if (raiz->esquerda == NULL)
        {
            struct NoAVL *temp = raiz->direita;
            free(raiz);
            return temp;
        }
        else if (raiz->direita == NULL)
        {
            struct NoAVL *temp = raiz->esquerda;
            free(raiz);
            return temp;
        }

        // Caso 2: Nó com dois filhos
        if (altura(raiz->esquerda) >= altura(raiz->direita)) {
            struct NoAVL *temp = encontrarMaximo(raiz->esquerda);
            raiz->dado = temp->dado;
            raiz->esquerda = excluir(raiz->esquerda, temp->dado);
        } else {
            struct NoAVL *temp = encontrarMinimo(raiz->direita);
            raiz->dado = temp->dado;
            raiz->direita = excluir(raiz->direita, temp->dado);
        }
    }
    return balanceamento(raiz, valor);
}

// Função para imprimir um nó
void imprimeNo(int c, int b){
    int i;
    for (i = 0; i < b; i++)
        printf("   ");
    printf("%i\n", c);
}

//Função que mostra a árvore AVL
void mostraArvore(struct NoAVL *a, int b){
    if (a != NULL){
        mostraArvore(a->direita, b + 1);
        imprimeNo(a->dado, b);
        mostraArvore(a->esquerda, b + 1);
    }
}

int main()
{

    struct NoAVL *raiz = NULL;
    raiz = inserir(raiz, 10);
    raiz = inserir(raiz, 55);
    raiz = inserir(raiz, 29);
    raiz = inserir(raiz, 52);
    raiz = inserir(raiz, 87);
    raiz = inserir(raiz, 99);
    mostraArvore(raiz, 3);
   
    printf("\nLetra A - Insere 31 ---------------------------\n");
    raiz = inserir(raiz, 31);
    mostraArvore(raiz, 3);
   
    printf("\nLetra B - Insere 15 ---------------------------\n");
    raiz = inserir(raiz, 15);
    mostraArvore(raiz, 3);
   
    printf("\nLetra C - Insere 23 ----------------------------\n");
    raiz = inserir(raiz, 23);
    mostraArvore(raiz, 3);
   
    printf("\nLetra D - Exclui 24 ---------------------------\n");
    raiz = excluir(raiz, 24);
    mostraArvore(raiz, 3);
   
    printf("\nLetra E - Exclui 35 ---------------------------\n");
    raiz = excluir(raiz, 35);
    mostraArvore(raiz, 3);

     printf("\nLetra F - Inserir 24 ---------------------------\n");
    raiz = inserir(raiz, 24);
    mostraArvore(raiz, 3);

     printf("\nLetra G - Exclui 27 ---------------------------\n");
    raiz = excluir(raiz, 27);
    mostraArvore(raiz, 3);

     printf("\nLetra H - Inserir 32 ---------------------------\n");
    raiz = inserir(raiz, 32);
    mostraArvore(raiz, 3);

     printf("\nLetra I - Exclui 30 ---------------------------\n");
    raiz = excluir(raiz, 30);
    mostraArvore(raiz, 3);
    
    printf("\nLetra J - Inserir 21 ---------------------------\n");
    raiz = inserir(raiz, 21);
    mostraArvore(raiz, 3);

    return 0;
}
