#include "splash.h"

#define N_TELAS_SPLASH 5
#define TEMPO_SPLASH 3000

GLuint frames_splash[N_TELAS_SPLASH];
void (*endSplashFunc)(int);
void (*beginSplashFunc)(int);
int end_splash_arg;
int begin_splash_arg;

void initSplash(const char **CAMINHO_TEXTURA, void (*onBegin)(int), int argb, void (*onEnd)(int), int arge){
	endSplashFunc = onEnd;
	beginSplashFunc = onBegin;
	begin_splash_arg = argb;
	end_splash_arg = arge;
	int i;
	unsigned int tamanho_parcial = strlen(CAMINHO_TEXTURA[0]);
	char caminho[tamanho_parcial + strlen(CAMINHO_TEXTURA[0])+2]; //2: um digito e '\0'
	strcpy(caminho, CAMINHO_TEXTURA[0]);
	strcat(caminho, "X");
	strcat(caminho, CAMINHO_TEXTURA[1]);
	for(i=0;i<N_TELAS_SPLASH;i++){
		caminho[tamanho_parcial] = i+'0';
		frames_splash[i] = carregarTextura((const char*)caminho);
	}
	
}

int textura_atual;
void desenhaSplash(){
	glClear(GL_COLOR_BUFFER_BIT);
	desenhaTextura(frames_splash[textura_atual]);
	glFlush();
}

void passar_textura(int direcao){
	if(direcao>0){
		if(textura_atual < N_TELAS_SPLASH-1){
			++textura_atual;
		} else {
			beginSplashFunc(begin_splash_arg);
			return;
		}
	} else {
		if(textura_atual > 0){
			--textura_atual;
		} else {
			endSplashFunc(end_splash_arg);
			return;
		}
	}
	glutTimerFunc(TEMPO_SPLASH/N_TELAS_SPLASH, passar_textura, direcao);
}

void splash(){
	textura_atual=0;
	passar_textura(1);
}

void splashReverso(){
	textura_atual=N_TELAS_SPLASH-1;
	passar_textura(-1);
}

