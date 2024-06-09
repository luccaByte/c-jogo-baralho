#include <stdio.h>
#include <conio.h>
#include <stdlib.h> //malloc, free
#include <time.h> // gerar numeros aleatorios
#include <string.h>

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

Pilha* criar_pilha(int capacidade);
void clean(Pilha* p);
int empty(Pilha* p);
void push(Pilha* p, Carta c);
Carta pop(Pilha* p);
void gerarBaralho(Pilha* monte);
void embaralhar(Pilha* monte);
void simularJogo(Pilha* monte, Pilha* morto, Pilha* jogador1, Pilha* jogador2, int* numerosJ1, int* numerosJ2);


Pilha* monte;
Pilha* morto;
Pilha* jogador1;
Pilha* jogador2;


int main()
{
    srand(time(NULL));

    monte = criar_pilha(52);
    morto = criar_pilha(52);
    jogador1 = criar_pilha(52);
    jogador2 = criar_pilha(52);

    gerarBaralho(monte);
    embaralhar(monte);

    int numerosJ1[5] = { 1, 2, 3, 4, 5 }; 
    int numerosJ2[5] = { 6, 7, 8, 9, 10 };

    simularJogo(monte, morto, jogador1, jogador2, numerosJ1, numerosJ2);

    clean(monte);
    clean(morto);
    clean(jogador1);
    clean(jogador2);
}


Pilha* criar_pilha(int capacidade)
{
    Pilha* p = (Pilha*)malloc(sizeof(Pilha));
    p->cartas = (Carta*)malloc(capacidade* sizeof(Carta));
    p->tamanho = 0;
    p->capacidade = capacidade;
    return p;
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
        Carta cartaVazia = { 0, "" };
        return cartaVazia;
    }
}

void gerarBaralho(Pilha* monte) {
    const char* naipes[] = { "Copas", "Espadas", "Ouros", "Paus" };
    for (int i = 0; i < 4; i++) 
    {
        for (int j = 1; j <= 13; j++) 
        {
            Carta carta;
            carta.num = j;
            strcpy_s(carta.naipe, sizeof(carta.naipe), naipes[i]);
            push(monte, carta);
        }
    }
}


void embaralhar(Pilha* monte) 
{
    for (int i = 0; i < monte->tamanho; i++) 
    {
        int j = rand() % monte->tamanho;
        Carta temp = monte->cartas[i];
        monte->cartas[i] = monte->cartas[j];
        monte->cartas[j] = temp;
    }
}

void simularJogo(Pilha* monte, Pilha* morto, Pilha* jogador1, Pilha* jogador2, int* numerosJ1, int* numerosJ2) 
{
    int pontosJ1 = 0, pontosJ2 = 0;
    while (!empty(monte)) 
    {
        Carta carta = pop(monte);
        int achou = 0;

        for (int i = 0; i < 5; i++) {
            if (carta.num == numerosJ1[i]) 
            {
                push(jogador1, carta);
                pontosJ1++;
                achou = 1;
                break;
            }
            else if (carta.num == numerosJ2[i]) 
            {
                push(jogador2, carta);
                pontosJ2++;
                achou = 1;
                break;
            }
        }

        if (!achou) 
        {
            push(morto, carta);
        }
    }

    printf("Pontos Jogador 1: %d\n", pontosJ1);
    printf("Pontos Jogador 2: %d\n", pontosJ2);

    if (pontosJ1 > pontosJ2) 
    {
        printf("O jogador 1 venceu!\n");
    }
    else if (pontosJ2 > pontosJ1) 
    {
        printf("O jogador 2 venceu!\n");
    }
    else {
        printf("Empate!\n");
    }
}
