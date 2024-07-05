// Implementação do algoritmo de substituição de páginas wsclock.

#include <stdio.h>
#include <stdlib.h>

#define NUM_FRAMES 3    // Número de frames na memória
#define CONTADOR_MAX 10 // Máximo valor do contador

typedef struct
{
    int pageNumber;
    int referenceBit;
    int contador; // Contador de tempo desde a última referência
} PageFrame;

int main()
{
    PageFrame memory[NUM_FRAMES];
    int pageReferences[] = {0, 1, 1, 2, 3, 0, 4, 1, 2, 5, 3, 4, 6}; // Páginas referenciadas
    int numReferences = sizeof(pageReferences) / sizeof(pageReferences[0]);
    int i, j, k;

    // Inicializa a memória
    for (i = 0; i < NUM_FRAMES; i++)
    {
        memory[i].pageNumber = -1; // -1 indica que o frame está vazio
        memory[i].referenceBit = 0;
        memory[i].contador = 0;
    }

    // Inicializa o ponteiro do relógio
    k = 0;

    // Simula as referências às páginas
    for (i = 0; i < numReferences; i++)
    {
        int pageReferenced = pageReferences[i];
        int pageFound = 0;

        // Verifica se a página está na memória
        for (j = 0; j < NUM_FRAMES; j++)
        {
            if (memory[j].pageNumber == pageReferenced)
            {
                memory[j].referenceBit = 1; // Define o bit de referência
                pageFound = 1;
                printf("Página %d já está referenciada na memória \n", pageReferenced);
                break;
            }
        }

        // Se a página não estiver na memória, substitui uma página
        if (!pageFound)
        {
            // Procura por uma página com bit de referência zero ou com menor contador
            while (1)
            {
                if (memory[k].referenceBit == 0 || memory[k].contador >= CONTADOR_MAX)
                {
                    // Substitui a página
                    printf("Substituiu página %d\n", memory[k].pageNumber);
                    memory[k].pageNumber = pageReferenced;
                    memory[k].referenceBit = 1;
                    memory[k].contador = 0; // Zera o contador
                    break;
                }
                else
                {
                    // Zera o bit de referência para a próxima verificação
                    memory[k].referenceBit = 0;
                }

                memory[k].contador++;     // Incrementa o contador
                k = (k + 1) % NUM_FRAMES; // Avança para o próximo frame
            }
        }

        // Imprime o estado da memória após cada referência
        printf("Após referência %d: ", pageReferenced);
        for (j = 0; j < NUM_FRAMES; j++)
        {
            if (memory[j].pageNumber == -1)
                printf("Página: [ - ] | ");
            else
                printf(" Página: %d; R = %d; Contador: %d | ", memory[j].pageNumber, memory[j].referenceBit, memory[j].contador);
        }
        printf("\n");
    }

    return 0;
}
