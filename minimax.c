#include "minimax.h"

int jogador_maquina=VAZIO;

celula_t tabuleiro_local[LADO_TABULEIRO][LADO_TABULEIRO];

void clonarTabuleiro(celula_t destino[LADO_TABULEIRO][LADO_TABULEIRO], celula_t origem[LADO_TABULEIRO][LADO_TABULEIRO]){
	memcpy(destino, origem, sizeof(celula_t[LADO_TABULEIRO][LADO_TABULEIRO]));
}

int bordas_valiosas=0;
int valorar(int jogador, Posicao *jogada){
	int valor=0;
	int k,l;
	for (k = jogada->y + 1, l = jogada->x - 1; k < LADO_TABULEIRO && l >= 0; ++k, --l) {
		if (tabuleiro[k][l] & jogador) {
			valor += k -jogada->y -1;
			break;
		} else if (tabuleiro[k][l] & VAZIO) {
			break;
		}
	}
	for (k = jogada->y + 1; k < LADO_TABULEIRO; ++k) {
		if (tabuleiro[k][jogada->x] & jogador) {
			valor += k -jogada->y -1;
			break;
		} else if (tabuleiro[k][jogada->x] & VAZIO) {
			break;
		}
	}
	for (k = jogada->y + 1, l = jogada->x + 1; k < LADO_TABULEIRO && l < LADO_TABULEIRO; ++k, ++l) {
		if (tabuleiro[k][l] & jogador) {
			valor += k -jogada->y -1;
			break;
		} else if (tabuleiro[k][l] & VAZIO) {
			break;
		}
	}
	for (l = jogada->x + 1; l < LADO_TABULEIRO; ++l) {
		if (tabuleiro[jogada->y][l] & jogador) {
			valor += l -jogada->x -1;
			break;
		} else if (tabuleiro[jogada->y][l] & VAZIO) {
			break;
		}
	}
	for (k = jogada->y - 1, l = jogada->x + 1; k >= 0 && l < LADO_TABULEIRO; --k, ++l) {
		if (tabuleiro[k][l] & jogador) {
			valor += l -jogada->x -1;
			break;
		} else if (tabuleiro[k][l] & VAZIO) {
			break;
		}
	}
	for (k = jogada->y - 1; k >= 0; --k) {
		if (tabuleiro[k][jogada->x] & jogador) {
			valor += jogada->y -k -1;
			break;
		} else if (tabuleiro[k][jogada->x] & VAZIO) {
			break;
		}
	}
	for (k = jogada->y - 1, l = jogada->x - 1; k >= 0 && l >= 0; --k, --l) {
		if (tabuleiro[k][l] & jogador) {
			valor += jogada->y -k -1;
			break;
		} else if (tabuleiro[k][l] & VAZIO) {
			break;
		}
	}
	for (l = jogada->x - 1; l >= 0; --l) {
		if (tabuleiro[jogada->y][l] & jogador) {
			valor += jogada->x -l -1;
			break;
		} else if (tabuleiro[jogada->y][l] & VAZIO) {
			break;
		}
	}
	
	if(bordas_valiosas){
		if(jogada->x == 0 || jogada->x == LADO_TABULEIRO-1){	//valorizar bordas
				valor += 3;
		}
		if(jogada->y == 0 || jogada->y == LADO_TABULEIRO-1){
				valor += 3;
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


int miniMax(int jogador, int profundidade, int alfa, int beta){
	int adversario = jogador==PRETO?BRANCO:PRETO;
	int valor = jogador==jogador_maquina?0:LADO_TABULEIRO*LADO_TABULEIRO;
	
	int n_jogadas;
	Posicao *jogadas = possiveisJogadas(jogador, &n_jogadas);

	celula_t becape_tabuleiro[LADO_TABULEIRO][LADO_TABULEIRO];
	clonarTabuleiro(becape_tabuleiro, tabuleiro);
	Pontos becape_pontos = pontuacao;
	Posicao becape_jogadas[LADO_TABULEIRO*LADO_TABULEIRO];
	memcpy(becape_jogadas, jogadas, sizeof(Posicao)*n_jogadas);
	
	
	if(profundidade == 0){			//fim da recursão
		int incremento, c;
		if(n_jogadas == 0){
			incremento = 0;
		} else if(jogador==jogador_maquina){
			int incremento=0;
			for (c = 0; c < n_jogadas; ++c) {
				int valor_jogada=valorar(jogador, jogadas +c);
				if(valor_jogada > incremento){
					incremento=valor_jogada;
				}
				if(valor_jogada >= beta)break;
			}
			
		} else {
			int incremento=LADO_TABULEIRO*LADO_TABULEIRO;
			for (c = 0; c < n_jogadas; ++c) {
				int valor_jogada=valorar(jogador, jogadas +c);
				if(valor_jogada < incremento){
					incremento=valor_jogada;
				}
				if (valor_jogada <= alfa)break;
			}
		}
		if(jogador_maquina==PRETO){
			valor = pontuacao.preto + incremento;
		} else {
			valor = pontuacao.branco + incremento;
		}
	
	} else {
		int i;
		for(i=0;i<n_jogadas;i++){
			jogar(jogador, jogadas[i]);
			int valor_2 = miniMax(adversario, profundidade-1, alfa, beta);
			if(jogador==jogador_maquina){
				if(valor_2 > valor)valor=valor_2;	
				if(valor_2 >= beta)break;
				if(valor_2 > alfa)alfa=valor_2;
				
			} else {
				if(valor_2 < valor)valor=valor_2;
				if(valor_2 <= alfa)break;
				if(valor_2 < beta)beta=valor_2;
			}
			clonarTabuleiro(tabuleiro,becape_tabuleiro);
			pontuacao = becape_pontos;
			memcpy(jogadas, becape_jogadas, sizeof(Posicao)*n_jogadas);
			
		}
	}
	
	return valor;
}

unsigned profundidade = 8;
void miniMaxPlay(int jogador, Posicao *jogadas, int n_jogadas){
	if(n_jogadas==0)return;
	int adversario = jogador==PRETO?BRANCO:PRETO;
	int valor = 0;

	int alfa=0;
	int beta=LADO_TABULEIRO*LADO_TABULEIRO;

	celula_t becape_tabuleiro[LADO_TABULEIRO][LADO_TABULEIRO];
	clonarTabuleiro(becape_tabuleiro, tabuleiro);
	Pontos becape_pontos = pontuacao;
	Posicao becape_jogadas[LADO_TABULEIRO*LADO_TABULEIRO];
	memcpy(becape_jogadas, jogadas, sizeof(Posicao)*n_jogadas);
	
	int melhor_jogada=0;
	int i;
	for(i=0;i<n_jogadas;i++){
		jogar(jogador, jogadas[i]);
		int valor_2 = miniMax(adversario, profundidade-1, alfa, beta);	
		if(valor_2 > alfa)alfa=valor_2;
		if(valor_2 > valor){
			valor=valor_2;
			melhor_jogada = i;
		}
			
		clonarTabuleiro(tabuleiro,becape_tabuleiro);
		pontuacao = becape_pontos;
		memcpy(jogadas, becape_jogadas, sizeof(Posicao)*n_jogadas);
	}
	
	jogar(jogador, jogadas[melhor_jogada]);
}


void (*aiPlay)(int, Posicao*, int) = miniMaxPlay;
void iniciarAi(int estrategia){
	if(estrategia & MINIMAX_PLAY){
		aiPlay = miniMaxPlay;
		profundidade = estrategia & PROFUNDIDADE;
		if(profundidade < 1 || profundidade > 8){
			puts("profundidade errada. disparado em 'void iniciarAi(int)'");
			exit(1);
		}
	} else {
		aiPlay = rushPlay;
	}
	
	
	bordas_valiosas = estrategia & VALORIZAR_BORDAS;
}
