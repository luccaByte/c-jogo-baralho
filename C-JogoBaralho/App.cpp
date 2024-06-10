#include <stdio.h>
#include <stdlib.h> // malloc, free
#include <time.h>   // gerar números aleatórios
#include <string.h>
#include <locale.h>

#define TAMANHO_MAX 52
#define _CRT_SECURE_NO_WARNINGS


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
void jogar(Pilha* monte, Pilha* jogador1, Pilha* jogador2);

int main() 
{
    setlocale(LC_ALL, "Portuguese");

    Pilha* monte = criar_pilha(TAMANHO_MAX);
    Pilha* jogador1 = criar_pilha(TAMANHO_MAX);
    Pilha* jogador2 = criar_pilha(TAMANHO_MAX);

    gerarBaralho(monte);
    srand((unsigned int)time(NULL));

    embaralhar(monte);
    jogar(monte, jogador1, jogador2);

    clean(monte);
    clean(jogador1);
    clean(jogador2);

    return 0;
}

Pilha* criar_pilha(int capacidade) 
{
    Pilha* p = (Pilha*)malloc(sizeof(Pilha));
    p->cartas = (Carta*)malloc(capacidade * sizeof(Carta));
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
        exit(1);
    }
}

void gerarBaralho(Pilha* monte) 
{
    int valores[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13 };
    char* naipes[] = { "Copas", "Espadas", "Ouros", "Paus" };
    for (int i = 0; i < 13; i++) 
    {
        for (int j = 0; j < 4; j++) 
        {
            Carta c;
            c.num = valores[i];
            strcpy(c.naipe, naipes[j]);
            push(monte, c);
        }
    }
}

void embaralhar(Pilha* monte) 
{
    int i, j;
    Carta temp;
    for (i = 0; i < monte->tamanho; i++) 
    {
        j = rand() % monte->tamanho;
        temp = monte->cartas[i];
        monte->cartas[i] = monte->cartas[j];
        monte->cartas[j] = temp;
    }
}

void jogar(Pilha* monte, Pilha* jogador1, Pilha* jogador2) 
{
    int escolhas1[5], escolhas2[5];
    printf("  ========== JOGO DE CARTAS ==========  \n");
    printf("Jogador 1, escolha 5 cartas (1 a 13):\n");
    for (int i = 0; i < 5; i++) 
    {
        scanf_s("%d", &escolhas1[i]);
    }
    printf("Jogador 2, escolha 5 cartas (1 a 13):\n");
    for (int i = 0; i < 5; i++) 
    {
        scanf_s("%d", &escolhas2[i]);
    }

    int pontos1 = 0, pontos2 = 0;

    while (!empty(monte)) 
    {
        Carta c = pop(monte);
        printf("  ========== Carta retirada: %d de %s ==========  \n", c.num, c.naipe);

        for (int i = 0; i < 5; i++) 
        {
            if (c.num == escolhas1[i]) 
            {
                push(jogador1, c);
                pontos1++;
                printf("  ========== Jogador 1 ganhou a carta! ==========  \n");
                break;
            }
            else if (c.num == escolhas2[i]) 
            {
                push(jogador2, c);
                pontos2++;
                printf("  ========== Jogador 2 ganhou a carta! ==========  \n");
                break;
            }
        }
        printf("* Pontos atuais:  \n");
        printf("- Jogador 1: %d \n", pontos1);
        printf("- Jogador 2: %d \n", pontos2);
    }
    printf("Fim do jogo!\n");
    printf("* Pontos finais:\n");
    printf("- Jogador 1: %d   \n", pontos1);
    printf("- Jogador 2: %d   \n", pontos2);
    if (pontos1 > pontos2) 
    {
        printf("  =========== Jogador 1 venceu! ===========  \n");
    }
    else if (pontos2 > pontos1) 
    {
        printf("  =========== Jogador 2 venceu! ===========  \n");
    }
    else 
    {
        printf("  ============= EMPATE =============  \n");
    }
}
