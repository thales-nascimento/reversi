#ifndef __TABULEIRO_H__
#define __TABULEIRO_H__

#include <stdlib.h>
#include <stdint.h>

// Estados de cada posição, preto e branco também são jogadores 
#define PRETO 0x100
#define BRANCO 0x200
#define VAZIO 0x400
#define HOVER 0x10
#define ATIVO 0x20
#define TRANSICAO 0xf
#define TRANSITAR 0x1

#define LADO_TABULEIRO 8
typedef uint16_t celula_t;
extern celula_t tabuleiro[LADO_TABULEIRO][LADO_TABULEIRO];

typedef struct{
	unsigned char preto, branco;
}Pontos;
typedef struct {
	unsigned char x, y;
} Posicao;

extern Pontos pontuacao;
/**
* Retorna um vetor de jogada com as possíveis jogadas para o jogador recebido por parâmetro
* Caso não seja possível efetuar jogada, returna NULL
*/
Posicao *possiveisJogadas(int jogador, int* n_jogadas);

/**
* Efetua a Posicao recebida por parâmetro para o jogador recebido por parâmetro
*/
void jogar(int jogador, Posicao jogada);

/**
* Esvazia o tabuleiro, colocando todas as posições como VAZIO
*/
void esvaziaTabuleiro();

void pontuar(int jogador, unsigned char swap);

#endif
