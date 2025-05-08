#include "main.h"

void atualizaPopulacao(int **proximaPopulacao, int **populacaoAtual, int TAMANHOPOPULACAO, int TAMANHOTABULEIRO);
int* evoluiPopulacao(int rodada, int **individuosTorneio, int **pai, int *fitnessTorneio,
                     int **tabuleiro, int **proximaPopulacao, int encontrouSolucao, int **populacaoAtual,
                     int *fitnessDaPopulacao, int TIPODESELECAO, int TIPODECRUZAMENTO, int TAMANHOPOPULACAO,
                     int TAMANHOTABULEIRO, double TAXAELITISMO, int QUANTIDADEINDIVIDUOSPORTORNEIO, double TAXAMUTACAO);
void inicializaPopulacao(int **populacaoAtual, int TAMANHOPOPULACAO, int TAMANHOTABULEIRO);
