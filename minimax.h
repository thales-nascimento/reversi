#ifndef __MINIMAX_H__
#define __MINIMAX_H__

#include "tabuleiro.h"
#include "string.h"

void rushPlay(int jogador, Posicao *jogadas, int n_jogadas);

void clonarTabuleiro(celula_t origem[LADO_TABULEIRO][LADO_TABULEIRO], celula_t destino[LADO_TABULEIRO][LADO_TABULEIRO]);
#endif
