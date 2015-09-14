#include "tabuleiro.h"
uint16_t tabuleiro[LADO_TABULEIRO][LADO_TABULEIRO] = {{0}};
Pontos pontuacao = {0,0};



void pontuar(int jogador, unsigned char swap){		//incrementa os pontos do jogador em 1 e converte 'swap' pontos do adversario para o jogador
	if(jogador==PRETO){
		pontuacao.preto += swap +1;
		pontuacao.branco -= swap;
	} else {
		pontuacao.branco += swap +1;
		pontuacao.preto -= swap;
	}
}

Posicao *possiveisJogadas(int jogador, int* n_jogadas) {
	// Vetor de jogadas possiveis
	Posicao* jogadas = NULL;
	*n_jogadas = 0;
	int i, j, k, l, adversario;
	if (jogador == BRANCO) {
		adversario = PRETO;
	} else {
		adversario = BRANCO;
	}
	// Percorre o tabuleiro procurando peças do jogador
	for (i = 0; i < LADO_TABULEIRO; i++) {
        for (j = 0; j < LADO_TABULEIRO; j++) {
			if (tabuleiro[i][j] & jogador) {
				// Vetor de peças adversárias vizinhas
				Posicao *vizinhos = (Posicao*) malloc(sizeof(Posicao));
				int n_vizinhos = 0;
                if (i == 0) { // se estiver na primeira linha não verifica a linha anterior
                    if (tabuleiro[i+1][j] & adversario) {
                        Posicao aux;
                        n_vizinhos++;
                        vizinhos = (Posicao*) realloc(vizinhos, n_vizinhos * sizeof(Posicao));
                        aux.x = i+1;
                        aux.y = j;
                        vizinhos[n_vizinhos - 1] = aux;
                    }
                    switch (j) {
                        default:
                        case 0: // se estiver na primeira coluna não verifica a coluna anterior
                            if (tabuleiro[i][j+1] & adversario) {
                                Posicao aux;
                                n_vizinhos++;
                                vizinhos = (Posicao*) realloc(vizinhos, n_vizinhos * sizeof(Posicao));
                                aux.x = i;
                                aux.y = j+1;
                                vizinhos[n_vizinhos - 1] = aux;
                            }
                            if (tabuleiro[i+1][j+1] & adversario) {
                                Posicao aux;
                                n_vizinhos++;
                                vizinhos = (Posicao*) realloc(vizinhos, n_vizinhos * sizeof(Posicao));
                                aux.x = i+1;
                                aux.y = j+1;
                                vizinhos[n_vizinhos - 1] = aux;
                            }
                            if (j == 0) // se entrar no 0 direto sai, se tiver entrado no default vai para o próximo caso
                                break;
                        case LADO_TABULEIRO - 1: // se estiver na última coluna não verifica a proxima coluna
                            if (tabuleiro[i][j-1] & adversario) {
                                Posicao aux;
                                n_vizinhos++;
                                vizinhos = (Posicao*) realloc(vizinhos, n_vizinhos * sizeof(Posicao));
                                aux.x = i;
                                aux.y = j-1;
                                vizinhos[n_vizinhos - 1] = aux;
                            }
                            if (tabuleiro[i+1][j-1] & adversario) {
                                Posicao aux;
                                n_vizinhos++;
                                vizinhos = (Posicao*) realloc(vizinhos, n_vizinhos * sizeof(Posicao));
                                aux.x = i+1;
                                aux.y = j-1;
                                vizinhos[n_vizinhos - 1] = aux;
                            }
                            break;
                    }
                } else if (i == LADO_TABULEIRO - 1) {
                    if (tabuleiro[i-1][j] & adversario) {
                        Posicao aux;
                        n_vizinhos++;
                        vizinhos = (Posicao*) realloc(vizinhos, n_vizinhos * sizeof(Posicao));
                        aux.x = i-1;
                        aux.y = j;
                        vizinhos[n_vizinhos - 1] = aux;
                    }
                    switch (j) {
                        default: 
                        case 0: // se estiver na primeira coluna não verifica a coluna anterior
                            if (tabuleiro[i][j+1] & adversario) {
                                Posicao aux;
                                n_vizinhos++;
                                vizinhos = (Posicao*) realloc(vizinhos, n_vizinhos * sizeof(Posicao));
                                aux.x = i;
                                aux.y = j+1;
                                vizinhos[n_vizinhos - 1] = aux;
                            }
                            if (tabuleiro[i-1][j+1] & adversario) {
                                Posicao aux;
                                n_vizinhos++;
                                vizinhos = (Posicao*) realloc(vizinhos, n_vizinhos * sizeof(Posicao));
                                aux.x = i-1;
                                aux.y = j+1;
                                vizinhos[n_vizinhos - 1] = aux;
                            }
                            if (j == 0) // se entrar no 0 direto sai, se tiver entrado no default vai para o próximo caso
                                break;
                        case LADO_TABULEIRO - 1: // se estiver na última coluna não verifica a coluna anterior
                            if (tabuleiro[i][j-1] & adversario) {
                                Posicao aux;
                                n_vizinhos++;
                                vizinhos = (Posicao*) realloc(vizinhos, n_vizinhos * sizeof(Posicao));
                                aux.x = i;
                                aux.y = j-1;
                                vizinhos[n_vizinhos - 1] = aux;
                            }
                            if (tabuleiro[i-1][j-1] & adversario) {
                                Posicao aux;
                                n_vizinhos++;
                                vizinhos = (Posicao*) realloc(vizinhos, n_vizinhos * sizeof(Posicao));
                                aux.x = i-1;
                                aux.y = j-1;
                                vizinhos[n_vizinhos - 1] = aux;
                            }
                            break;
                    }
                } else if (j == 0) { // se estiver na primeira coluna não verifica a coluna anterior
                    for (k = -1; k <= 1 ; k++) {
                        for (l = 0; l <= 1; l++) {
                            if (k == i && l == j) {
                                // não faz nada
                            } else {
                                if (tabuleiro[i + k][j + l] & adversario) {
                                    Posicao aux;
                                    n_vizinhos++;
                                    vizinhos = (Posicao*) realloc(vizinhos, n_vizinhos * sizeof(Posicao));
                                    aux.x = i + k;
                                    aux.y = j + l;
                                    vizinhos[n_vizinhos - 1] = aux;
                                }
                            }
                        }
                    }
                } else if (j == LADO_TABULEIRO - 1) { // se estiver na última coluna não verifica a próxima
                    for (k = -1; k <= 1 ; k++) {
                        for (l = -1; l <= 0; l++) {
                            if (k == i && l == j) {
                                // não faz nada
                            } else {
                                if (tabuleiro[i + k][j + l] & adversario) {
                                    Posicao aux;
                                    n_vizinhos++;
                                    vizinhos = (Posicao*) realloc(vizinhos, n_vizinhos * sizeof(Posicao));
                                    aux.x = i + k;
                                    aux.y = j + l;
                                    vizinhos[n_vizinhos - 1] = aux;
                                }
                            }
                        }
                    }
                } else { // se não estiver em nenhuma das extremidades verifica tds os vizinhos
                    for (k = -1; k <= 1 ; k++) {
                        for (l = -1; l <= 1; l++) {
                            if (k == i && l == j) {
                                // não faz nada
                            } else {
                                if (tabuleiro[i + k][j + l] & adversario) {
                                    Posicao aux;
                                    n_vizinhos++;
                                    vizinhos = (Posicao*) realloc(vizinhos, n_vizinhos * sizeof(Posicao));
                                    aux.x = i + k;
                                    aux.y = j + l;
                                    vizinhos[n_vizinhos - 1] = aux;
                                }
                            }
                        }
                    }
                }
                int c;
                // Percorre o vetor de peças adversarias vizinhas
                for (c = 0; c < n_vizinhos; c++) {
                    if (vizinhos[c].x == i + 1 && vizinhos[c].y == j - 1) { // baixo esquerda
                        for (k = i + 2, l = j - 2; k < LADO_TABULEIRO && l >= 0; k++, l--) {
                            if (tabuleiro[k][l] == VAZIO) {
                                Posicao aux;
                                (*n_jogadas)++;
                                aux.x = k;
                                aux.y = l;
                                jogadas = (Posicao*) realloc(jogadas, (*n_jogadas) * sizeof(Posicao));
                                jogadas[(*n_jogadas) - 1] = aux;
                                break;
                            } else if (tabuleiro[k][l] & jogador) {
                                break;
                            }
                        }
                    } else if (vizinhos[c].x == i + 1 && vizinhos[c].y == j){ // baixo
                        for (k = i + 2; k < LADO_TABULEIRO; k++) {
                            if (tabuleiro[k][j] == VAZIO) {
                                Posicao aux;
                                (*n_jogadas)++;
                                aux.x = k;
                                aux.y = j;
                                jogadas = (Posicao*) realloc(jogadas, (*n_jogadas) * sizeof(Posicao));
                                jogadas[(*n_jogadas) - 1] = aux;
                                break;
                            } else if (tabuleiro[k][j] & jogador) {
                                break;
                            }
                        }
                    } else if (vizinhos[c].x == i + 1 && vizinhos[c].y == j + 1){ // baixo direita
                        for (k = i + 2, l = j + 2; k < LADO_TABULEIRO && l < LADO_TABULEIRO; k++, l++) {
                            if (tabuleiro[k][l] == VAZIO) {
                                Posicao aux;
                                (*n_jogadas)++;
                                aux.x = k;
                                aux.y = l;
                                jogadas = (Posicao*) realloc(jogadas, (*n_jogadas) * sizeof(Posicao));
                                jogadas[(*n_jogadas) - 1] = aux;
                                break;
                            } else if (tabuleiro[k][l] & jogador) {
                                break;
                            }
                        }
                    } else if (vizinhos[c].x == i     && vizinhos[c].y == j + 1){ // direita
                        for (l = j + 2; l < LADO_TABULEIRO; l++) {
                            if (tabuleiro[i][l] == VAZIO) {
                                Posicao aux;
                                (*n_jogadas)++;
                                aux.x = i;
                                aux.y = l;
                                jogadas = (Posicao*) realloc(jogadas, (*n_jogadas) * sizeof(Posicao));
                                jogadas[(*n_jogadas) - 1] = aux;
                                break;
                            } else if (tabuleiro[i][l] & jogador) {
                                break;
                            }
                        }
                    } else if (vizinhos[c].x == i - 1 && vizinhos[c].y == j + 1){ // cima direita
                        for (k = i - 2, l = j + 2; k >= 0 && l < LADO_TABULEIRO; k--, l++) {
                            if (tabuleiro[k][l] == VAZIO) {
                                Posicao aux;
                                (*n_jogadas)++;
                                aux.x = k;
                                aux.y = l;
                                jogadas = (Posicao*) realloc(jogadas, (*n_jogadas) * sizeof(Posicao));
                                jogadas[(*n_jogadas) - 1] = aux;
                                break;
                            } else if (tabuleiro[k][l] & jogador) {
                                break;
                            }
                        }
                    } else if (vizinhos[c].x == i - 1 && vizinhos[c].y == j){ // cima
                        for (k = i - 2; k >= 0; k--) {
                            if (tabuleiro[k][j] == VAZIO) {
                                Posicao aux;
                                (*n_jogadas)++;
                                aux.x = k;
                                aux.y = j;
                                jogadas = (Posicao*) realloc(jogadas, (*n_jogadas) * sizeof(Posicao));
                                jogadas[(*n_jogadas) - 1] = aux;
                                break;
                            } else if (tabuleiro[k][j] & jogador) {
                                break;
                            }
                        }
                    } else if (vizinhos[c].x == i - 1 && vizinhos[c].y == j - 1){ // cima esquerda
                        for (k = i - 2, l = j - 2; k >= 0 && l >= 0; k--, l--) {
                            if (tabuleiro[k][l] == VAZIO) {
                                Posicao aux;
                                (*n_jogadas)++;
                                aux.x = k;
                                aux.y = l;
                                jogadas = (Posicao*) realloc(jogadas, (*n_jogadas) * sizeof(Posicao));
                                jogadas[(*n_jogadas) - 1] = aux;
                                break;
                            } else if (tabuleiro[k][l] & jogador) {
                                break;
                            }
                        }
                    } else if (vizinhos[c].x == i && vizinhos[c].y == j - 1){ // esquerda
                        for (l = j - 2; l >= 0; l--) {
                            if (tabuleiro[i][l] == VAZIO) {
                                Posicao aux;
                                (*n_jogadas)++;
                                aux.x = i;
                                aux.y = l;
                                jogadas = (Posicao*) realloc(jogadas, (*n_jogadas) * sizeof(Posicao));
                                jogadas[(*n_jogadas) - 1] = aux;
                                break;
                            } else if (tabuleiro[i][l] & jogador) {
                                break;
                            }
                        }
                    }
                }
                free(vizinhos);
            }
        }
    }
	
	return jogadas;
}

