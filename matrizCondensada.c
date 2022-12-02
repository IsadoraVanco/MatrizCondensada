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

elemento* LerMatriz(FILE *arquivo);
void EscreverMatriz(elemento *inicio);
elemento* SomarMatrizes(elemento *inicioA, elemento *inicioB);
void ApagarMatriz(elemento *inicio);

int main() {
    elemento* inicioA = NULL;
    elemento* inicioB = NULL;
    elemento* inicioC = NULL;

    FILE *arquivo;
    arquivo = fopen(NOME_ARQUIVO, "r");
    if(arquivo == NULL){
        printf("Arquivo %s nao encontrado.", NOME_ARQUIVO);
        return 1;
    }

    inicioA = LerMatriz(arquivo);
    inicioB = LerMatriz(arquivo);
    fclose(arquivo);

    
    printf("\n*****A*****\n");
    EscreverMatriz(inicioA);
    
    printf("*****B*****\n");
    EscreverMatriz(inicioB);
    
    printf("*****C*****\n");
    //soma e escreve a matriz resultante
    inicioC = SomarMatrizes(inicioA, inicioB);
    
    ApagarMatriz(inicioA);
    ApagarMatriz(inicioB);
    ApagarMatriz(inicioC);
    
    return 0;
}

//guarda a matriz já condensada e retorna o ponteiro do inicio
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

//escreve as informações da matriz condensada e a matriz completa
void EscreverMatriz(elemento *inicio){
    elemento* aux = inicio;
    
    printf("Matriz Condensada:\n");
    //escreve a matriz condensada
    while(inicio != NULL){
        printf("%d [%d, %d]\n", inicio -> valor, inicio -> i + 1, inicio -> j + 1);
        inicio = inicio -> proxElemento;
    }
    printf("\n");

    //retorna o ponteiro para o inicio (passado como parametro)
    inicio = aux;

    printf("Matriz Completa:\n");
    //escreve a matriz inteira (com elementos 0)
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

//soma as duas matrizes, escreve e retorna o ponteiro do inicio dela
elemento* SomarMatrizes(elemento *inicioA, elemento *inicioB){
    elemento *inicioC = NULL;
    elemento *elementoAnterior, *novoElemento;
    int c;

    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++){
            c = 0;
            
            if(inicioA -> i == i && inicioA -> j == j){
                c += inicioA -> valor;
                if(inicioA -> proxElemento != NULL){
                    inicioA = inicioA -> proxElemento;
                }
            }
            if(inicioB -> i == i && inicioB -> j == j){
                c += inicioB -> valor;
                if(inicioB -> proxElemento != NULL){
                    inicioB = inicioB -> proxElemento;
                }
            }

            if(c != 0){
                novoElemento = malloc(sizeof(elemento));
                novoElemento -> valor = c;
                novoElemento -> i = i;
                novoElemento -> j = j;
                novoElemento -> proxElemento = NULL;
                
                // se o inicio ainda não aponta para algum endereço
                // ou seja, é o primeiro elemento identificado,
                // atribui o endereço do primeiro para o inicio
                if(inicioC == NULL){
                    inicioC = novoElemento;
                    elementoAnterior = novoElemento;
                }else{ //caso haja elementos existentes
                    elementoAnterior -> proxElemento = novoElemento;
                    elementoAnterior = novoElemento;
                }
            }
        }
    }

    EscreverMatriz(inicioC);
    return inicioC;
}

//apaga a matriz passada como parametro
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
