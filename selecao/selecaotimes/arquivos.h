#ifndef ARQUIVOS_H
#define ARQUIVOS_H

#include "times.h"
#include "partidas.h"

void carregarTimes(VetTimes *vet, const char *nomeArquivo);
void salvarTimes(VetTimes *vet, const char *nomeArquivo);
void carregarPartidas(VetPartidas *vet, const char *nomeArquivo);
void salvarPartidas(VetPartidas *vet, const char *nomeArquivo);

#endif
