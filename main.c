#include <stdio.h>
#include "graficos.h"
#include "tabuleiro.h"
#include "menu.h"
#include <SDL2/SDL.h>
#include <SOIL/SOIL.h>
#include <SDL2/SDL_mixer.h> 

#define SEM_JOGADAS 0
#define HA_JOGADAS 1

#define ESTADO_JOGANDO 0
#define ESTADO_VITORIA 1
#define ESTADO_MENU_PRINCIPAL 2
#define ESTADO_MENU_PAUSA 3
#define ESTADO_CREDITOS 4

int jogador_ativo = BRANCO;
int menu_principal=0,menu_pausa=0;


void trocarEstado(int estado);

int trocarJogador(){
	if(jogador_ativo==PRETO){
		jogador_ativo=BRANCO;
	} else {
		jogador_ativo=PRETO;
	}
	
	static int ultimo_n_jogadas = 0;		//limpar as marcações da rodada anterior
	static Posicao *ultimas_jogadas = NULL;
	int i;
	for(i=0; i<ultimo_n_jogadas; i++){
		tabuleiro[ultimas_jogadas[i].x][ultimas_jogadas[i].y] &= ~ATIVO;
	}
	
	int n_jogadas = 0;						//gerar marcacoes desta rodada
	Posicao *jogadas = possiveisJogadas(jogador_ativo, &n_jogadas);
	for (i=0; i<n_jogadas; i++) {
		tabuleiro[jogadas[i].x][jogadas[i].y] |= ATIVO;
	}
	
	if(ultimas_jogadas != NULL) free(ultimas_jogadas);	
	ultimo_n_jogadas = n_jogadas;			//preparar para limpar as marcacoes desta rodada
	ultimas_jogadas = jogadas;

	if(n_jogadas==0){
		return SEM_JOGADAS;
	} else {
		return HA_JOGADAS;
	}
}

void vitoria(){
	if(pontuacao.branco > pontuacao.preto)jogador_ativo=BRANCO;	//ultimo jogador ativo aparecerá na mensagem de vitória
	else jogador_ativo = PRETO;
	trocarEstado(ESTADO_VITORIA);
}

void controleDeJogo(){
	if(trocarJogador() == SEM_JOGADAS){
		if(trocarJogador() == SEM_JOGADAS){
			vitoria();
		}
	}
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

void activeMouse(int key,int status,int x, int y){
	int j = (x-LADO_CASA/2)/(LADO_CASA);
	if(j<LADO_TABULEIRO){
		
		int i = (y-LADO_CASA/2)/(LADO_CASA);
		if(i<LADO_TABULEIRO){
			if(tabuleiro[i][j] & ATIVO){
				tabuleiro[i][j] &= ~ATIVO;
				Posicao posicao = {j,i};
				jogar(jogador_ativo, posicao);
				controleDeJogo();
			};
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
			glutMouseFunc(activeMouse);
		break;
		case ESTADO_VITORIA:
			glutDisplayFunc(drawVictory);
			glutPassiveMotionFunc(hoverMouse);
			glutKeyboardFunc(keyboardVictory);
			glutMouseFunc(activeMouse);
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
	
	glDisable(GL_LIGHTING);
	
	glViewport(0,0, XMAX, YMAX);
	glOrtho(0, XMAX, YMAX, 0, -1, 1);
	
}

void iniciarPartidaHumanoHumano(){
	esvaziaTabuleiro();
	trocarJogador();
	trocarEstado(ESTADO_JOGANDO);
}
void inciarPartidaHumanoMaquina(){
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
	iniciarMenu(XMAX,YMAX);
	menu_principal = novoMenu();
	selecionarMenu(menu_principal);
	adicionarTexto("REVERSI",50,10);
	adicionarBotao("humano vs humano", 40,20,20,5,iniciarPartidaHumanoHumano);
	adicionarBotao("humano vs maquina", 40,20,28,5,inciarPartidaHumanoMaquina);
	adicionarBotao("creditos", 40,20,36,5,mostrarCreditos);
	adicionarBotao("sair", 40,20,44,5,quitar);
	menu_pausa = novoMenu();
	selecionarMenu(menu_pausa);
	adicionarTexto("JOGO PAUSADO", 50, 10);
	adicionarBotao("retornar ao jogo", 40,20,20,5,retornarAoJogo);
	adicionarBotao("menu principal", 40,20,28,5,menuPrincipal);
	adicionarBotao("sair", 40,20,36,5,quitar);
	
	inicializaGl(argc, argv);
	
	menuPrincipal();
	
	glutTimerFunc(20,mainLoop,0);
	glutMainLoop();
	return 0;
}
