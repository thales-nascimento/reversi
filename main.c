#include <stdio.h>
#include "graficos.h"
#include "tabuleiro.h"
#include "menu.h"
#include "minimax.h"
#include "splash.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h> 

#define ESTADO_JOGANDO 0
#define ESTADO_MENU_AI 1
#define ESTADO_VITORIA 2
#define ESTADO_MENU_PRINCIPAL 3
#define ESTADO_MENU_PAUSA 4
#define ESTADO_CREDITOS 5
#define ESTADO_SPLASH 6


int jogador_ativo = BRANCO;
int menu_principal=0,menu_pausa=0,menu_ai=0;

const char CAMINHO_TEXTURA_MENU[] = "resources/reversi.jpg";
const char *CAMINHO_TEXTURA_SPLASH[] = {"resources/logo",".jpg"};
SDL_Surface *screen;
Mix_Music *musica_fundo;

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
Posicao ultimas_jogadas[LADO_TABULEIRO*LADO_TABULEIRO];
void limparMarcacoes(){
	int i;
	for(i=0; i<ultimo_n_jogadas; i++){
		tabuleiro[ultimas_jogadas[i].y][ultimas_jogadas[i].x] &= ~ATIVO;
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
		if(vencendo==2){
			vitoria();
		} else {
			trocarJogador();
		}
	} else {
		vencendo=0;
	
		if(jogador_maquina != jogador_ativo){	//apenas marca o tabuleiro para o jogador humano
			int i;
			for (i=0; i<n_jogadas; i++) {
				tabuleiro[jogadas[i].y][jogadas[i].x] |= ATIVO;
			}
			
			ultimo_n_jogadas = n_jogadas;			//preparar para limpar as marcacoes desta rodada
			memcpy(ultimas_jogadas, jogadas,sizeof(Posicao)*n_jogadas);
		} else {
			aiPlay(jogador_maquina, jogadas, n_jogadas);
			trocarJogador();
		}
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

void keyboardIngame(unsigned char key, int x, int y){
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
void keyboardPause(unsigned char key, int x, int y){
	switch(key){
		case 27:	//esc
			trocarEstado(ESTADO_JOGANDO);
		break;
	}
}

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
				} else {
					limparMarcacoes();
					glutTimerFunc(500,machineDelay,0);
				}
			}
		}
	}
}

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


void mainLoop(int value){		//game main loop
	glutTimerFunc(20,mainLoop,0);	
	glutPostRedisplay();
}

