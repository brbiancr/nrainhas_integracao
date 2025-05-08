#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "main.h"
#include "selecao.h"
#include "ordenacao.h"

/*
    ----------
    elitismo()
    ----------
    Copia para proximaPopulacao uma porcentagem TAXAELITISMO dos individuos com maior fitness da populacaoAtual.
    Retorna a posicao do ultimo individuo da populacao
*/
void elitismo(int* indice, int **proximaPopulacao, int **populacaoAtual, int TAMANHOPOPULACAO, int TAMANHOTABULEIRO, double TAXAELITISMO){

    int i, j;
    for (i=0; i<(TAMANHOPOPULACAO*(TAXAELITISMO*100))/100; i++){
        for (j=0; j<TAMANHOTABULEIRO; j++)
            proximaPopulacao[i][j] = populacaoAtual[TAMANHOPOPULACAO-(i+1)][j];
    }

    *indice = i;
}

/*
    ------------------
    selecaoAleatoria()
    ------------------
    Seleciona de forma aleat�ria os dois individuos pais.
    O processo ocorre at� que ambos os pais sejam diferentes entre si.
*/
void selecaoAleatoria(int **pai, int **populacaoAtual, int TAMANHOPOPULACAO, int TAMANHOTABULEIRO){
    int i, j;
    int individuo;
    int cont = 0;

    for (i=0; i<2; i++){

        individuo = (rand()%TAMANHOPOPULACAO);

        for (j=0; j<TAMANHOTABULEIRO; j++)
            pai[i][j] = populacaoAtual[individuo][j];

        if (i>0){
            for (j=0; j<TAMANHOTABULEIRO; j++){
                if (pai[0][j] == pai[1][j])
                    cont++;
            }
        }

        if (cont == TAMANHOTABULEIRO)
            i--;
    }
}

/*
    ---------------
    selecaoRoleta()
    ---------------
    Representa proporcionalmente os individuos na roleta de acordo com seu fitness.
    Gira a roleta e seleciona um pai.
    O precesso se repete at� que exista dois pais diferentes entre si.
*/
void selecaoRoleta(int **pai, int *fitnessDaPopulacao, int **populacaoAtual, int TAMANHOPOPULACAO, int TAMANHOTABULEIRO){
    int i, j;
    int k = 0;
    int somaFitness = 0;
    int numeroSorteado, fitnessAcumulado, cont;

    // Soma os fitness da populacao
    for (i=0; i<TAMANHOPOPULACAO; i++)
        somaFitness += fitnessDaPopulacao[i];

    for(k=0; k<2; k++){
        cont = 0;
        // Roda a roleta (sorteia um numero aleatorio)
        numeroSorteado = rand() % somaFitness;

        // Seleciona um pai
        fitnessAcumulado = 0;
        for (i=0; (i<TAMANHOPOPULACAO) && (fitnessAcumulado <= numeroSorteado); i++){
            fitnessAcumulado += fitnessDaPopulacao[i];
            if (fitnessAcumulado > numeroSorteado){
                for (j=0; j<TAMANHOTABULEIRO; j++)
                    pai[k][j] = populacaoAtual[i][j];
            }
        }

        // Verifica se os pais s�o iguais
        if (k>0){
            for (i=0; i<TAMANHOTABULEIRO; i++){
                if (pai[0][i] == pai[1][i])
                    cont++;
            }
        }

        if (cont == TAMANHOTABULEIRO)
            k--;
    }

    /*
    printf("Pai 1 :");
    for(int i = 0; i < TAMANHOTABULEIRO; i++)
        printf("%d ", pai[0][i]);

    printf("\nPai 2 :");
        for(int i = 0; i < TAMANHOTABULEIRO; i++)
            printf("%d ", pai[1][i]);
    */
}

