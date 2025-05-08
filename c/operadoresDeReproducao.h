#include "main.h"

void cruzamentoDoisPontos(int *indice, int **pai, int **proximaPopulacao, int TAMANHOTABULEIRO);
void cruzamentoUmPonto(int *indice, int **pai, int **proximaPopulacao, int TAMANHOTABULEIRO);
void mutacao(int *indice, int **proximaPopulacao, double TAXAMUTACAO, int TAMANHOTABULEIRO);
int individuoExisteNaPopulacao(int **proximaPopulacao, int *indice, int TAMANHOTABULEIRO);
