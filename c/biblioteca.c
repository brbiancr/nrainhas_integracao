#include<jni.h>
#include<stdio.h>
#include<stdlib.h>
#include"populacao.h"
#include"NQueensNative.h"


JNIEXPORT void JNICALL Java_NQueensNative_inicializaPopulacao2(JNIEnv *env, jobject obj,
                          jobjectArray populacaoAtual, jint tamanhoPopulacao, jint tamanhoTabuleiro){

    // Converter o jobjectArray para um array C
    int **populacao = (int **)malloc(tamanhoPopulacao * sizeof(int *));
    for (int i = 0; i < tamanhoPopulacao; i++) {
        jintArray row = (jintArray)(*env)->GetObjectArrayElement(env, populacaoAtual, i);
        populacao[i] = (int *)malloc(tamanhoTabuleiro * sizeof(int));

        // Criar um buffer temporário para conversão
        jint *tempArray = (jint *)malloc(tamanhoTabuleiro * sizeof(jint));

        // Obter os elementos da linha do array Java e armazenar em `tempArray`
        (*env)->GetIntArrayRegion(env, row, 0, tamanhoTabuleiro, tempArray);

        // Copiar os valores para `populacao[i]`
        for (int j = 0; j < tamanhoTabuleiro; j++) {
            populacao[i][j] = (int)tempArray[j];
        }

        // Liberar buffer temporário e referência local
        free(tempArray);
        (*env)->DeleteLocalRef(env, row);
    }

    // Chamar a função que inicializa a população
    inicializaPopulacao(populacao, tamanhoPopulacao, tamanhoTabuleiro);

    // Atualizar o array Java com os novos valores
    for (int i = 0; i < tamanhoPopulacao; i++) {
        jintArray row = (jintArray)(*env)->GetObjectArrayElement(env, populacaoAtual, i);

        // Criar um buffer temporário para conversão
        jint *tempArray = (jint *)malloc(tamanhoTabuleiro * sizeof(jint));

        // Copiar os valores da matriz C para o buffer temporário
        for (int j = 0; j < tamanhoTabuleiro; j++) {
            tempArray[j] = (jint)populacao[i][j];
        }

        // Atualizar os valores da linha no array Java
        (*env)->SetIntArrayRegion(env, row, 0, tamanhoTabuleiro, tempArray);

        // Liberar buffer temporário e referência local
        free(tempArray);
        (*env)->DeleteLocalRef(env, row);
    }

    // Liberar memória alocada para a matriz C
    for (int i = 0; i < tamanhoPopulacao; i++) {
        free(populacao[i]);
    }
    free(populacao);
}

