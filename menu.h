#ifndef __MENU_H__
#define __MENU_H__

#include <stdio.h>
#include <string.h>
#include <GL/freeglut.h>

#define FONTE_LARGURA 9
#define FONTE_ALTURA 15

#define BOTAO_NORMAL 0
#define BOTAO_HOVER 1
#define BOTAO_CLICK 2

typedef struct{
	char* texto;
	int offset_texto_x;
	int offset_texto_y;
	int x,w;
	int y,h;
	void (*funcao)();
	int parametro;
	int estado;
}Botao;

typedef struct{
	char* texto;
	int x,y;
	int offset_texto_x;
	int offset_texto_y;
}Texto;

typedef struct{
	Botao *botoes;
	Texto *textos;
	unsigned int n_botoes,n_textos;
	GLuint textura;
}Menu;

void iniciarMenu(const int _XMAX, const int _YMAX);
int novoMenu(const char *CAMINHO_TEXTURA);
void selecionarMenu(int menu);
void adicionarTexto(char *texto, float x, float y);
void adicionarBotao(char *texto, float x, float w, float y, float h, void (*funcao)(int), int parametro);

void desenhaMenu();

void menuClick(int key,int status,int x, int y);
void menuHover(int x, int y);
//TODO: void menuKeyBoard( int key);


void destruirMenu();

#endif
