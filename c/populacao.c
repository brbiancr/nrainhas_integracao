#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "main.h"
#include "populacao.h"
#include "fitness.h"
#include "ordenacao.h"
#include "operadoresDeReproducao.h"
#include "selecao.h"
#include "print.h"

/*
    -------------------
    atualizaPopulacao()
    -------------------

*/
void atualizaPopulacao(int **proximaPopulacao, int **populacaoAtual, int TAMANHOPOPULACAO, int TAMANHOTABULEIRO){
    int i, j;

    for (i=0; i<TAMANHOPOPULACAO; i++){
        for (j=0; j<TAMANHOTABULEIRO; j++)
            populacaoAtual[i][j] = proximaPopulacao[i][j];
    }
}

/*
    -----------------
    evoluiPopulacao()
    -----------------
    Evolui a populacao ate que a quantidade de evolucoes sejam alcancadas ou ate que uma solucao otima seja encontrada
*/
int* evoluiPopulacao(int rodada, int **individuosTorneio, int **pai, int *fitnessTorneio,
                         int **tabuleiro, int **proximaPopulacao, int encontrouSolucao, int **populacaoAtual,
                         int *fitnessDaPopulacao, int TIPODESELECAO, int TIPODECRUZAMENTO, int TAMANHOPOPULACAO,
                         int TAMANHOTABULEIRO, double TAXAELITISMO, int QUANTIDADEINDIVIDUOSPORTORNEIO, double TAXAMUTACAO){
    int indiceInicio = 0;
    int *indice = &indiceInicio;

    encontrouSolucao = fitness(tabuleiro, fitnessDaPopulacao, encontrouSolucao, populacaoAtual, TAMANHOPOPULACAO, TAMANHOTABULEIRO);
    ordenaPopulacao(populacaoAtual, fitnessDaPopulacao, TAMANHOPOPULACAO, TAMANHOTABULEIRO);
    elitismo(indice, proximaPopulacao, populacaoAtual, TAMANHOPOPULACAO, TAMANHOTABULEIRO, TAXAELITISMO);

    do{
        do{
            switch (TIPODESELECAO){
                case 1: selecaoAleatoria(pai, populacaoAtual, TAMANHOTABULEIRO, TAMANHOTABULEIRO);
                        break;
                case 2: selecaoRoleta(pai, fitnessDaPopulacao, populacaoAtual, TAMANHOPOPULACAO, TAMANHOTABULEIRO);
                        break;
                case 3: selecaoTorneio(individuosTorneio, pai, fitnessTorneio, populacaoAtual, fitnessDaPopulacao, QUANTIDADEINDIVIDUOSPORTORNEIO, TAMANHOPOPULACAO, TAMANHOTABULEIRO);
                        break;
                case 4: selecaoTorneioDosDissimilares(individuosTorneio, pai, fitnessTorneio, populacaoAtual, fitnessDaPopulacao, QUANTIDADEINDIVIDUOSPORTORNEIO, TAMANHOPOPULACAO, TAMANHOTABULEIRO);
                        break;
            }

            switch (TIPODECRUZAMENTO){
                case 1: cruzamentoUmPonto(indice, pai, proximaPopulacao, TAMANHOTABULEIRO);
                        break;
                case 2: cruzamentoDoisPontos(indice, pai, proximaPopulacao, TAMANHOTABULEIRO);
                        break;
            }

            mutacao(indice, proximaPopulacao, TAXAMUTACAO, TAMANHOTABULEIRO);

        }while(individuoExisteNaPopulacao(proximaPopulacao, indice, TAMANHOTABULEIRO));

        *indice = (*indice)+1;
    } while (*indice < TAMANHOPOPULACAO);

    atualizaPopulacao(proximaPopulacao, populacaoAtual, TAMANHOPOPULACAO, TAMANHOTABULEIRO);
    encontrouSolucao = fitness(tabuleiro, fitnessDaPopulacao, encontrouSolucao, populacaoAtual, TAMANHOPOPULACAO, TAMANHOTABULEIRO);
    ordenaPopulacao(populacaoAtual, fitnessDaPopulacao, TAMANHOPOPULACAO, TAMANHOTABULEIRO);

    int *melhorIndividuo = (int*) malloc(sizeof(int*) * TAMANHOTABULEIRO);

    for(int i = 0; i < TAMANHOTABULEIRO; i++)
        melhorIndividuo[i] = populacaoAtual[TAMANHOPOPULACAO-1][i];

    mostraPopulacao(populacaoAtual, fitnessDaPopulacao, TAMANHOPOPULACAO, TAMANHOTABULEIRO);

    return melhorIndividuo;
}

/*
    ---------------------
    inicializaPopulacao()
    ---------------------
    Inicializa de forma aleatoria a populacao inicial.
    A populacao inicial nao deve ter individuos iguais.
*/
void inicializaPopulacao(int **populacaoAtual, int TAMANHOPOPULACAO, int TAMANHOTABULEIRO){
    int i, j, k, l;
    int cont;

    srand(time(NULL));

    for (i = 0; i < TAMANHOPOPULACAO; i++){
        do{
            for (j=0; j<TAMANHOTABULEIRO; j++){
                populacaoAtual[i][j] = rand()%TAMANHOTABULEIRO;
                printf("%d ", populacaoAtual[i][j]);
            }

            printf("\n");
        }while(i > 0 && individuoExisteNaPopulacao(populacaoAtual, &i, TAMANHOTABULEIRO));
    }
}