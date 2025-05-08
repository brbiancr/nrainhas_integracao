public class NQueensNative {
    public native void inicializaPopulacao2(int [][]populacaoAtual, int TAMANHOPOPULACAO, int TAMANHOTABULEIRO);
    public native int[] evoluiPopulacao2(int rodada, int [][]individuosTorneio, int [][]pai, int []fitnessTorneio,
                                         int [][]tabuleiro, int [][]proximaPopulacao, int encontrouSolucao, int [][]populacaoAtual,
                                         int []fitnessDaPopulacao, int TIPODESELECAO, int TIPODECRUZAMENTO, int TAMANHOPOPULACAO,
                                         int TAMANHOTABULEIRO, double TAXAELITISMO, int QUANTIDADEINDIVIDUOSPORTORNEIO, double TAXAMUTACAO);

    static{
        System.load("C:\\Users\\biby_\\Desktop\\nrainhas_frontend\\src\\main\\c\\libNQueensNative.dll");
    }

    public static void main(String[] args) {
        int TAMANHOPOPULACAO = 10   ;
        int TAMANHOTABULEIRO = 8;
        int [][]populacaoAtual = new int[TAMANHOPOPULACAO][TAMANHOTABULEIRO];

        NQueensNative jni = new NQueensNative();

        jni.inicializaPopulacao2(populacaoAtual, TAMANHOPOPULACAO, TAMANHOTABULEIRO);

        // Exibir a população inicializada
        System.out.println("População Inicializada:");
        for (int i = 0; i < TAMANHOPOPULACAO; i++) {
            for (int j = 0; j < TAMANHOTABULEIRO; j++) {
                System.out.print(populacaoAtual[i][j] + " ");
            }
            System.out.println();
        }

        int rodada = 0;
        int encontrouSolucao = 0;
        int QUANTIDADEINDIVDUOSTORNEIO = 5;
        int TIPODESELECAO = 2;
        int TIPODECRUZAMENTO = 2;

        double TAXAELITISMO = 0.2;
        double TAXAMUTACAO = 0.1;

        int [][]individuosTorneio = new int[QUANTIDADEINDIVDUOSTORNEIO][TAMANHOTABULEIRO];
        int [][]pai = new int[2][TAMANHOTABULEIRO];
        int [][]tabuleiro = new int[TAMANHOTABULEIRO][TAMANHOTABULEIRO];
        int [][]proximaPopulacao = new int[TAMANHOPOPULACAO][TAMANHOTABULEIRO];


        int []fitnessTorneio = new int[QUANTIDADEINDIVDUOSTORNEIO];
        int []fitnessPopulacao = new int[TAMANHOPOPULACAO];
        int []melhorIndividuo = new int[TAMANHOTABULEIRO];

        for(int i = 0; encontrouSolucao == 0; i++){
            melhorIndividuo = jni.evoluiPopulacao2(rodada, individuosTorneio, pai, fitnessTorneio, tabuleiro, proximaPopulacao,
                    encontrouSolucao, populacaoAtual, fitnessPopulacao, TIPODESELECAO, TIPODECRUZAMENTO, TAMANHOPOPULACAO,
                    TAMANHOTABULEIRO, TAXAELITISMO, QUANTIDADEINDIVDUOSTORNEIO, TAXAMUTACAO);

            if(fitnessPopulacao[TAMANHOPOPULACAO-1] == TAMANHOTABULEIRO)
                encontrouSolucao = 1;

            System.out.println("Melhor Individuo da rodada " + rodada);
            for(int j = 0; j < TAMANHOTABULEIRO; j++)
                System.out.print(melhorIndividuo[j] + " ");
            System.out.println("Fitness " + fitnessPopulacao[TAMANHOPOPULACAO-1]);
        }

    }
}
