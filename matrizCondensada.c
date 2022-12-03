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
elemento* MultiplicarMatrizes(elemento *inicioA, elemento *inicioB);
int SomarElementosAbaixoDiagonal(elemento *inicio);
void ApagarMatriz(elemento *inicio);

int main() {
    elemento* inicioA = NULL;
    elemento* inicioB = NULL;
    elemento* inicioC = NULL;
    elemento* inicioD = NULL;
    FILE *arquivo;
    int elementosC;
    
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
    inicioC = SomarMatrizes(inicioA, inicioB);
    elementosC = SomarElementosAbaixoDiagonal(inicioC);
    
    printf("\n*****D*****\n");
    inicioD = MultiplicarMatrizes(inicioA, inicioB);
    
    ApagarMatriz(inicioA);
    ApagarMatriz(inicioB);
    ApagarMatriz(inicioC);
    ApagarMatriz(inicioD);
    
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

//escreve cada valor da matriz condensada em suas respectivas posições e a matriz completa
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

//soma as duas matrizes, escreve o resultado e retorna o ponteiro do inicio da resultante
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

//multiplica as duas matrizes, escreve o resultado e retorna o ponteiro do inicio da resultante
elemento* MultiplicarMatrizes(elemento *inicioA, elemento *inicioB){
    elemento *auxA = inicioA; //guarda o endereço inicial de A
    elemento *auxB = inicioB; //guarda o endereço inicial de B
    
    elemento *inicioC = NULL;
    elemento *elementoAnterior, *novoElemento;

    int somaElemento, multiplicacaoElemento;

    for(int i = 0; i < N; i++){ //linha do elemento resultante
        for(int j = 0; j < N; j++){ //coluna do elemento resultante
            somaElemento = 0;
            
            for(int n = 0; n < N; n++){ //posição do elemento na linha/coluna
                //retorna os ponteiros para o inicio de cada matriz
                inicioA = auxA; 
                inicioB = auxB;
                multiplicacaoElemento = 0;
                
                while(inicioA != NULL){ //procura se tem o elemento na linha da matriz A
                    if(inicioA -> i == i && inicioA -> j == n){
                        multiplicacaoElemento = inicioA -> valor;
                        break;
                    }else{
                        inicioA = inicioA -> proxElemento;
                    }
                }

                while(inicioB != NULL){ //procura se tem o elemento na coluna da matriz B
                    if(inicioB -> j == j && inicioB -> i == n){
                        multiplicacaoElemento *= inicioB -> valor;
                        break;
                    }else{
                        inicioB = inicioB -> proxElemento;
                    }
                }

                if(inicioB == NULL){ //se não encontrou o elemento de B 
                    multiplicacaoElemento = 0;
                }
                somaElemento += multiplicacaoElemento;
            }

            if(somaElemento != 0){ //armazena na lista ligada
                novoElemento = malloc(sizeof(elemento));
                novoElemento -> valor = somaElemento;
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

//soma os elementos abaixo da diagonal principal e retorna o resultado
int SomarElementosAbaixoDiagonal(elemento *inicio){
    int resultado = 0;

    while(inicio != NULL){
        //se o elemento estiver na diagonal ou abaixo dela
        if(inicio -> j < inicio -> i){
            resultado += inicio -> valor;
            inicio = inicio -> proxElemento;
        }else{
            inicio = inicio -> proxElemento;
        }
    }

    printf("O resultado da soma de todos os elementos abaixo da diagonal principal da matriz eh %d.\n", resultado);
    return resultado;
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