void jogar(int jogador, const Posicao jogada){
	unsigned char swap=0;		//pontos que serão trocados entre os jogadores
	int adversario=jogador==BRANCO?PRETO:BRANCO;
	
	tabuleiro[jogada.y][jogada.x] = jogador;
	
	//atualizar tabuleiro
	int i, j;
	for(i=jogada.x+1; i<LADO_TABULEIRO ;i++){	//percorrer horizontalmente (->) procurando uma peça para fechar as outras
		if(tabuleiro[jogada.y][i] & jogador){
			swap += i-jogada.x-1;
			for(i=i-1; i>jogada.x; i--){			//retornando convertendo as peças
				tabuleiro[jogada.y][i] &= ~adversario;
				tabuleiro[jogada.y][i] |= jogador;
				tabuleiro[jogada.y][i] |= TRANSICAO;
			}
			break;
		
		} else if(tabuleiro[jogada.y][i] & VAZIO){
			break;
		}
	}
	for(i=jogada.x-1; i>=0; i--){				//percorrer horizontalmente (<-) procurando uma peça para fechar as outras
		if(tabuleiro[jogada.y][i] & jogador){
			swap += jogada.x-i-1;
			for(i=i+1; i<jogada.x; i++){		//retornando fechando as peças
				tabuleiro[jogada.y][i] &= ~adversario;
				tabuleiro[jogada.y][i] |= jogador;
				tabuleiro[jogada.y][i] |= TRANSICAO;
			}
			break;
		
		} else if(tabuleiro[jogada.y][i] & VAZIO){
			break;
		}
	}
	for(i=jogada.y+1; i<LADO_TABULEIRO; i++){		//percorrer verticalmente (^) procurando uma peça para fechar as outras
		if(tabuleiro[i][jogada.x] & jogador){
			swap += i-jogada.y-1;
			for(i=i-1; i>jogada.y; i--){
				tabuleiro[i][jogada.x] &= ~adversario;
				tabuleiro[i][jogada.x] |= jogador;
				tabuleiro[i][jogada.x] |= TRANSICAO;
			}
			break;
			
		} else if(tabuleiro[i][jogada.x] & VAZIO){
			break;
		}
	}
	for(i=jogada.y-1; i>=0; i--){					//percorrer verticalmente (v) procurando uma peça para fechar as outras
		if(tabuleiro[i][jogada.x] & jogador){
			swap += jogada.y-i-1;
			for(i=i+1; i<jogada.y; i++){
				tabuleiro[i][jogada.x] &= ~adversario;
				tabuleiro[i][jogada.x] |= jogador;
				tabuleiro[i][jogada.x] |= TRANSICAO;
			}
			break;
			
		} else if(tabuleiro[i][jogada.x] & VAZIO){
			break;
		} 
	}
	
	for(i=jogada.x-1, j=jogada.y-1; i>=0 && j>=0; --i, --j){			//percorrer diagonalmente (<v) procurando uma peça para fechar as outras
		if(tabuleiro[j][i] & jogador){
			swap += jogada.x-i-1;
			for(i=i+1, j=j+1; i<jogada.x; i++,j++){
				tabuleiro[j][i] &= ~adversario;
				tabuleiro[j][i] |= jogador;
				tabuleiro[j][i] |= TRANSICAO;
			}
			break;
			
		} else if(tabuleiro[j][i] & VAZIO){
			break;
		} 
	}
	for(i=jogada.x+1, j=jogada.y-1; i<LADO_TABULEIRO && j>=0; ++i, --j){			//percorrer diagonalmente (>v) procurando uma peça para fechar as outras
		if(tabuleiro[j][i] & jogador){
			swap += jogada.y-j-1;
			for(i=i-1, j=j+1; j<jogada.y; i--,j++){
				tabuleiro[j][i] &= ~adversario;
				tabuleiro[j][i] |= jogador;
				tabuleiro[j][i] |= TRANSICAO;
			}
			break;
			
		} else if(tabuleiro[j][i] & VAZIO){
			break;
		} 
	}
	for(i=jogada.x-1, j=jogada.y+1; i>=0 && j<LADO_TABULEIRO; --i, ++j){			//percorrer diagonalmente (<^) procurando uma peça para fechar as outras
		if(tabuleiro[j][i] & jogador){
			swap += jogada.x-i-1;
			for(i=i+1, j=j-1; i<jogada.x; i++,j--){
				tabuleiro[j][i] &= ~adversario;
				tabuleiro[j][i] |= jogador;
				tabuleiro[j][i] |= TRANSICAO;
			}
			break;
			
		} else if(tabuleiro[j][i] & VAZIO){
			break;
		} 
	}
	for(i=jogada.x+1, j=jogada.y+1; i<LADO_TABULEIRO && j<LADO_TABULEIRO; ++i, ++j){			//percorrer diagonalmente (>^) procurando uma peça para fechar as outras
		if(tabuleiro[j][i] & jogador){
			swap += i-jogada.x-1;
			for(i=i-1, j=j-1; i>jogada.x; i--,j--){
				tabuleiro[j][i] &= ~adversario;
				tabuleiro[j][i] |= jogador;
				tabuleiro[j][i] |= TRANSICAO;
			}
			break;
			
		} else if(tabuleiro[j][i] & VAZIO){
			break;
		} 
	}
	
	pontuar(jogador, swap);
}


void esvaziaTabuleiro() {
	int i, j;
	for (i = 0; i < LADO_TABULEIRO; i++) {
		for (j = 0; j < LADO_TABULEIRO; j++) {
			tabuleiro[i][j] = VAZIO;
		}
	}
	tabuleiro[LADO_TABULEIRO/2][LADO_TABULEIRO/2] = tabuleiro[LADO_TABULEIRO/2-1][LADO_TABULEIRO/2-1] = PRETO;
	tabuleiro[LADO_TABULEIRO/2][LADO_TABULEIRO/2-1] = tabuleiro[LADO_TABULEIRO/2-1][LADO_TABULEIRO/2] = BRANCO;
	pontuacao.branco = 2;
	pontuacao.preto = 2;
}