void trocarEstado(int estado){
	switch(estado){
		case ESTADO_JOGANDO:
			glutDisplayFunc(drawGame);
			glutPassiveMotionFunc(hoverMouse);
			glutKeyboardFunc(keyboardIngame);	
			glutMouseFunc(doisJogadoresMouse);
		break;
		case ESTADO_VITORIA:
			glutDisplayFunc(drawVictory);
			glutPassiveMotionFunc(hoverMouse);
			glutKeyboardFunc(keyboardVictory);
			glutMouseFunc(NULL);
		break;
		case ESTADO_MENU_PRINCIPAL:
			selecionarMenu(menu_principal);
			glutDisplayFunc(desenhaMenu);
			glutPassiveMotionFunc(menuHover);
			glutKeyboardFunc(NULL);
			glutMouseFunc(menuClick);
		break;
		case ESTADO_CREDITOS:
			esvaziaTabuleiro();
			glutDisplayFunc(desenhaCreditos);
			glutPassiveMotionFunc(NULL);
			glutKeyboardFunc(keyboardVictory);
			glutMouseFunc(NULL);
		break;
		case ESTADO_MENU_PAUSA:
			selecionarMenu(menu_pausa);
			glutDisplayFunc(desenhaMenu);
			glutPassiveMotionFunc(menuHover);
			glutKeyboardFunc(keyboardPause);
			glutMouseFunc(menuClick);
		break;
		case ESTADO_MENU_AI:
			selecionarMenu(menu_ai);
			glutDisplayFunc(desenhaMenu);
			glutPassiveMotionFunc(menuHover);
			glutKeyboardFunc(keyboardVictory);
			glutMouseFunc(menuClick);
		break;
		case ESTADO_SPLASH:
			glutDisplayFunc(desenhaSplash);
			
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

void iniciarPartidaHumanoHumano(int parametro){
	jogador_maquina=VAZIO;
	esvaziaTabuleiro();
	trocarJogador();
	trocarEstado(ESTADO_JOGANDO);
}
void inciarPartidaHumanoMaquina(int dificuldade){
	switch(dificuldade){
		case 1: iniciarAi(RUSH_PLAY);
		break;
		case 2: iniciarAi(RUSH_PLAY | VALORIZAR_BORDAS);
		break;
		case 3: iniciarAi(MINIMAX_PLAY | 4);
		break;
		case 4: iniciarAi(MINIMAX_PLAY | 6 | VALORIZAR_BORDAS);
		break;
		case 5: iniciarAi(MINIMAX_PLAY | 8 | VALORIZAR_BORDAS);
	}
	jogador_ativo=BRANCO;
	jogador_maquina=PRETO;
	
	esvaziaTabuleiro();
	trocarJogador();
	trocarEstado(ESTADO_JOGANDO);
}
void quitar(int parametro){
	trocarEstado(ESTADO_SPLASH);
	splashReverso();
	destruirMenu();
	puts("obrigado por jogar");
}

//- inicializa a SDL e SDL_Mix
void initSom(){
	SDL_Init(SDL_INIT_AUDIO);
	Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096);
}

void carregarSom(){
	musica_fundo = Mix_LoadMUS("resources/theme.wav");
}

void fecharMixer(){
	Mix_FreeMusic(musica_fundo);
	Mix_CloseAudio();
	SDL_Quit();
}

int main(int argc, char **argv){
	inicializaGl(argc, argv);
	trocarEstado(ESTADO_SPLASH);
	initSplash(CAMINHO_TEXTURA_SPLASH, trocarEstado, ESTADO_MENU_PRINCIPAL, exit, 0);
	splash(1);
	
	iniciarMenu(XMAX,YMAX);
	iniciarAi(MINIMAX_PLAY | 4 | VALORIZAR_BORDAS);
	menu_principal = novoMenu(CAMINHO_TEXTURA_MENU);
	selecionarMenu(menu_principal);
	adicionarBotao("Humano vs Humano", 40,20,36,5,iniciarPartidaHumanoHumano,0);
	adicionarBotao("Humano vs Maquina", 40,20,44,5,trocarEstado,ESTADO_MENU_AI);
	adicionarBotao("Creditos", 40,20,52,5,trocarEstado,ESTADO_CREDITOS);
	adicionarBotao("Sair", 40,20,60,5,quitar,0);
	menu_pausa = novoMenu(CAMINHO_TEXTURA_MENU);
	selecionarMenu(menu_pausa);
	adicionarTexto("JOGO PAUSADO", 50, 10);
	adicionarBotao("Retornar ao jogo", 40,20,28,5,trocarEstado,ESTADO_JOGANDO);
	adicionarBotao("Menu principal", 40,20,36,5,trocarEstado,ESTADO_MENU_PRINCIPAL);
	adicionarBotao("Sair", 40,20,44,5,quitar,0);
	menu_ai = novoMenu(CAMINHO_TEXTURA_MENU);
	selecionarMenu(menu_ai);
	adicionarTexto("Seletor de dificuldade", 50, 10);
	adicionarBotao("1", 5,14,28,7,inciarPartidaHumanoMaquina,1);
	adicionarBotao("2", 24,14,28,7,inciarPartidaHumanoMaquina,2);
	adicionarBotao("3", 43,14,28,7,inciarPartidaHumanoMaquina,3);
	adicionarBotao("4", 62,14,28,7,inciarPartidaHumanoMaquina,4);
	adicionarBotao("5", 81,14,28,7,inciarPartidaHumanoMaquina,5);
	adicionarBotao("Menu principal", 40,20,38,5,trocarEstado,ESTADO_MENU_PRINCIPAL);
	adicionarBotao("Sair", 40,20,46,5,quitar,0);
	
	
	mainLoop(0);
	initSom();
	carregarSom();
	Mix_PlayMusic(musica_fundo, -1);
	glutMainLoop();
	fecharMixer();
	return 0;
}
