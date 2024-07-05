// Implementação do algoritmo de escalonamento ROUND-ROBIN. 

// Bruna Leão Rosa Silveira
// Gabriel Nogueira
#include <stdio.h>
#include <stdlib.h>

typedef enum {
    PRONTO,
    EM_EXECUCAO,
    BLOQUEADO,
    CONCLUIDO
} EstadoProcesso;

typedef struct {
    int id;
    int tempo_restante;
    EstadoProcesso estado;
} Processo;

void roundRobin(Processo processos[], int num_processos, int quantum) {
    int tempo_atual = 0;
    int processos_restantes = num_processos;

    while (processos_restantes > 0) {
        for (int i = 0; i < num_processos; i++) {
            if (processos[i].estado == PRONTO) {
                processos[i].estado = EM_EXECUCAO;
                printf("Tempo %d: Processo %d em execução\n", tempo_atual, processos[i].id);

                int tempo_executado = 0;
                while (tempo_executado < quantum && processos[i].tempo_restante > 0) {
                    tempo_atual++;
                    tempo_executado++;
                    processos[i].tempo_restante--;
                    printf("Tempo %d: Processo %d - Tempo restante %d\n", tempo_atual, processos[i].id, processos[i].tempo_restante);
                }

                if (processos[i].tempo_restante == 0) {
                    processos[i].estado = CONCLUIDO;
                    printf("Tempo %d: Processo %d concluído\n", tempo_atual, processos[i].id);
                    processos_restantes--;
                } else {
                    processos[i].estado = PRONTO;
                }
            }
        }
    }
}

int main() {
    Processo processos[] = {
        {1, 6, PRONTO},
        {2, 17, PRONTO},
        {3, 5, PRONTO}
    };
    int num_processos = sizeof(processos) / sizeof(processos[0]);
    int quantum = 3; // Tamanho do quantum

    roundRobin(processos, num_processos, quantum);
    return 0;
}
