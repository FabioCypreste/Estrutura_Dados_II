#include <stdio.h>
#include <stdlib.h>

//Struct de criação de um nó de uma árvore.
typedef struct No{
  int dado;
  struct No *esquerda;
  struct No *direita;
} No;

//Função para criação de nó de uma árvore binária
No *createNo(int dado){
  No *newNo = (No*)malloc(sizeof(No));
  
  if (newNo == NULL){
    printf("Erro: Falha ao alocar memória para o novo nó.\n");
    exit(-1);
  }
  
  newNo->dado = dado;
  newNo->esquerda = NULL;
  newNo->direita = NULL;
  
  return newNo;
}

//Função de inserção de um nó em uma árvore binária.
No *insertNo(No *raiz, int dado){
  if (raiz == NULL){
    raiz = createNo(dado);
  }
  else{
    if (dado <= raiz->dado){
      raiz->esquerda = insertNo(raiz->esquerda, dado);
    }
    else{
      raiz->direita = insertNo(raiz->direita, dado);
    }
  }
  
  return raiz;
}

//Função para encontrar o nó que possui o menor valor em uma árvore binária.
No *findMinNo(No *raiz){
  while (raiz->esquerda != NULL) {
    raiz = raiz->esquerda;
  }
  
  return raiz;
}

//Função para excluir um nó em uma árvore binária.
No *excludeNo(No *raiz, int dado){
  if (raiz == NULL){
    return raiz;
  }
  else if (dado < raiz->dado){
    raiz->esquerda = excludeNo(raiz->esquerda, dado);
  } 
  else if (dado > raiz->dado){
    raiz->direita = excludeNo(raiz->direita, dado);
  } 
  else{
    // Caso 1: Nó com apenas um filho ou nenhum
    if (raiz->esquerda == NULL){
      No *temp = raiz->direita;
      free(raiz);
      return temp;
    }
    else if (raiz->direita == NULL){
      No *temp = raiz->esquerda;
      free(raiz);
      return temp;
    }

    // Caso 2: Nó com dois filhos, é encontrado o sucessor in-order;
    No *temp = findMinNo(raiz->direita);
    raiz->dado = temp->dado;
    raiz->direita = excludeNo(raiz->direita, temp->dado);
  }
  return raiz;
}

// Função para realizar a pesquisa de um elemento em uma árvore binária.
No *searchNo(No *raiz, int dado){
  if (raiz == NULL || raiz->dado == dado){
    return raiz;
  }
  if (dado < raiz->dado){
    return searchNo(raiz->esquerda, dado);
  }
  return searchNo(raiz->direita, dado);
}

//Função para imprimir no console uma árvore binária.
void printTree(No *raiz, int profundidade){
  if (raiz == NULL) {
    return;
  }
  printTree(raiz->direita, profundidade + 1);
  for(int i = 0; i < profundidade; i++){
    printf("  ");
  }
  
  printf("%d\n", raiz->dado);
  printTree(raiz->esquerda, profundidade + 1);
}

int main(){
  //Definição da raíz da árvore binária e criação de seus nós.
  No *raiz = NULL;
  raiz = insertNo(raiz, 16);
  insertNo(raiz, 15);
  insertNo(raiz, 4);
  insertNo(raiz, 8);
  insertNo(raiz, 42);
  insertNo(raiz, 23);

  //Encontrando o menor valor da árvore binária:
  printf("Encontro do menor valor da árvore binária pela função findMinNo(): \n");
  No *minNo = findMinNo(raiz);
  if (minNo != NULL) {
    printf("Menor valor: %d\n", minNo->dado);
  }

  //Encontro de um valor existente e um existente na árvore binária
  int i;
  int valor = 23;
  for (i=0;i <= 1; i++){
    if (searchNo(raiz, valor) == NULL){
      printf("Valor %d não encontrado na árvore binária. \n", valor);
    }
    else{
      printf("Valor %d encontrado. \n", valor);
    }
    valor = valor + 7;
  }
  
  //Impressão da árvore binária
  printf("Árvore binária sendo criada pela função PrintTree(): \n");
  printTree(raiz, 0);

  //Deleção de um valor na árvore binária
  valor = 15;
  printf("Exclusão do nó com valor 15 da árvore binária.\n");
  raiz = excludeNo(raiz, valor);

  //Impressão da árvore após exclusão
  printf("Árvore após exclusão do nó:\n");
  printTree(raiz, 0);

  //Inserção de um valor na árvore binaria
  valor = 80;
  insertNo(raiz, valor);

  //Impressão da árvore após inserção
  printf("Árvore após inserção do nó:\n");
  printTree(raiz, 0);
  return 0;
}
