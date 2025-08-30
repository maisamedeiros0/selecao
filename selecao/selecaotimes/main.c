#include <stdio.h>
#include <stdlib.h>
#include "times.h"
#include "partidas.h"
#include "arquivos.h"

int main() {
    VetTimes times;
    VetPartidas partidas;

    inicializarTimes(&times);
    inicializarPartidas(&partidas);

    carregarTimes(&times, "times.txt");
    carregarPartidas(&partidas, "partidas.txt");

    int opcao;
    do {
        printf("\n--- Campeonato Esportivo ---\n");
        printf("\n");
        printf("1. Inserir Time\n");
        printf("2. Listar Times\n");
        printf("3. Atualizar Time\n");
        printf("4. Remover Time\n");
        printf("\n");
        printf("5. Inserir Partida\n");
        printf("6. Listar Partidas\n");
        printf("7. Atualizar Partida\n");
        printf("8. Remover Partida\n");
        printf("\n");
        printf("9. Gerar Classificação\n");
        printf("0. Sair\n");
        printf("\n");
        printf("----------------------------\n");
        printf("\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                inserirTime(&times);
                break;
            case 2:
                listarTimes(&times);
                break;
            case 3:
                atualizarTime(&times);
                break;
            case 4:
                removerTime(&times);
                break;
            case 5:
                inserirPartida(&partidas, &times);
                break;
            case 6:
                listarPartidas(&partidas, &times);
                break;
            case 7:
                atualizarPartida(&partidas, &times);
                break;
            case 8:
                removerPartida(&partidas);
                break;
            case 9:
                gerarClassificacao(&times);
                break;
            case 0:
                salvarTimes(&times, "times.txt");
                salvarPartidas(&partidas, "partidas.txt");
                printf("\nDados salvos. Encerrando...\n");
                break;
            default:
                printf("\nOpcao invalida!\n");
        }
    } while (opcao != 0);

    liberarTimes(&times);
    liberarPartidas(&partidas);

    return 0;
}


