#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct no
{
    char *cdg;
    int acertos;
} No;

void heapifymax(No *V, int T, int i)
{
    No ajuda;
    int P = i, E = 2 * i + 1, D = 2 * i;
    if (E < T && V[E].acertos > V[P].acertos)
        P = E;
    if (D < T && V[D].acertos > V[P].acertos)
        P = D;
    if (P != i)
    {
        ajuda = V[i];
        V[i] = V[P];
        V[P] = ajuda;
        heapifymax(V, T, P);
    }
}

void heapifymin(No *V, int T, int i)
{
    No ajuda;
    int P = i, E = 2 * i + 1, D = 2 * i;
    if (E < T && V[E].acertos < V[P].acertos)
        P = E;
    if (D < T && V[D].acertos < V[P].acertos)
        P = D;
    if (P != i)
    {
        ajuda = V[i];
        V[i] = V[P];
        V[P] = ajuda;
        heapifymin(V, T, P);
    }
}

int main(int argc, char *argv[])
{
    char *chave = (char *)malloc(33 * sizeof(char));
    int premio, range, nmr;
    int *sorteado = (int *)malloc(10 * sizeof(int));
    int *jogado = (int *)malloc(15 * sizeof(int));

    FILE *input = fopen(argv[1], "r");
    FILE *output = fopen(argv[2], "w");

    fscanf(input, "%i", &premio);
    fscanf(input, "%i", &range);

    No *heapmax = (No *)malloc(range * sizeof(No));
    No *heapmin = (No *)malloc(range * sizeof(No));

    for (int i = 0; i < 10; i++)
    {
        fscanf(input, "%i", &sorteado[i]);
    }

    for (int i = 0; i < range; i++)
    {
        heapmax[i].acertos = 0;
        heapmin[i].acertos = 0;
        heapmax[i].cdg = (char *)malloc(33 * sizeof(char));
        heapmin[i].cdg = (char *)malloc(33 * sizeof(char));
        fscanf(input, "%s", heapmax[i].cdg);
        strcpy(heapmin[i].cdg, heapmax[i].cdg);
        for (int x = 0; x < 15; x++)
        {
            fscanf(input, "%i", &nmr);
            for (int y = 0; y < 10; y++)
            {
                if (nmr == sorteado[y])
                {
                    heapmax[i].acertos++;
                    heapmin[i].acertos++;
                    break;
                }
            }
        }
    }

    heapifymax(heapmax, range, 0);
    int vencedores = 1;
    int nmracerto = heapmax[0].acertos;
    for (int i = 1; i < range; i++)
    {
        if(heapmax[i].acertos == nmracerto)
        {
            vencedores++;
        }
    }
    fprintf(output, "[%i:%i:%i]\n", vencedores, nmracerto, (premio/2)/vencedores);
    for(int i = 0; i < vencedores; i++)
    {
        fprintf(output, "%s\n", heapmax[i].cdg);
    }
    heapifymin(heapmin, range, 0);
    vencedores = 1;
    nmracerto = heapmin[0].acertos;
    for (int i = 1; i < range; i++)
    {
        if(heapmin[i].acertos == nmracerto)
        {
            vencedores++;
        }
    }
    fprintf(output, "[%i:%i:%i]\n", vencedores, nmracerto, (premio/2)/vencedores);
    for(int i = 0; i < vencedores; i++)
    {
        fprintf(output, "%s\n", heapmin[i].cdg);
    }
    
    fclose(input);
    fclose(output);

    return 0;
}