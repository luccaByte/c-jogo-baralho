#include <stdio.h>
#include <conio.h>
#include <stdlib.h> //malloc, free
#include <time.h> // gerar numeros aleatorios

typedef struct 
{
    int num; 
    char naipe[10];
} Carta;

typedef struct
{
    Carta* cartas;
    int tamanho;
    int capacidade;
} Pilha;

Pilha* criar_pilha(int capacidade)
{
    Pilha* p = (Pilha*)malloc(sizeof(Pilha));
    p->cartas = (Carta*)malloc(capacidade * sizeof(Carta));
    p->tamanho = 0;
    p->capacidade = capacidade;
    return p;
}

void clean(Pilha* p);
int empty(Pilha* p);
void push(Pilha* p, Carta c);
Carta pop(Pilha* p);

int main()
{

}

void clean(Pilha* p) 
{
    free(p->cartas);
    free(p);
}

int empty(Pilha* p)
{
    return p->tamanho == 0;
}

void push(Pilha* p, Carta c)
{
    if (p->tamanho < p->capacidade)
    {
        p->cartas[p->tamanho] = c;
        p->tamanho++;
    }
    else
    {
        printf("Erro: a pilha está cheia!\n");
    }
}

Carta pop(Pilha* p)
{
    if (!empty(p))
    {
        p->tamanho--;
        return p->cartas[p->tamanho];
    }
    else
    {
        printf("Erro: A pilha está vazia!\n");
    }
}