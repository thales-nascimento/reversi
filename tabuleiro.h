#ifndef __TABULEIRO_H__
#define __TABULEIRO_H__

#include <stdlib.h>

// Estados de cada posição, preto e branco também são jogadores 
#define PRETO 0x1
#define BRANCO 0x2
#define VAZIO 0x4
#define HOVER 0x10
#define ATIVO 0x20

#define LADO_TABULEIRO 8
extern char tabuleiro[LADO_TABULEIRO][LADO_TABULEIRO];

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

#endif
