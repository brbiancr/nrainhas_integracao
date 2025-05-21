#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "main.h"
#include "fitness.h"
#include "operadoresDeReproducao.h"
#include "ordenacao.h"
#include "populacao.h"
#include "print.h"
#include "selecao.h"

int main(){

    int TAMANHOPOPULACAO = 200;
    int TAMANHOTABULEIRO = 8;
    int QUANTIDADEINDIVIDUOSPORTORNEIO = 5;
    double TAXAELITISMO = 0.2;
    double TAXAMUTACAO = 0.1;
    int TIPODESELECAO = 2; // 1- Aleatoria. 2- Roleta. 3- Torneio. 4- Torneio dos dissimilares
    int TIPODECRUZAMENTO = 2; // 1- Cruzamento de um ponto. 2- Cruzamento de dois pontos
    int encontrouSolucao = 0;

/*
    // Calcular o tempo de execucao do programa
    double time_spent = 0.0;
    clock_t begin = clock();
*/
    int i;
    int *fitnessTorneio, *fitnessDaPopulacao;
    int **individuosTorneio, **pai, **tabuleiro, **proximaPopulacao, **populacaoAtual;
    FILE *arquivo;
    FILE *novosDadosArq;

    // Alocando memoria
    populacaoAtual = (int**) malloc(sizeof(int*) * TAMANHOPOPULACAO);
    proximaPopulacao = (int**) malloc(sizeof(int*) * TAMANHOPOPULACAO);
    fitnessDaPopulacao = (int*) malloc(sizeof(int) * TAMANHOPOPULACAO);
    individuosTorneio = (int**) malloc(sizeof(int*) * QUANTIDADEINDIVIDUOSPORTORNEIO);
    pai = (int**) malloc(sizeof(int*) * 2);
    fitnessTorneio = (int*) malloc(sizeof(int) * QUANTIDADEINDIVIDUOSPORTORNEIO);
    tabuleiro = (int**) malloc(sizeof(int*) * TAMANHOTABULEIRO);

    for (i=0; i<TAMANHOPOPULACAO; i++){
        populacaoAtual[i] = (int*) malloc(sizeof(int) * TAMANHOTABULEIRO);
        proximaPopulacao[i] = (int*) malloc(sizeof(int) * TAMANHOTABULEIRO);
    }

    for (i=0; i<QUANTIDADEINDIVIDUOSPORTORNEIO; i++)
        individuosTorneio[i] = (int*) malloc(sizeof(int*) * TAMANHOTABULEIRO);

    for (i=0; i<2; i++)
        pai[i] = (int*) malloc(sizeof(int) * TAMANHOTABULEIRO);

    for (i=0; i<TAMANHOTABULEIRO; i++)
        tabuleiro[i] = malloc(sizeof(int) * TAMANHOTABULEIRO);

    // Verificando alocacao de memoria
    if (populacaoAtual == NULL || proximaPopulacao == NULL || fitnessDaPopulacao == NULL || individuosTorneio == NULL || pai == NULL || fitnessTorneio == NULL || tabuleiro == NULL){
        printf ("Falha ao alocar memoria!\n");
        return 0;
    }

    inicializaPopulacao(populacaoAtual, TAMANHOPOPULACAO, TAMANHOTABULEIRO);
    fitness(tabuleiro, fitnessDaPopulacao, encontrouSolucao, populacaoAtual, TAMANHOPOPULACAO, TAMANHOTABULEIRO);
    ordenaPopulacao(populacaoAtual, fitnessDaPopulacao, TAMANHOPOPULACAO, TAMANHOTABULEIRO);
    mostraPopulacao(populacaoAtual, fitnessDaPopulacao, TAMANHOPOPULACAO, TAMANHOTABULEIRO);

    novosDadosArq = fopen("novosDadosArq.txt", "a+");
    if(novosDadosArq == NULL){
        printf("ERRO AO ABRIR ARQUIVO (novosDadosArq.txt) PARA SALVAR DADOS!\n");
        fclose(novosDadosArq);
        return 0;
    }

    fprintf(novosDadosArq, "Rodada\t");
    fprintf(novosDadosArq, "Melhor fitness\t");
    fprintf(novosDadosArq, "Pior fitness\t\n");
    for (i = 0; encontrouSolucao == 0 && i < 1000; i++){
        evoluiPopulacao(i, individuosTorneio, pai, fitnessTorneio, tabuleiro, proximaPopulacao, encontrouSolucao, populacaoAtual, fitnessDaPopulacao,
                        TIPODESELECAO, TIPODECRUZAMENTO, TAMANHOPOPULACAO, TAMANHOTABULEIRO, TAXAELITISMO,
                        QUANTIDADEINDIVIDUOSPORTORNEIO, TAXAMUTACAO);

        if(fitnessDaPopulacao[TAMANHOPOPULACAO-1] == TAMANHOTABULEIRO)
            encontrouSolucao = 1;

        printf("Rodada %d\n", i+1);

        mostraPopulacao(populacaoAtual, fitnessDaPopulacao, TAMANHOPOPULACAO, TAMANHOTABULEIRO);

        printf("Individuo com melhor fitness da rodada: ");
        for(int j = 0; j < TAMANHOTABULEIRO; j++)
            printf("%d ", populacaoAtual[TAMANHOPOPULACAO-1][j]);
        printf(" Fitness: %d \n", fitnessDaPopulacao[TAMANHOPOPULACAO-1]);

        fprintf(novosDadosArq, "%d\t", i + 1);
        fprintf(novosDadosArq, "%d\t", fitnessDaPopulacao[TAMANHOPOPULACAO-1]);
        fprintf(novosDadosArq, "%d\t\n", fitnessDaPopulacao[0]);

    }

/*
    // Calcular o tempo de execucao do programa
    clock_t end = clock();
    time_spent += (double)(end - begin) / CLOCKS_PER_SEC;
*/
    /*
    arquivo = fopen("dadosNRainhas.txt", "a+");
    if(arquivo == NULL){
        printf("ERRO AO ABRIR ARQUIVO PARA SALVAR DADOS!\n");
        fclose(arquivo);
        return 0;
    } else{
        fprintf(arquivo, "Tamanho da populacao\t%d\n", TAMANHOPOPULACAO);
        fprintf(arquivo, "Tamanho do tabuleiro\t %d\n", TAMANHOTABULEIRO);
        fprintf(arquivo, "Quantidade de individuos por torneio\t %d\n", QUANTIDADEINDIVIDUOSPORTORNEIO);
        fprintf(arquivo, "Taxa de elitismo\t %.2f\n", TAXAELITISMO);
        fprintf(arquivo, "Taxa de mutacao\t %.2f\n", TAXAMUTACAO);
        fprintf(arquivo, "Tipo de selecao\t");
        if(TIPODESELECAO == 1)
            fprintf(arquivo, "Selecao aleatoria\n");
        if(TIPODESELECAO == 2)
            fprintf(arquivo, "Selecao por roleta\n");
        if(TIPODESELECAO == 3)
            fprintf(arquivo, "Selecao por torneio\n");
        if(TIPODESELECAO == 4)
            fprintf(arquivo, "Selecao por torneio dos dissimilares\n");
        fprintf(arquivo, "Tipo de cruzamento\t ");
        if(TIPODECRUZAMENTO == 1)
            fprintf(arquivo, "Cruzamento de um ponto\n");
        if(TIPODECRUZAMENTO == 2)
            fprintf(arquivo, "Cruzamento de dois pontos\n");

        fprintf(arquivo, "Rodadas\t %d\n\n", i+1);
        fprintf(arquivo, "Tempo de execucao\t %f\n\n", time_spent);

        mostraPopulacao(populacaoAtual, fitnessDaPopulacao);

        fclose(arquivo);
    }
    */
    fclose(novosDadosArq);

    // Liberando memoria alocada
    for(i = 0; i < TAMANHOPOPULACAO; i++){
        free (*populacaoAtual);
        free (*proximaPopulacao);
    }

    for(i = 0; i < QUANTIDADEINDIVIDUOSPORTORNEIO; i++){
        free (*individuosTorneio);
    }

    for(i = 0; i < 2; i++){
        free (*pai);
    }

    for(i = 0; i < TAMANHOTABULEIRO; i++){
        free (*tabuleiro);
    }

    free (populacaoAtual);
    free (proximaPopulacao);
    free (individuosTorneio);
    free (fitnessDaPopulacao);
    free (pai);
    free (tabuleiro);
    free (fitnessTorneio);
    free (arquivo);

    return 0;
}
