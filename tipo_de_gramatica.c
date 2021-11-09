#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>


typedef struct reg {
   char   cadeia[20];
   struct reg *prox ;
} regras;



int main(void) {
  int n=0;
  bool Tipo1 = true;
  bool Tipo2 = true;
  bool Tipo3 = true;

  regras *esq = NULL;
  regras *dir = NULL;
  regras *exc = NULL;

  printf("digite a quantidade de regras:\n");
  scanf("%d",&n);
  printf("Digite a regras sendo '->' igual a '=' e 'ε' = '(vazio)': \n");
  for(int i=0;i<n;i++){

    regras *nEsq = (regras*)malloc(sizeof(regras));
    regras *nDir = (regras*)malloc(sizeof(regras));

    char string[20];
    scanf("%s", string);

      //divide cada regra em esq e direita
    char *s1= strtok(string, "=");
    char *s2= strtok(NULL, "\0");

    //inclui possivel exceção na lista de exceçoes
    if(s2 == NULL){
      regras *nexc = (regras*)malloc(sizeof(regras));
      strcpy(nexc->cadeia , s1 );
      nexc->prox = exc;
      exc = nexc;
    }

    //cria lista da esquerda
    strcpy(nEsq->cadeia , s1 );
    nEsq->prox = esq;
    esq = nEsq;

    //cria lista da direita
    if(s2!=NULL){
      strcpy(nDir->cadeia , s2 );
      nDir->prox = dir;
      dir = nDir;
    }

    //confere se quebra o tipo 1
    if(s2!=NULL){
      if(strlen(s1)>strlen(s2))
       Tipo1 = false;
    }

  }

      //confere se a exceção quebra o tipo 1
  if(exc != NULL){
    regras *aux = exc;
    regras *auxDir = dir;
    while(aux!=NULL){
      while(auxDir!=NULL){
         if(strstr(auxDir->cadeia,aux->cadeia))
          Tipo1 = false;
        auxDir=auxDir->prox;
      }
    aux=aux->prox;
    }
  }

  printf("\n-------------TIPO 0--------------\n");

  if(Tipo1)
    printf("\n-------------TIPO 1--------------\n");

    //confere se quebra o tipo 2
    regras *aux = esq;
    while(aux!=NULL){
      if(strlen(aux->cadeia)>1){
        Tipo2 = false;
        Tipo3 = false;
      }
      else if (!(isupper(aux->cadeia[0]))){
        Tipo2 = false;
        Tipo3 = false;
      }
    aux=aux->prox;
    }

  if(Tipo2){
  printf("\n-------------TIPO 2--------------\n");

    //confere se quebra o tipo 3
    regras *aux = dir;
    while(aux!=NULL){

      int n = strlen(aux->cadeia);

      if(n>2)
        Tipo3 = false;
      else if(n==2){
        if (isupper(aux->cadeia[0]) || !(isupper(aux->cadeia[1])))
          Tipo3 = false;
      }else
        if(isupper(aux->cadeia[0]))
          Tipo3 = false;
    aux=aux->prox;
    }
  }

  if(Tipo3)
    printf("\n-------------TIPO 3--------------\n");


  return 0;
}
