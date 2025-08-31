#include "times.h"
#include "partidas.h"
#include <stdio.h>

void carregarTimes(VetTimes *vet, const char *nomeArquivo) {
    FILE *f = fopen(nomeArquivo, "r");
    if (!f) return;

    Time t;
    while (fscanf(f, "%d;%63[^;];%d;%d;%d;%d;%d;%d;%d\n",
                  &t.id, t.nome, &t.pontos, &t.vitorias, &t.empates,
                  &t.derrotas, &t.golsPro, &t.golsSofridos, &t.golsContra) == 9) {
        if (vet->qtd == vet->cap) vet->cap += 10, vet->itens = realloc(vet->itens, vet->cap * sizeof(Time));
        vet->itens[vet->qtd++] = t;
    }
    fclose(f);
}

void salvarTimes(VetTimes *vet, const char *nomeArquivo) {
    FILE *f = fopen(nomeArquivo, "w");
    if (!f) {
        printf("Erro ao salvar arquivo %s\n", nomeArquivo);
        return;
    }

    for (int i = 0; i < vet->qtd; i++) {
        Time t = vet->itens[i];
        fprintf(f, "%d;%s;%d;%d;%d;%d;%d;%d;%d\n",
                t.id, t.nome, t.pontos, t.vitorias, t.empates,
                t.derrotas, t.golsPro, t.golsSofridos, t.golsContra);
    }

    fclose(f);
}

void carregarPartidas(VetPartidas *vet, const char *nomeArquivo) {
    FILE *f = fopen(nomeArquivo, "r");
    if (!f) return;

    Partida p;
    while (fscanf(f, "%d;%d;%d;%d;%d;%d;%d;%d;%d;%d;%d\n",
                  &p.id, &p.idCasa, &p.idFora,
                  &p.golsCasa, &p.golsFora,
                  &p.golsContraCasa, &p.golsContraFora,
                  &p.data.dia, &p.data.mes, &p.data.ano,
                  &p.disputada) == 11) {
        if (vet->qtd == vet->cap) vet->cap += 10, vet->itens = realloc(vet->itens, vet->cap * sizeof(Partida));
        vet->itens[vet->qtd++] = p;
    }

    fclose(f);
}

void salvarPartidas(VetPartidas *vet, const char *nomeArquivo) {
    FILE *f = fopen(nomeArquivo, "w");
    if (!f) {
        printf("Erro ao salvar arquivo %s\n", nomeArquivo);
        return;
    }

    for (int i = 0; i < vet->qtd; i++) {
        Partida p = vet->itens[i];
        fprintf(f, "%d;%d;%d;%d;%d;%d;%d;%d;%d;%d;%d\n",
                p.id, p.idCasa, p.idFora,
                p.golsCasa, p.golsFora,
                p.golsContraCasa, p.golsContraFora,
                p.data.dia, p.data.mes, p.data.ano,
                p.disputada);
    }

    fclose(f);
}
