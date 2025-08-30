#ifndef PARTIDAS_H
#define PARTIDAS_H

#include "times.h" 

typedef struct {
    int dia, mes, ano;  
} Data;

typedef struct {
    int id;                
    int idCasa;            
    int idFora;           
    int golsCasa;           
    int golsFora;           
    int golsContraCasa;     
    int golsContraFora;     
    Data data;
    int disputada;  
} Partida;

typedef struct {
    Partida *itens;
    int qtd, cap;
} VetPartidas;

void inicializarPartidas(VetPartidas *vet);
void liberarPartidas(VetPartidas *vet);
void inserirPartida(VetPartidas *vet, VetTimes *times);
void listarPartidas(VetPartidas *vet, VetTimes *times);
int buscarPartidaPorId(VetPartidas *vet, int id);
void atualizarPartida(VetPartidas *vet, VetTimes *times);
void removerPartida(VetPartidas *vet);
void carregarPartidas(VetPartidas *vet, const char *nomeArquivo);
void salvarPartidas(VetPartidas *vet, const char *nomeArquivo);

#endif
