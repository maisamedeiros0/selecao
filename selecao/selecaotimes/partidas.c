#include "partidas.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Realocação dinâmica para expandir a capacidade
static void aumentarCapacidade(VetPartidas *vet) {
    vet->cap += 10;
    vet->itens = realloc(vet->itens, vet->cap * sizeof(Partida));
    if (!vet->itens) {
        printf("Erro ao realocar memoria!\n");
        exit(1);
    }
}

// Atualiza as estatísticas de dois times após uma partida
static void atualizarEstatisticas(Time *casa, Time *fora,
                                  int golsCasa, int golsFora,
                                  int golsContraCasa, int golsContraFora) {

    casa->golsPro     += golsCasa + golsContraFora;
    fora->golsPro     += golsFora + golsContraCasa;

    casa->golsSofridos += golsFora + golsContraCasa;
    fora->golsSofridos += golsCasa + golsContraFora;

    casa->golsContra += golsContraCasa;
    fora->golsContra += golsContraFora;

    // Define vitória, derrota ou empate baseado nos gols totais
    int totalCasa = golsCasa + golsContraFora;
    int totalFora = golsFora + golsContraCasa;

    if (totalCasa > totalFora) {
        casa->vitorias++; casa->pontos += 3;
        fora->derrotas++;
    } else if (totalCasa < totalFora) {
        fora->vitorias++; fora->pontos += 3;
        casa->derrotas++;
    } else {
        casa->empates++; casa->pontos++;
        fora->empates++; fora->pontos++;
    }
}

void inicializarPartidas(VetPartidas *vet) {
    vet->qtd = 0;
    vet->cap = 10;
    vet->itens = malloc(vet->cap * sizeof(Partida));
    if (!vet->itens) {
        printf("Erro ao alocar memoria!\n");
        exit(1);
    }
}

void liberarPartidas(VetPartidas *vet) {
    free(vet->itens);
    vet->qtd = 0;
    vet->cap = 0;
}

void inserirPartida(VetPartidas *vet, VetTimes *times) {
    if (vet->qtd == vet->cap) aumentarCapacidade(vet);

    Partida p;
    p.id = (vet->qtd == 0) ? 1 : vet->itens[vet->qtd - 1].id + 1;

    // Lê os times envolvidos
    printf("ID do time da casa: ");
    scanf("%d", &p.idCasa);
    printf("ID do time visitante: ");
    scanf("%d", &p.idFora);

    if (p.idCasa == p.idFora) {
        printf("Erro: o mesmo time nao pode jogar contra ele mesmo!\n");
        return;
    }

    printf("Data da partida (DD MM AAAA): ");
    scanf("%d %d %d", &p.data.dia, &p.data.mes, &p.data.ano);

    p.golsCasa = p.golsFora = 0;
    p.golsContraCasa = p.golsContraFora = 0;
    p.disputada = 0;

    vet->itens[vet->qtd++] = p;
    printf("Partida cadastrada com ID %d!\n", p.id);
}

void listarPartidas(VetPartidas *vet, VetTimes *times) {
    if (vet->qtd == 0) {
        printf("Nenhuma partida cadastrada.\n");
        return;
    }

    printf("\n--- Lista de Partidas ---\n");
    for (int i = 0; i < vet->qtd; i++) {
        Partida p = vet->itens[i];

        int idxCasa = buscarTimePorId(times, p.idCasa);
        int idxFora = buscarTimePorId(times, p.idFora);

        char nomeCasa[64] = "??", nomeFora[64] = "??";
        if (idxCasa != -1) strcpy(nomeCasa, times->itens[idxCasa].nome);
        if (idxFora != -1) strcpy(nomeFora, times->itens[idxFora].nome);

        // Exibe partida com ou sem resultado
        if (p.disputada) {
            printf("ID:%d | %s %d (%d GC) x %d (%d GC) %s | Data: %02d/%02d/%04d\n",
                   p.id, nomeCasa, p.golsCasa, p.golsContraCasa,
                   p.golsFora, p.golsContraFora, nomeFora,
                   p.data.dia, p.data.mes, p.data.ano);
        } else {
            printf("ID:%d | %s vs %s | Data: %02d/%02d/%04d (Agendada)\n",
                   p.id, nomeCasa, nomeFora,
                   p.data.dia, p.data.mes, p.data.ano);
        }
    }
}

int buscarPartidaPorId(VetPartidas *vet, int id) {
    for (int i = 0; i < vet->qtd; i++) {
        if (vet->itens[i].id == id) return i;
    }
    return -1;
}

void atualizarPartida(VetPartidas *vet, VetTimes *times) {
    int id;
    printf("Digite o ID da partida: ");
    scanf("%d", &id);

    int idx = buscarPartidaPorId(vet, id);
    if (idx == -1) {
        printf("Partida nao encontrada!\n");
        return;
    }

    Partida *p = &vet->itens[idx];

    printf("Deseja registrar resultado? (1=sim, 0=nao): ");
    int opc;
    scanf("%d", &opc);

    if (opc == 1) {
        if (p->disputada) {
            printf("Essa partida ja foi concluida!\n");
            return;
        }

        // Lê os gols e gols contra dos times
        printf("Gols do time da casa: ");
        scanf("%d", &p->golsCasa);
        printf("Gols contra do time da casa: ");
        scanf("%d", &p->golsContraCasa);
        printf("Gols do time visitante: ");
        scanf("%d", &p->golsFora);
        printf("Gols contra do time visitante: ");
        scanf("%d", &p->golsContraFora);

        p->disputada = 1;

        // Atualiza as estatísticas dos times
        int idxCasa = buscarTimePorId(times, p->idCasa);
        int idxFora = buscarTimePorId(times, p->idFora);

        if (idxCasa != -1 && idxFora != -1) {
            atualizarEstatisticas(&times->itens[idxCasa], &times->itens[idxFora],
                                  p->golsCasa, p->golsFora,
                                  p->golsContraCasa, p->golsContraFora);
        }

        printf("Resultado registrado!\n");
    } else {
        // Permite alterar a data da partida
        printf("Nova data (DD MM AAAA): ");
        scanf("%d %d %d", &p->data.dia, &p->data.mes, &p->data.ano);
        printf("Data atualizada!\n");
    }
}

void removerPartida(VetPartidas *vet) {
    int id;
    printf("Digite o ID da partida para remover: ");
    scanf("%d", &id);

    int idx = buscarPartidaPorId(vet, id);
    if (idx == -1) {
        printf("Partida nao encontrada!\n");
        return;
    }

    // Remove deslocando os elementos à esquerda
    for (int i = idx; i < vet->qtd - 1; i++) {
        vet->itens[i] = vet->itens[i + 1];
    }
    vet->qtd--;

    printf("Partida removida!\n");
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
        if (vet->qtd == vet->cap) aumentarCapacidade(vet);
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