JNIEXPORT jintArray JNICALL Java_NQueensNative_evoluiPopulacao2(JNIEnv *env, jobject obj, jint rodada,
    jobjectArray individuosTorneio, jobjectArray pai, jintArray fitnessTorneio, jobjectArray tabuleiro,
    jobjectArray proximaPopulacao, jint encontrouSolucao, jobjectArray populacaoAtual, jintArray fitnessPopulacao,
    jint TIPODESELECAO, jint TIPODECRUZAMENTO, jint TAMANHOPOPULACAO, jint TAMANHOTABULEIRO, jdouble TAXAELITISMO,
    jint QUANTIDADEINDIVIDUOSPORTORNEIO, jdouble TAXAMUTACAO){

    int **individuosTorneioC = (int **)malloc(QUANTIDADEINDIVIDUOSPORTORNEIO * sizeof(int *));
    int **paiC = (int **)malloc(2 * sizeof(int *));
    int **tabuleiroC = (int **)malloc(TAMANHOTABULEIRO * sizeof(int *));
    int **proximaPopulacaoC = (int **)malloc(TAMANHOPOPULACAO * sizeof(int *));
    int **populacaoAtualC = (int **)malloc(TAMANHOPOPULACAO * sizeof(int *));

    // Conversão de populacaoAtual e proximaPopulacao
    for (int i = 0; i < TAMANHOPOPULACAO; i++) {
        jintArray row = (jintArray)(*env)->GetObjectArrayElement(env, proximaPopulacao, i);
        proximaPopulacaoC[i] = (int *)malloc(TAMANHOTABULEIRO * sizeof(int));

        jint *tempArray = (*env)->GetIntArrayElements(env, row, NULL);
        for (int j = 0; j < TAMANHOTABULEIRO; j++) {
            proximaPopulacaoC[i][j] = tempArray[j];
        }
        (*env)->ReleaseIntArrayElements(env, row, tempArray, JNI_ABORT);
        (*env)->DeleteLocalRef(env, row);

        row = (jintArray)(*env)->GetObjectArrayElement(env, populacaoAtual, i);
        populacaoAtualC[i] = (int *)malloc(TAMANHOTABULEIRO * sizeof(int));

        tempArray = (*env)->GetIntArrayElements(env, row, NULL);
        for (int j = 0; j < TAMANHOTABULEIRO; j++) {
            populacaoAtualC[i][j] = tempArray[j];
        }
        (*env)->ReleaseIntArrayElements(env, row, tempArray, JNI_ABORT);
        (*env)->DeleteLocalRef(env, row);
    }

    // Conversão de individuosTorneio
    for (int i = 0; i < QUANTIDADEINDIVIDUOSPORTORNEIO; i++) {
        jintArray row = (jintArray)(*env)->GetObjectArrayElement(env, individuosTorneio, i);
        individuosTorneioC[i] = (int *)malloc(TAMANHOTABULEIRO * sizeof(int));

        jint *tempArray = (*env)->GetIntArrayElements(env, row, NULL);
        for (int j = 0; j < TAMANHOTABULEIRO; j++) {
            individuosTorneioC[i][j] = tempArray[j];
        }
        (*env)->ReleaseIntArrayElements(env, row, tempArray, JNI_ABORT);
        (*env)->DeleteLocalRef(env, row);
    }

    // Conversão de tabuleiro
    for (int i = 0; i < TAMANHOTABULEIRO; i++) {
        jintArray row = (jintArray)(*env)->GetObjectArrayElement(env, tabuleiro, i);
        tabuleiroC[i] = (int *)malloc(TAMANHOTABULEIRO * sizeof(int));

        jint *tempArray = (*env)->GetIntArrayElements(env, row, NULL);
        for (int j = 0; j < TAMANHOTABULEIRO; j++) {
            tabuleiroC[i][j] = tempArray[j];
        }
        (*env)->ReleaseIntArrayElements(env, row, tempArray, JNI_ABORT);
        (*env)->DeleteLocalRef(env, row);
    }

    // Conversão de pai
    for (int i = 0; i < 2; i++) {
        jintArray row = (jintArray)(*env)->GetObjectArrayElement(env, pai, i);
        paiC[i] = (int *)malloc(TAMANHOTABULEIRO * sizeof(int));

        jint *tempArray = (*env)->GetIntArrayElements(env, row, NULL);
        for (int j = 0; j < TAMANHOTABULEIRO; j++) {
            paiC[i][j] = tempArray[j];
        }
        (*env)->ReleaseIntArrayElements(env, row, tempArray, JNI_ABORT);
        (*env)->DeleteLocalRef(env, row);
    }

    // Conversão de fitnessTorneio e fitnessPopulacao
    jint *fitnessTorneioC = (*env)->GetIntArrayElements(env, fitnessTorneio, NULL);
    jint *fitnessPopulacaoC = (*env)->GetIntArrayElements(env, fitnessPopulacao, NULL);

    int *fitnessTorneioC2 = (int *)fitnessTorneioC;
    int *fitnessPopulacaoC2 = (int *)fitnessPopulacaoC;

    // Chamar a função de evolução da população
    int * melhorIndividuoC = evoluiPopulacao(rodada, individuosTorneioC, paiC, fitnessTorneioC2, tabuleiroC, proximaPopulacaoC,
                                encontrouSolucao, populacaoAtualC, fitnessPopulacaoC2, TIPODESELECAO, TIPODECRUZAMENTO,
                                TAMANHOPOPULACAO, TAMANHOTABULEIRO, TAXAELITISMO, QUANTIDADEINDIVIDUOSPORTORNEIO, TAXAMUTACAO);

    // Converter os resultados de volta para Java
    jintArray melhorIndividuo = (*env)->NewIntArray(env, TAMANHOTABULEIRO);
    (*env)->SetIntArrayRegion(env, melhorIndividuo, 0, TAMANHOTABULEIRO, (jint*)melhorIndividuoC);

    for(int i = 0; i < TAMANHOPOPULACAO; i++){
        jintArray row = (jintArray) (*env)->GetObjectArrayElement(env, populacaoAtual, i);
        (*env)->SetIntArrayRegion(env, row, 0, TAMANHOTABULEIRO, (jint *)populacaoAtualC[i]);
        (*env)->DeleteLocalRef(env, row);
    }

    (*env)->SetIntArrayRegion(env, fitnessPopulacao, 0, TAMANHOPOPULACAO, fitnessPopulacaoC);

    // Liberação de memória alocada dinamicamente
    for (int i = 0; i < TAMANHOPOPULACAO; i++) {
        free(proximaPopulacaoC[i]);
        free(populacaoAtualC[i]);
    }
    for (int i = 0; i < QUANTIDADEINDIVIDUOSPORTORNEIO; i++){
        free(individuosTorneioC[i]);
    }
    for (int i = 0; i < TAMANHOTABULEIRO; i++) {
        free(tabuleiroC[i]);
    }
    for (int i = 0; i < 2; i++) {
        free(paiC[i]);
    }

    free(individuosTorneioC);
    free(paiC);
    free(tabuleiroC);
    free(proximaPopulacaoC);
    free(populacaoAtualC);
    free(melhorIndividuoC);
    (*env)->ReleaseIntArrayElements(env, fitnessTorneio, fitnessTorneioC, 0);
    (*env)->ReleaseIntArrayElements(env, fitnessPopulacao, fitnessPopulacaoC, 0);

    return melhorIndividuo;
}
