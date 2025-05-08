#include "main.h"

void elitismo(int* indice, int **proximaPopulacao, int **populacaoAtual, int TAMANHOPOPULACAO, int TAMANHOTABULEIRO, double TAXAELITISMO);
void selecaoAleatoria(int **pai, int **populacaoAtual, int TAMANHOPOPULACAO, int TAMANHOTABULEIRO);
void selecaoRoleta(int **pai, int *fitnessDaPopulacao, int **populacaoAtual, int TAMANHOPOPULACAO, int TAMANHOTABULEIRO);
void selecaoTorneio(int **individuosTorneio, int **pai, int *fitnessTorneio, int **populacaoAtual, int *fitnessDaPopulacao, int QUANTIDADEINDIVIDUOSPORTORNEIO, int TAMANHOPOPULACAO, int TAMANHOTABULEIRO);
void selecaoTorneioDosDissimilares(int **individuosTorneio, int **pai, int *fitnessTorneio, int **populacaoAtual, int *fitnessDaPopulacao, int QUANTIDADEINDIVIDUOSPORTORNEIO, int TAMANHOPOPULACAO, int TAMANHOTABULEIRO);