#ifndef __MINIMAX_H__
#define __MINIMAX_H__

#include "tabuleiro.h"


extern int jogador_maquina;


void iniciarAi();

void rushPlay(int jogador, Posicao *jogadas, int n_jogadas);
void rushCornerPlay(int jogador, Posicao *jogadas, int n_jogadas);
void miniMaxPlay(int jogador, Posicao *jogadas, int n_jogadas);

#endif
