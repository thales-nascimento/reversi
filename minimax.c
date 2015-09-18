#include "minimax.h"

void clonarTabuleiro(celula_t origem[LADO_TABULEIRO][LADO_TABULEIRO], celula_t destino[LADO_TABULEIRO][LADO_TABULEIRO]){
	memcpy(destino, origem, sizeof(celula_t[LADO_TABULEIRO][LADO_TABULEIRO]));
}

int valorar(int jogador, Posicao *jogada){
	int valor=0;
	int k,l;
	for (k = jogada->y + 1, l = jogada->x - 1; k < LADO_TABULEIRO && l >= 0; k++, l--) {
		if (tabuleiro[k][l] & jogador) {
			valor += k -jogada->y -1;
			break;
		} else if (tabuleiro[k][l] & VAZIO) {
			break;
		}
	}
	for (k = jogada->y + 1; k < LADO_TABULEIRO; k++) {
		if (tabuleiro[k][jogada->x] & jogador) {
			valor += k -jogada->y -1;
			break;
		} else if (tabuleiro[k][jogada->x] & VAZIO) {
			break;
		}
	}
	for (k = jogada->y + 1, l = jogada->x + 1; k < LADO_TABULEIRO && l < LADO_TABULEIRO; k++, l++) {
		if (tabuleiro[k][l] & jogador) {
			valor += k -jogada->y -1;
			break;
		} else if (tabuleiro[k][l] & VAZIO) {
			break;
		}
	}
	for (l = jogada->x + 1; l < LADO_TABULEIRO; l++) {
		if (tabuleiro[jogada->y][l] & jogador) {
			valor += l -jogada->x -1;
			break;
		} else if (tabuleiro[jogada->y][l] & VAZIO) {
			break;
		}
	}
	for (k = jogada->y - 1, l = jogada->x + 1; k >= 0 && l < LADO_TABULEIRO; k--, l++) {
		if (tabuleiro[k][l] & jogador) {
			valor += l -jogada->x -1;
			break;
		} else if (tabuleiro[k][l] & VAZIO) {
			break;
		}
	}
	for (k = jogada->y - 1; k >= 0; k--) {
		if (tabuleiro[k][jogada->x] & jogador) {
			valor += jogada->y -k -1;
			break;
		} else if (tabuleiro[k][jogada->x] & VAZIO) {
			break;
		}
	}
	for (k = jogada->y - 1, l = jogada->x - 1; k >= 0 && l >= 0; k--, l--) {
		if (tabuleiro[k][l] & jogador) {
			valor += jogada->y -k -1;
			break;
		} else if (tabuleiro[k][l] & VAZIO) {
			break;
		}
	}
	for (l = jogada->x - 1; l >= 0; l--) {
		if (tabuleiro[jogada->y][l] & jogador) {
			valor += jogada->x -l -1;
			break;
		} else if (tabuleiro[jogada->y][l] & VAZIO) {
			break;
		}
	}
	return valor;
}

int max(int jogador, Posicao *jogadas, int n_jogadas){
	int max=-1;
	int indice=0;
	int c;
	for (c = 0; c < n_jogadas; ++c) {
		int valor=valorar(jogador, jogadas +c);
		if(valor > max){
			max=valor;
			indice=c;
		}
	}
	return indice;
}


int min(int jogador, Posicao *jogadas, int n_jogadas){
	int min=LADO_TABULEIRO*LADO_TABULEIRO;
	int indice=0;
	int c;
	for (c = 0; c < n_jogadas; ++c) {
		int valor=valorar(jogador, jogadas +c);
		if(valor < min){
			min=valor;
			indice=c;
		}
	}
	return indice;
}



void rushPlay(int jogador, Posicao *jogadas, int n_jogadas){
	if(n_jogadas==0)return;
	jogar(jogador, jogadas[max(jogador, jogadas, n_jogadas)]);
}
