#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "contaBancaria.h"

// Cria uma nova conta
ContaBancaria *criar_conta(int numero, int agenciaNumero, const char *nomeCliente, const char *dataAbertura, float saldo, const char *status) {
    ContaBancaria *novaConta = (ContaBancaria *)malloc(sizeof(ContaBancaria));
    if (novaConta == NULL) {
        printf("Erro ao alocar memória para nova conta.\n");
        return NULL;
    }
    novaConta->numero = numero;
    novaConta->agenciaNumero = agenciaNumero;
    strcpy(novaConta->nomeCliente, nomeCliente);
    strcpy(novaConta->dataAbertura, dataAbertura);
    novaConta->saldo = saldo;
    strcpy(novaConta->status, status);
    novaConta->esquerda = NULL;
    novaConta->direita = NULL;
    return novaConta;
}

// Insere uma conta na árvore
void inserir_conta(ContaBancaria **raiz, ContaBancaria *novaConta) {
    if (*raiz == NULL) {
        *raiz = novaConta;
    } else if (novaConta->numero < (*raiz)->numero) {
        inserir_conta(&(*raiz)->esquerda, novaConta);
    } else if (novaConta->numero > (*raiz)->numero) {
        inserir_conta(&(*raiz)->direita, novaConta);
    } else {
        printf("A conta com número %d já existe.\n", novaConta->numero);
        free(novaConta);
    }
}

// Lista as contas de uma agência
void listar_contas_agencia(ContaBancaria *raiz, int agenciaNumero) {
    if (raiz != NULL) {
        listar_contas_agencia(raiz->esquerda, agenciaNumero);
        if (raiz->agenciaNumero == agenciaNumero) {
            printf("Cliente:%s\tData:%s\tSaldo:%.2f\tStatus:%s\tNumero:%d\n", 
                   raiz->nomeCliente, raiz->dataAbertura, raiz->saldo, raiz->status, raiz->numero);
        }
        listar_contas_agencia(raiz->direita, agenciaNumero);
    }
}

// Salva as contas no arquivo
void salvar_contas(ContaBancaria *raiz, FILE *file) {
    if (raiz) {
        fprintf(file, "\tConta %d\tCliente:%s\tData:%s\tSaldo:%.2f\tStatus:%s\n", 
                raiz->numero, raiz->nomeCliente, raiz->dataAbertura, raiz->saldo, raiz->status);
        
        // Chamada recursiva para o próximo nó na árvore
        salvar_contas(raiz->esquerda, file);
        salvar_contas(raiz->direita, file);
    }
}

// Lê as contas do arquivo
ContaBancaria *ler_contas(FILE *file) {
    ContaBancaria *raiz = NULL;
    char linha[256];
    
    while (fgets(linha, sizeof(linha), file)) {
        ContaBancaria *novaConta = (ContaBancaria *)malloc(sizeof(ContaBancaria));
        if (novaConta == NULL) {
            printf("Erro ao alocar memória para nova conta.\n");
            continue;
        }
        
        // Ajuste o formato para ler o número da agência também
        if (sscanf(linha, "Cliente:%[^\t]\tData:%[^\t]\tSaldo:%f\tStatus:%[^\t]\tNumero:%d\tAgencia:%d",
                   novaConta->nomeCliente, novaConta->dataAbertura, &novaConta->saldo, novaConta->status, 
                   &novaConta->numero, &novaConta->agenciaNumero) == 6) {
            novaConta->esquerda = NULL;
            novaConta->direita = NULL;
            inserir_conta(&raiz, novaConta);
        } else {
            printf("Erro ao ler linha: %s\n", linha);
            free(novaConta);
        }
    }

    return raiz;
}

// Libera a memória alocada para as contas
void liberar_contas(ContaBancaria *raiz) {
    if (raiz != NULL) {
        liberar_contas(raiz->esquerda);
        liberar_contas(raiz->direita);
        free(raiz);
    }
}
