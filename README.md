# Matriz Condensada

Uma matriz de elementos numéricos pode apresentar elementos com valor igual a 0 (zero). A representação condensada da mesma matriz utiliza uma lista ligada onde somente elementos da matriz original com valores diferentes de zero são armazenados.

Faça um programa que leia duas matrizes (A e B) 15 por 15 de elementos numéricos. Implemente as seguintes funções:

* A **leitura** da matriz deve ser realizada por uma função, os elementos das duas matrizes estarão em um arquivo. A função deve retonar ponteiro para a representação condensada da matriz (representação da matriz sem os elementos com valor zero).
* Construa uma função para **escrever** a matriz condensada (todas as informações das células, com exceção do ponteiro) e a matriz completa, a partir da representação condensada, ou seja, o parâmetro de entrada deve ser o ponteiro de início da lista ligada.
* Implemente a função para **somar** as duas matrizes (A+B), recebendo como parâmetro a representação condensada de cada matriz, a resposta deve ser armazenada em uma matriz condensada, ative a função de escrita para exibir os resultados. A matriz condensada com o resultado da soma deve apresentar alocação dinâmica de memória.
* Implementar uma função para **multiplicar** as matrizes (A*B), recebendo como parâmetros o endereço inicial das listas ligadas de A e B, retornando o ponteiro para a matriz condensada C, resultante. Faça a chamada para a função que escreve a matriz (item a).
* Implementar uma função para **somar os elementos que estão abaixo da diagonal principal**, recebendo como parâmetro a matriz condensada e retornando o resultado da soma. Escreva o resultado.