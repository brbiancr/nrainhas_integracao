#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "main.h"
#include "operadoresDeReproducao.h"

/*
    ----------------------
    cruzamentoDoisPontos()
    ----------------------

    Sao selecionados dois pontos de corte diferentes entre si de maneira aleatoria nos individuos pais.
    Recombina os dois pais gerando um novo filho.
    Adiciona o filho na proxima geracao.
    Retorna o indice do ultimo individuo da populacao.
*/
void cruzamentoDoisPontos(int *indice, int **pai, int **proximaPopulacao, int TAMANHOTABULEIRO){
    int i;
    int corte1, corte2;
    int filho[TAMANHOTABULEIRO];

    do{
        corte1 = rand() % TAMANHOTABULEIRO;
        corte2 = rand() % TAMANHOTABULEIRO;
    } while (corte1 == corte2 || (corte1 == TAMANHOTABULEIRO || corte2 == TAMANHOTABULEIRO) );

    if (corte1 > corte2){
        int temp = corte1;
        corte1 = corte2;
        corte2 = temp;
    }

    // Realiza o cruzamento
    for (i=0; i<corte1; i++)
        filho[i] = pai[0][i];

    for (i=corte1; i<corte2; i++)
        filho[i] = pai[1][i];

    for (i=corte2; i<TAMANHOTABULEIRO; i++)
        filho[i] = pai[0][i];

    // Adiciona o filho na populacao
    for (i=0; i<TAMANHOTABULEIRO; i++)
        proximaPopulacao[*indice][i] = filho[i];
}

/*
    -------------------
    cruzamentoUmPonto()
    -------------------

    Seleciona aleatoriamente um ponto de corte nos individuos pais.
    Recombina os dois pais gerando um novo filho.
    Adiciona o filho gerado na ger��o seguinte
    Retorna o indice do ultimo indiv�duo da popula��o.
*/
void cruzamentoUmPonto(int *indice, int **pai, int **proximaPopulacao, int TAMANHOTABULEIRO){
    int i;
    int corte;
    int filho[TAMANHOTABULEIRO];

    do{
        corte = rand()% TAMANHOTABULEIRO;
    } while (corte == TAMANHOTABULEIRO);

    for (i=0; i<corte; i++)
        filho[i] = pai[0][i];

    for (i=corte; i<TAMANHOTABULEIRO; i++)
        filho[i] = pai[1][i];

    // Adiciona o filho na populacao
    for (i=0; i<TAMANHOTABULEIRO; i++)
        proximaPopulacao[*indice][i] = filho[i];
}

/*
    ---------
    mutacao()
    ---------

    Define a partir da TAXAMUTACAO se haver� ou n�o muta��o.
    Caso a muta��o ocorra, define de modo aleat�rio quantos pontos ser�o mutados (1 ou 2)
                           Define de modo aleat�rio quais os pontos de muta��o.
                           Muta o individiduo filho
*/
void mutacao(int *indice, int **proximaPopulacao, double TAXAMUTACAO, int TAMANHOTABULEIRO){
    int i, j;
    int quantidadeDePontos;
    int mutarIndividuo;

    mutarIndividuo = rand()%(int)(1.0/TAXAMUTACAO);     // Define se haver� ou n�o muta��o

    if (mutarIndividuo == 0){
        quantidadeDePontos = 1 + rand()%TAMANHOTABULEIRO;

        int posicao[quantidadeDePontos];

        for (i=0; i<quantidadeDePontos; i++){
            posicao[i] = rand()%TAMANHOTABULEIRO;

            // Verificando se existem pontos de mutacao iguais
            for(j=0; j<i; j++){
                if(posicao[i] == posicao[j]){
                    posicao[i] = rand()%TAMANHOTABULEIRO;
                    j = -1;
                }
            }
        }

        for(i=0; i< quantidadeDePontos; i++){
            int novoValor;

            do {
                novoValor = rand() % TAMANHOTABULEIRO;
            } while (novoValor == proximaPopulacao[*indice][posicao[i]]);

            proximaPopulacao[*indice][posicao[i]] = novoValor;
        }
    }
}

int individuoExisteNaPopulacao(int **proximaPopulacao, int *indice, int TAMANHOTABULEIRO){
    int i, j;
    int cont;

    for(i = 0; i < (*indice); i++){
        cont = 0;

        for(j = 0; j < TAMANHOTABULEIRO; j++){
            if(proximaPopulacao[i][j] == proximaPopulacao[(*indice)][j])
                cont++;
        }
        if(cont == TAMANHOTABULEIRO){
            return 1; // true
        }
    }

    return 0; // false
}
