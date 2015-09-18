#include <stdio.h>
#include "graficos.h"
#include "tabuleiro.h"
#include "menu.h"
#include "minimax.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h> 
#include <time.h>

#define ESTADO_JOGANDO 0
#define ESTADO_VITORIA 2
#define ESTADO_MENU_PRINCIPAL 3
#define ESTADO_MENU_PAUSA 4
#define ESTADO_CREDITOS 5


int jogador_ativo = BRANCO;
int jogador_maquina = VAZIO;
int menu_principal=0,menu_pausa=0;

const char CAMINHO_TEXTURA_MENU[] = "resources/reversi2.jpg";

void trocarEstado(int estado);


int vencendo=0;
void vitoria(){
	vencendo=0;
	if(pontuacao.branco > pontuacao.preto)jogador_ativo=BRANCO;	//ultimo jogador ativo aparecerá na mensagem de vitória
	else if(pontuacao.branco < pontuacao.preto)jogador_ativo = PRETO;
	else jogador_ativo=VAZIO;
	trocarEstado(ESTADO_VITORIA);
}

int ultimo_n_jogadas = 0;		//limpar as marcações da rodada anterior
Posicao *ultimas_jogadas = NULL;
void limparMarcacoes(){
	if(ultimas_jogadas != NULL){
		int i;
		for(i=0; i<ultimo_n_jogadas; i++){
			tabuleiro[ultimas_jogadas[i].y][ultimas_jogadas[i].x] &= ~ATIVO;
		}
	}
}
void trocarJogador(){
	if(jogador_ativo==PRETO){
		jogador_ativo=BRANCO;
	} else {
		jogador_ativo=PRETO;
	}	

	
	limparMarcacoes();
	
	int n_jogadas = 0;						//gerar marcacoes desta rodada
	Posicao *jogadas = possiveisJogadas(jogador_ativo, &n_jogadas);
	
	if(n_jogadas==0){
		++vencendo;
		if(vencendo==2)vitoria();
	} else {
		vencendo=0;
	}
	
	if(jogador_maquina != jogador_ativo){	//apenas marca o tabuleiro para o jogador humano
		int i;
		for (i=0; i<n_jogadas; i++) {
			tabuleiro[jogadas[i].y][jogadas[i].x] |= ATIVO;
		}
		
		if(ultimas_jogadas != NULL) free(ultimas_jogadas);	
		ultimo_n_jogadas = n_jogadas;			//preparar para limpar as marcacoes desta rodada
		ultimas_jogadas = jogadas;
	} else {
		rushPlay(jogador_maquina, jogadas, n_jogadas);
		free(jogadas);
		trocarJogador();
	}
	
	
}

void machineDelay(int value){
	trocarJogador();
}

void drawVictory(){
	glClear(GL_COLOR_BUFFER_BIT);
	desenhaTabuleiro();
	desenhaPontuacao(jogador_ativo);
	if(jogador_ativo == PRETO){
		popup(" jogador\n\n preto\n\n venceu!\n\n  (ESC)");
	} else {
		popup(" jogador\n\n branco\n\n venceu!\n\n  (ESC)");
	}
	glFlush();
}

void drawGame(){
	glClear(GL_COLOR_BUFFER_BIT);
	desenhaTabuleiro();
	desenhaPontuacao(jogador_ativo);
	glFlush();
}
void desenhaCreditos(){
	glClear(GL_COLOR_BUFFER_BIT);
	desenhaTabuleiro();
	popup(" Thales\n Taleco\n\nVinicius\n Caminha\n\n  (ESC)");
	glFlush();
}

void ingameKeyboard(unsigned char key, int x, int y){
	switch(key){
		case 27:	//esc
			trocarEstado(ESTADO_MENU_PAUSA);
		break;
	}
}
void keyboardVictory(unsigned char key, int x, int y){
	if(key==27){	//esc
		trocarEstado(ESTADO_MENU_PRINCIPAL);
	}
}
void keyboardPrincipal(unsigned char key, int x, int y){
		//TODO
}
void keyboardPause(unsigned char key, int x, int y){
	switch(key){
		case 27:	//esc
			trocarEstado(ESTADO_JOGANDO);
		break;
	}
}
void noKeyboard(unsigned char key, int x, int y){}

void doisJogadoresMouse(int key,int status,int x, int y){
	int j = (x-LADO_CASA/2)/(LADO_CASA);
	if(j<LADO_TABULEIRO){
		
		int i = (y-LADO_CASA/2)/(LADO_CASA);
		if(i<LADO_TABULEIRO){
			if(tabuleiro[i][j] & ATIVO){
				tabuleiro[i][j] &= ~ATIVO;
				Posicao posicao = {j,i};
				jogar(jogador_ativo, posicao);
				if(jogador_maquina == VAZIO){
					trocarJogador();
					if(vencendo != 0){
						trocarJogador();
					}
				} else {
					limparMarcacoes();
					glutTimerFunc(500,machineDelay,0);
				}
			}
		}
	}
}
void noClick(int key, int status, int x, int y){}

