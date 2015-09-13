#include "menu.h"

unsigned int n_botoes=0;
Botao *botoes = NULL;
unsigned int n_textos=0;
Texto *textos = NULL;
unsigned int n_menus=0;
unsigned int menu_ativo=0;
Menu *menus = NULL;

int MXMAX=0,MYMAX=0;

void iniciarMenu(const int _XMAX,const int _YMAX){
	MYMAX=_YMAX;
	MXMAX=_XMAX;
}

int novoMenu(){
	++n_menus;
	menus = realloc(menus, sizeof(Menu)*n_menus);
	return n_menus-1;
}
void selecionarMenu(int menu){
	menus[menu_ativo].botoes=botoes;
	menus[menu_ativo].textos=textos;
	menus[menu_ativo].n_botoes=n_botoes;
	menus[menu_ativo].n_textos=n_textos;
	menu_ativo=menu;
	if(menu>n_menus || n_menus==0){
		puts("indice de menu inexistente");
		puts("erro disparado por trocarMenu(int)");
		exit(1);
	}
	botoes=menus[menu].botoes;
	textos=menus[menu].textos;
	n_botoes=menus[menu].n_botoes;
	n_textos=menus[menu].n_textos;
}

void adicionarTexto(char* texto, float x, float y){
	++n_textos;
	textos = realloc(textos, sizeof(Texto)*n_textos);
	textos[n_textos-1].x = x*MXMAX/100;
	textos[n_textos-1].y = y*MYMAX/100;
	textos[n_textos-1].offset_texto_x = -(strlen(texto)*FONTE_LARGURA)/2;
	textos[n_textos-1].offset_texto_y = -(FONTE_ALTURA)/2;
	textos[n_textos-1].texto = texto;
}

void adicionarBotao(char* texto, float x, float w, float y, float h, void (*funcao)()){
	++n_botoes;
	botoes = realloc(botoes, sizeof(Botao)*n_botoes);
	
	if(x>100 || y> 100 || w> 100 || h > 100){
		if(x>100)puts("aviso: valor x do menu é maior que 100%");
		if(y>100)puts("aviso: valor y do menu é maior que 100%");
		if(w>100)puts("aviso: valor w do menu é maior que 100%");
		if(h>100)puts("aviso: valor h do menu é maior que 100%");
		puts("erro disparado em adicionarBotao(char*,float,float,float,float,void(*)");
		exit(1);
	}
	botoes[n_botoes-1].x = x*MXMAX/100;
	botoes[n_botoes-1].y = y*MYMAX/100;
	botoes[n_botoes-1].w = w*MXMAX/100;
	botoes[n_botoes-1].h = h*MYMAX/100;
	botoes[n_botoes-1].funcao=funcao;
	botoes[n_botoes-1].texto=texto;
	botoes[n_botoes-1].offset_texto_x = (botoes[n_botoes-1].w - strlen(texto)*FONTE_LARGURA)/2;
	botoes[n_botoes-1].offset_texto_y = (botoes[n_botoes-1].h + FONTE_ALTURA)/2;
	botoes[n_botoes-1].estado = BOTAO_NORMAL;
}

void desenhaMenu(){
	glClear(GL_COLOR_BUFFER_BIT);
	
	int i,j;
	for(i=0;i<n_textos;++i){
		glColor3ub(255,255,255);
		glRasterPos2i(textos[i].x +textos[i].offset_texto_x, textos[i].y +textos[i].offset_texto_y);
		for(j=0;j<strlen(textos[i].texto);++j){
			glutBitmapCharacter(GLUT_BITMAP_9_BY_15, textos[i].texto[j]);
		}
	}
	
	for(i=0;i<n_botoes;++i){
		if(botoes[i].estado==BOTAO_CLICK){
			glColor3ub(127,127,63);
		} else if(botoes[i].estado==BOTAO_HOVER){
			glColor3ub(63,127,63);
		} else {
			glColor3ub(63,63,63);
		}
		glBegin(GL_QUADS);
			glVertex2i(botoes[i].x,botoes[i].y);
			glVertex2i(botoes[i].x,botoes[i].y+botoes[i].h);
			glVertex2i(botoes[i].x+botoes[i].w,botoes[i].y+botoes[i].h);
			glVertex2i(botoes[i].x+botoes[i].w,botoes[i].y);
		glEnd();
		
		glColor3ub(255,255,255);
		glRasterPos2i(botoes[i].x +botoes[i].offset_texto_x, botoes[i].y +botoes[i].offset_texto_y);
		for(j=0;j<strlen(botoes[i].texto);++j){
			glutBitmapCharacter(GLUT_BITMAP_9_BY_15, botoes[i].texto[j]);
			
		}
	}
	glFlush();
}

int intersectar(x,y){
	int i;
	for(i=0;i<n_botoes;i++){
		if(x>=botoes[i].x && x<= botoes[i].x+botoes[i].w){
			if(y>=botoes[i].y && y<=botoes[i].y+botoes[i].h){
				return i;
			}
		}
	}
	
	return i;
}

void menuClick(int key,int status,int x, int y){
	if(key != GLUT_LEFT_BUTTON)return;
	int i = intersectar(x,y);
	if(i != n_botoes){
		botoes[i].estado = BOTAO_CLICK;
		if(status == GLUT_UP){
			botoes[i].funcao();
			botoes[i].estado = BOTAO_NORMAL;
		}
	}
}
void menuHover(int x, int y){
	static int last_i=0;
	botoes[last_i].estado = BOTAO_NORMAL;
	
	int i = intersectar(x,y);
	if(i != n_botoes){
		last_i=i;
		botoes[i].estado = BOTAO_HOVER;
	}
	
}

void destruirMenu(){
	n_textos=n_botoes=n_menus=0;
	int i;
	for(i=0;i<n_menus;++i){
		selecionarMenu(i);
		free(textos);
		free(botoes);
	}
	free(menus);
}
