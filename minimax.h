#ifndef __MINIMAX_H__
#define __MINIMAX_H__

#include "tabuleiro.h"
#include "stdio.h"

extern int jogador_maquina;

#define RUSH_PLAY 0x10
#define MINIMAX_PLAY 0x20
#define VALORIZAR_BORDAS 0x40
#define PROFUNDIDADE 0x0f

void iniciarAi(int estragegia);

extern void (*aiPlay)(int, Posicao*, int);

#endif