void hoverMouse(int x, int y){
	static int last_y=0,last_x=0;
	tabuleiro[last_y][last_x] &= ~HOVER;
	
	int j = (x-LADO_CASA/2)/(LADO_CASA);
	if(j<LADO_TABULEIRO){
		
		int i = (y-LADO_CASA/2)/(LADO_CASA);
		if(i<LADO_TABULEIRO){
			tabuleiro[i][j] |= HOVER;
			last_y=i;
			last_x=j;
		}
	}
}
void noHover(int x,int y){}


void mainLoop(int value){		//game main loop
	glutTimerFunc(20,mainLoop,0);	
	glutPostRedisplay();
}

void trocarEstado(int estado){
	switch(estado){
		case ESTADO_JOGANDO:
			glutDisplayFunc(drawGame);
			glutPassiveMotionFunc(hoverMouse);
			glutKeyboardFunc(ingameKeyboard);	//corrigir
			glutMouseFunc(doisJogadoresMouse);
		break;
		case ESTADO_VITORIA:
			glutDisplayFunc(drawVictory);
			glutPassiveMotionFunc(hoverMouse);
			glutKeyboardFunc(keyboardVictory);
			glutMouseFunc(noClick);
		break;
		case ESTADO_MENU_PRINCIPAL:
			selecionarMenu(menu_principal);
			glutDisplayFunc(desenhaMenu);
			glutPassiveMotionFunc(menuHover);
			glutKeyboardFunc(keyboardPrincipal);
			glutMouseFunc(menuClick);
		break;
		case ESTADO_CREDITOS:
			glutDisplayFunc(desenhaCreditos);
			glutPassiveMotionFunc(noHover);
			glutKeyboardFunc(keyboardVictory);
			glutMouseFunc(noClick);
		break;
		case ESTADO_MENU_PAUSA:
			selecionarMenu(menu_pausa);
			glutDisplayFunc(desenhaMenu);
			glutPassiveMotionFunc(menuHover);
			glutKeyboardFunc(keyboardPause);//corrigir
			glutMouseFunc(menuClick);
		break;
		
	}
}

void inicializaGl(int argc, char** argv){
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE);
	glutInitWindowSize(XMAX,YMAX);
	glutCreateWindow("reversi");

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glViewport(0,0, XMAX, YMAX);
	glOrtho(0, XMAX, YMAX, 0, -1, 1);
	
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	
}

void iniciarPartidaHumanoHumano(){
	jogador_maquina=VAZIO;
	esvaziaTabuleiro();
	trocarJogador();
	trocarEstado(ESTADO_JOGANDO);
}
void inciarPartidaHumanoMaquina(){
	jogador_ativo=BRANCO;
	jogador_maquina=PRETO;
	
	esvaziaTabuleiro();
	trocarJogador();
	trocarEstado(ESTADO_JOGANDO);
}
void mostrarCreditos(){
	esvaziaTabuleiro();
	trocarEstado(ESTADO_CREDITOS);
}
void quitar(){
	destruirMenu();
	puts("obrigado por jogar");
	exit(0);
}
void menuPrincipal(){
	trocarEstado(ESTADO_MENU_PRINCIPAL);
}
void retornarAoJogo(){
	trocarEstado(ESTADO_JOGANDO);
}


int main(int argc, char **argv){
	inicializaGl(argc, argv);
	iniciarMenu(XMAX,YMAX);
	menu_principal = novoMenu(CAMINHO_TEXTURA_MENU);
	selecionarMenu(menu_principal);
	adicionarBotao("humano vs humano", 40,20,36,5,iniciarPartidaHumanoHumano);
	adicionarBotao("humano vs maquina", 40,20,44,5,inciarPartidaHumanoMaquina);
	adicionarBotao("creditos", 40,20,52,5,mostrarCreditos);
	adicionarBotao("sair", 40,20,60,5,quitar);
	menu_pausa = novoMenu(CAMINHO_TEXTURA_MENU);
	selecionarMenu(menu_pausa);
	adicionarTexto("JOGO PAUSADO", 50, 10);
	adicionarBotao("retornar ao jogo", 40,20,28,5,retornarAoJogo);
	adicionarBotao("menu principal", 40,20,36,5,menuPrincipal);
	adicionarBotao("sair", 40,20,44,5,quitar);
	
	menuPrincipal();
	
	glutTimerFunc(20,mainLoop,0);
	glutMainLoop();
	return 0;
}
