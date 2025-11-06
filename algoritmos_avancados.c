#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Cada sala tem um nome e dois ponteiros (esquerda e direita)
typedef struct Sala {
    char nome[50];
    struct Sala *esquerda;
    struct Sala *direita;
} Sala;

//  Função criarSala()
// Cria dinamicamente uma sala com o nome informado
Sala* criarSala(const char* nome) {
    Sala* novaSala = (Sala*) malloc(sizeof(Sala));
    if (novaSala == NULL) {
        printf("Erro ao alocar memória para a sala.\n");
        exit(1);
    }
    strcpy(novaSala->nome, nome);
    novaSala->esquerda = NULL;
    novaSala->direita = NULL;
    return novaSala;
}

//  Função conectarSalas()
// Conecta uma sala principal a duas outras (à esquerda e à direita)
void conectarSalas(Sala* principal, Sala* esquerda, Sala* direita) {
    if (principal != NULL) {
        principal->esquerda = esquerda;
        principal->direita = direita;
    }
}

//  Função explorarSalas()
// Permite o jogador navegar pela árvore binária
void explorarSalas(Sala* salaAtual) {
    char escolha;

    while (salaAtual != NULL) {
        printf("\nVocê está em: %s\n", salaAtual->nome);

        // Se a sala não tiver saídas, fim da exploração
        if (salaAtual->esquerda == NULL && salaAtual->direita == NULL) {
            printf(" Fim da exploração! Não há mais portas nesta sala.\n");
            return;
        }

        printf("Para onde deseja ir? (e = esquerda | d = direita | s = sair): ");
        scanf(" %c", &escolha);

        if (escolha == 's' || escolha == 'S') {
            printf("Você decidiu encerrar a exploração. \n");
            return;
        } 
        else if (escolha == 'e' || escolha == 'E') {
            if (salaAtual->esquerda != NULL)
                salaAtual = salaAtual->esquerda;
            else
                printf(" Não há caminho à esquerda!\n");
        } 
        else if (escolha == 'd' || escolha == 'D') {
            if (salaAtual->direita != NULL)
                salaAtual = salaAtual->direita;
            else
                printf(" Não há caminho à direita!\n");
        } 
        else {
            printf("Opção inválida! Tente novamente.\n");
        }
    }
}

// Função principal: monta o mapa e inicia a exploração
int main() {
    // Criação das salas (nós da árvore)
    Sala* hallEntrada = criarSala("Hall de Entrada");
    Sala* biblioteca = criarSala("Biblioteca");
    Sala* cozinha = criarSala("Cozinha");
    Sala* sotao = criarSala("Sótão");
    Sala* jardim = criarSala("Jardim");

    // Conectando as salas manualmente (árvore fixa)
    conectarSalas(hallEntrada, biblioteca, cozinha);
    conectarSalas(biblioteca, sotao, NULL);
    conectarSalas(cozinha, NULL, jardim);

    printf(" Bem-vindo à Mansão Misteriosa! \n");
    printf("Explore os cômodos e descubra o que há dentro...\n");

    // Inicia a exploração pelo Hall de Entrada
    explorarSalas(hallEntrada);

    // Liberação de memória (boa prática)
    free(hallEntrada);
    free(biblioteca);
    free(cozinha);
    free(sotao);
    free(jardim);

    return 0;
}
