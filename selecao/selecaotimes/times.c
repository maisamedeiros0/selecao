#include "times.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Realocação dinâmica para expandir a capacidade
static void aumentarCapacidade(VetTimes *vet) {
    vet->cap += 10;
    vet->itens = realloc(vet->itens, vet->cap * sizeof(Time));
    if (!vet->itens) {
        printf("Erro ao realocar memoria!\n");
        exit(1);
    }
}

// Inicializa o vetor de times com capacidade inicial
void inicializarTimes(VetTimes *vet) {
    vet->qtd = 0;
    vet->cap = 10;
    vet->itens = malloc(vet->cap * sizeof(Time));
    if (!vet->itens) {
        printf("Erro ao alocar memoria!\n");
        exit(1);
    }
}

void liberarTimes(VetTimes *vet) {
    free(vet->itens);
    vet->qtd = 0;
    vet->cap = 0;
}

void inserirTime(VetTimes *vet) {
    if (vet->qtd == vet->cap) {
        aumentarCapacidade(vet);
    }

    Time novo;
    
    novo.id = (vet->qtd == 0) ? 1 : vet->itens[vet->qtd - 1].id + 1;

    printf("Nome do time: ");
    getchar(); // limpa o buffer
    fgets(novo.nome, sizeof(novo.nome), stdin);
    novo.nome[strcspn(novo.nome, "\n")] = '\0'; // remove o '\n'

    novo.pontos = novo.vitorias = novo.empates = novo.derrotas = 0;
    novo.golsPro = novo.golsSofridos = novo.golsContra = 0;

    vet->itens[vet->qtd++] = novo;

    printf("Time '%s' inserido com ID %d!\n", novo.nome, novo.id);
}

void listarTimes(VetTimes *vet) {
    if (vet->qtd == 0) {
        printf("Nenhum time cadastrado.\n");
        return;
    }

    printf("\n--- Lista de Times ---\n");
    for (int i = 0; i < vet->qtd; i++) {
        Time t = vet->itens[i];
        printf("ID: %d | Nome: %s | Pontos: %d | Vitorias:%d Empates:%d Derrotas:%d | Gols:%d GolsSofridos:%d GolsContra:%d\n",
               t.id, t.nome, t.pontos, t.vitorias, t.empates, t.derrotas,
               t.golsPro, t.golsSofridos, t.golsContra);
    }
}

int buscarTimePorId(VetTimes *vet, int id) {
    for (int i = 0; i < vet->qtd; i++) {
        if (vet->itens[i].id == id) return i;
    }
    return -1;
}

void atualizarTime(VetTimes *vet) {
    int id;
    printf("Digite o ID do time para atualizar: ");
    scanf("%d", &id);

    int idx = buscarTimePorId(vet, id);
    if (idx == -1) {
        printf("Time nao encontrado!\n");
        return;
    }

    printf("Novo nome do time: ");
    getchar();
    fgets(vet->itens[idx].nome, sizeof(vet->itens[idx].nome), stdin);
    vet->itens[idx].nome[strcspn(vet->itens[idx].nome, "\n")] = '\0';

    printf("Time atualizado!\n");
}

void removerTime(VetTimes *vet) {
    int id;
    printf("Digite o ID do time para remover: ");
    scanf("%d", &id);

    int idx = buscarTimePorId(vet, id);
    if (idx == -1) {
        printf("Time nao encontrado!\n");
        return;
    }

    for (int i = idx; i < vet->qtd - 1; i++) {
        vet->itens[i] = vet->itens[i + 1];
    }
    vet->qtd--;

    printf("Time removido!\n");
}

// Função auxiliar de comparação usada para ordenação da classificação
static int compararTimes(const void *a, const void *b) {
    const Time *t1 = (const Time *)a;
    const Time *t2 = (const Time *)b;

    // Critérios de desempate: pontos > vitórias > saldo > gols pró
    int saldo1 = t1->golsPro - t1->golsSofridos;
    int saldo2 = t2->golsPro - t2->golsSofridos;

    if (t1->pontos != t2->pontos) return t2->pontos - t1->pontos;
    if (t1->vitorias != t2->vitorias) return t2->vitorias - t1->vitorias;
    if (saldo1 != saldo2) return saldo2 - saldo1;
    return t2->golsPro - t1->golsPro;
}

void gerarClassificacao(VetTimes *vet) {
    if (vet->qtd == 0) {
        pri