/*
    ----------------
    selecaoTorneio()
    ----------------
    S�o selecionados N individuos distintos entre si para participar do torneio.
    O individuo com maior aptid�o entre os selecionados � escolhido para ser um pai.
    O precesso se repete at� que exista dois pais diferentes entre si.
*/
void selecaoTorneio(int **individuosTorneio, int **pai, int *fitnessTorneio, int **populacaoAtual, int *fitnessDaPopulacao,
                    int QUANTIDADEINDIVIDUOSPORTORNEIO, int TAMANHOPOPULACAO, int TAMANHOTABULEIRO){
    int i, j, k;
    int individuo[QUANTIDADEINDIVIDUOSPORTORNEIO];
    int cont = 0;

    //srand(time(NULL));

    for (k=0; k<2; k++){
        // Seleciona individuos para o torneio
        for (i=0; i < QUANTIDADEINDIVIDUOSPORTORNEIO; i++){
            individuo[i] = rand() % TAMANHOPOPULACAO;

            // Verifica se existem individuos iguais no torneio
            for(j=0; j<i; j++){
                if(individuo[i] == individuo[j]){
                    individuo[i] = rand() % TAMANHOPOPULACAO;
                    j = -1;
                }
            }

            fitnessTorneio[i] = fitnessDaPopulacao[individuo[i]];
            for (j=0; j<TAMANHOTABULEIRO; j++)
                individuosTorneio[i][j] = populacaoAtual[individuo[i]][j];
        }

        ordenaTorneio(individuosTorneio, fitnessTorneio, TAMANHOTABULEIRO, QUANTIDADEINDIVIDUOSPORTORNEIO);

        // Seleciona o individuo com maior fitness para ser o pai
        for (i=0; i<TAMANHOTABULEIRO; i++)
            pai[k][i] = individuosTorneio[QUANTIDADEINDIVIDUOSPORTORNEIO-1][i];
    }

    // Verifica se os pais sao iguais
    if (k>0){
        for (i=0; i<TAMANHOTABULEIRO; i++){
            if (pai[0][i] == pai[1][i])
                cont++;
        }
    }

    if (cont == TAMANHOTABULEIRO){
        for (i=0; i<TAMANHOTABULEIRO; i++)
            pai[1][i] = individuosTorneio[QUANTIDADEINDIVIDUOSPORTORNEIO-2][i];
    }
}

/*
    ----------------
    selecaoTorneioDosDissimilares()
    ----------------
    São selecionados N individuos distintos entre si para participar do torneio.
    O individuo com maior aptidão é escolhido para ser o pai 1.
    São selecionados N individuos distintos entre si para participar do torneio.
    O individuo com menor aptidão é escolhido para ser o pai 2.
*/
void selecaoTorneioDosDissimilares(int **individuosTorneio, int **pai, int *fitnessTorneio, int **populacaoAtual,
                                    int *fitnessDaPopulacao, int QUANTIDADEINDIVIDUOSPORTORNEIO, int TAMANHOPOPULACAO,
                                    int TAMANHOTABULEIRO){
    int i, j;
    int individuo[QUANTIDADEINDIVIDUOSPORTORNEIO];
    int cont = 0;

    //srand(time(NULL));

    // Seleciona individuos para o torneio
    for (i=0; i < QUANTIDADEINDIVIDUOSPORTORNEIO; i++){
        individuo[i] = rand()%TAMANHOPOPULACAO;

        // Verifica se existem individuos iguais no torneio
        for(j=0; j<i; j++){
            if(individuo[i] == individuo[j]){
                individuo[i] = rand()%TAMANHOPOPULACAO;
                j = -1;
            }
        }

        fitnessTorneio[i] = fitnessDaPopulacao[individuo[i]];
        for (j=0; j<TAMANHOTABULEIRO; j++)
            individuosTorneio[i][j] = populacaoAtual[individuo[i]][j];
    }

    ordenaTorneio(individuosTorneio, fitnessTorneio, TAMANHOTABULEIRO, QUANTIDADEINDIVIDUOSPORTORNEIO);

    // Seleciona o individuo com maior fitness para ser o pai 1
    for (i=0; i<TAMANHOTABULEIRO; i++)
        pai[0][i] = individuosTorneio[QUANTIDADEINDIVIDUOSPORTORNEIO-1][i];

    // Seleciona individuos para o torneio
    for (i=0; i < QUANTIDADEINDIVIDUOSPORTORNEIO; i++){
        individuo[i] = rand() % TAMANHOPOPULACAO;

        // Verifica se existem individuos iguais no torneio
        for(j=0; j<i; j++){
            if(individuo[i] == individuo[j]){
                individuo[i] = rand() % TAMANHOPOPULACAO;
                j = -1;
            }
        }

        fitnessTorneio[i] = fitnessDaPopulacao[individuo[i]];
        for (j=0; j<TAMANHOTABULEIRO; j++)
            individuosTorneio[i][j] = populacaoAtual[individuo[i]][j];
    }

    ordenaTorneio(individuosTorneio, fitnessTorneio, TAMANHOTABULEIRO, QUANTIDADEINDIVIDUOSPORTORNEIO);

    // Seleciona o individuo com menor fitness para ser o pai 2
    for (i=0; i<TAMANHOTABULEIRO; i++)
        pai[1][i] = individuosTorneio[0][i];

    // Verifica se os pais sao iguais
    for (i=0; i<TAMANHOTABULEIRO; i++){
        if (pai[0][i] == pai[1][i])
            cont++;
    }

    if (cont == TAMANHOTABULEIRO){
        for (i=0; i<TAMANHOTABULEIRO; i++)
            pai[1][i] = individuosTorneio[1][i];

    }
}
