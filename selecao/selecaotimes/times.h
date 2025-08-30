#ifndef TIMES_H
#define TIMES_H

typedef struct {
    int id;                
    char nome[64];
    int pontos;
    int vitorias;
    int empates;
    int derrotas;
    int golsPro;
    int golsContra;
} Time;

typedef struct {
    Time *itens;
    int qtd, cap;
} VetTimes;

void inicializarTimes(VetTimes *vet);
void liberarTimes(VetTimes *vet);
void inserirTime(VetTimes *vet);
void listarTimes(VetTimes *vet);
int buscarTimePorId(VetTimes *vet, int id);
void atualizarTime(VetTimes *vet);
void removerTime(VetTimes *vet);
void gerarClassificacao(VetTimes *vet);
void carregarTimes(VetTimes *vet, const char *nomeArquivo);
void salvarTimes(VetTimes *vet, const char *nomeArquivo);

#endif
