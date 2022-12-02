#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//sempre quadrada
#define N 15
#define NOME_ARQUIVO "matrizes.txt"

struct cel{
    int valor;
    int i;
    int j;
    struct cel* proxElemento;
};
typedef struct cel elemento;

void EscreverMatriz(elemento *inicio);
void ApagarMatriz(elemento *inicio);
elemento* LerMatriz(FILE *arquivo);

int main() {
    
    elemento* inicioA = NULL;
    elemento* inicioB = NULL;

    FILE *arquivo;
    arquivo = fopen(NOME_ARQUIVO, "r");
    if(arquivo == NULL){
        printf("Arquivo %s nao encontrado.", NOME_ARQUIVO);
        return 1;
    }

    inicioA = LerMatriz(arquivo);
    inicioB = LerMatriz(arquivo);
    
    printf("A\n");
    EscreverMatriz(inicioA);
    ApagarMatriz(inicioA);
    
    printf("B\n");
    EscreverMatriz(inicioB);
    ApagarMatriz(inicioB);
    
    fclose(arquivo);
    
    return 0;
}

void EscreverMatriz(elemento *inicio){
    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++){

            if(inicio -> i == i && inicio -> j == j && inicio -> valor != 0){
                printf("%d ", inicio -> valor);
                if(inicio -> proxElemento != NULL){
                    inicio = inicio -> proxElemento;
                }
            }else{
                printf("%d ", 0);
            }
        }
        printf("\n");
    }
    printf("\n");
}

void ApagarMatriz(elemento *inicio){
    elemento *proximo, *elemento;
    
    //recebe o endereço do primeiro elemento
    proximo = inicio;

    //percorre toda lista até achar o ultimo elemento (NULL)
    while(proximo != NULL){
        //recebe o endereço do elemento 
        elemento = proximo;
        //recebe o endereço do proximo elemento
        proximo = proximo -> proxElemento;
        //apaga o elemento
        free(elemento);
    }
    //aterra o ponteiro do inicio
    inicio = NULL;
    printf("Matriz apagada.\n");
}

//guarda a matriz já condensada
elemento* LerMatriz(FILE *arquivo){
    char linha[N + 1];
    int n;
    
    elemento *inicio = NULL;
    elemento *elementoAnterior, *novoElemento;

    //considere a matriz sem erros!
    for(int i = 0; i < N; i++){
        //le com ou sem uma linha separando (espaço)
        fscanf(arquivo, "%s\n", linha);
        
        for(int j = 0; j < N; j++){
            //transforma o caractere em inteiro
            n = linha[j] - '0';
            if(n != 0){
                // printf("%d ", n);
                novoElemento = malloc(sizeof(elemento));
                novoElemento -> valor = n;
                novoElemento -> i = i;
                novoElemento -> j = j;
                novoElemento -> proxElemento = NULL;
                
                // se o inicio ainda não aponta para algum endereço
                // ou seja, é o primeiro elemento identificado,
                // atribui o endereço do primeiro para o inicio
                if(inicio == NULL){
                    inicio = novoElemento;
                    elementoAnterior = novoElemento;
                }else{ //caso haja elementos existentes
                    elementoAnterior -> proxElemento = novoElemento;
                    elementoAnterior = novoElemento;
                }
            }
        }
        // printf("\n");
    }

    //retorna apenas o ponteiro do primeiro elemento
    return inicio;
}