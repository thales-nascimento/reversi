#include "graficos.h"
#include <stdio.h>

#define COR_BRANCO 224
#define COR_PRETO 31

void desenhaTabuleiro(){
	int i,j;
	char comutador=0;
	
	glBegin(GL_QUADS);
		for(i=0;i<LADO_TABULEIRO;++i){
			for(j=0;j<LADO_TABULEIRO;j++){
				unsigned char green=0, red=0;
				if(tabuleiro[i][j] & HOVER){
					green = 32;
				}
				if(tabuleiro[i][j] & ATIVO){
					red = 48;
				}
				
				if(comutador){
					glColor3ub(63+red,63+green,63);
				} else {
					glColor3ub(127+red,127+green,63);
				}
				comutador=!comutador;
				
				glVertex2i(LADO_CASA/2 + (j+1)*LADO_CASA, LADO_CASA/2 + i*LADO_CASA);
				glVertex2i(LADO_CASA/2 + j*LADO_CASA, LADO_CASA/2 + i*LADO_CASA);
				glVertex2i(LADO_CASA/2 + j*LADO_CASA, LADO_CASA/2 + (i+1)*LADO_CASA);
				glVertex2i(LADO_CASA/2 + (j+1)*LADO_CASA, LADO_CASA/2 + (i+1)*LADO_CASA);
			}
			comutador=!comutador;
		}
	glEnd();
	
	for(i=0;i<LADO_TABULEIRO;++i){
		for(j=0;j<LADO_TABULEIRO;j++){
			if(tabuleiro[i][j] & VAZIO){
				continue;
			}else if(tabuleiro[i][j] & PRETO){
				if(tabuleiro[i][j] & TRANSICAO){
					int cinza = COR_PRETO + (COR_BRANCO-COR_PRETO)*(tabuleiro[i][j] & TRANSICAO)/(TRANSICAO+1);
					glColor3ub(cinza,cinza,cinza);
					tabuleiro[i][j] -= TRANSITAR;
				} else {
					glColor3ub(COR_PRETO,COR_PRETO,COR_PRETO);
				}
			} else if(tabuleiro[i][j] & BRANCO){
				if(tabuleiro[i][j] & TRANSICAO){
					int cinza = COR_BRANCO - (COR_BRANCO-COR_PRETO)*(tabuleiro[i][j] & TRANSICAO)/(TRANSICAO+1);
					glColor3ub(cinza,cinza,cinza);
					tabuleiro[i][j] -= TRANSITAR;
				} else {
					glColor3ub(COR_BRANCO,COR_BRANCO,COR_BRANCO);
				}
			}
			
			int a;
			float vertex_angle;
			float x = + (j+1)*LADO_CASA;
			float y = + (i+1)*LADO_CASA;
			const float R = LADO_CASA*3/8;
			const int NUM_VERTEX=20;
			glBegin(GL_POLYGON);
				for(a=0;a<NUM_VERTEX;a++){
					vertex_angle = 2*a*M_PI/NUM_VERTEX;
					glVertex2d(x+R*cos(vertex_angle), y+R*sin(vertex_angle));
				}	
			glEnd();			
		}
	}
}

void desenhaPontuacao(int jogador_ativo){
	char pretos[12], brancos[14];
	sprintf(pretos, "pretos: %d", pontuacao.preto);
	sprintf(brancos, "brancos: %d", pontuacao.branco);
	glColor3ub(224,224,244);
	glRasterPos2i((1+LADO_TABULEIRO)*LADO_CASA, LADO_CASA);
	int i=0;
	for(i=0;i<strlen(pretos);i++){
		glutBitmapCharacter(GLUT_BITMAP_9_BY_15, pretos[i]);
	}
	glRasterPos2i((1+LADO_TABULEIRO)*LADO_CASA, LADO_CASA-16);
	for(i=0;i<strlen(brancos);i++){
		glutBitmapCharacter(GLUT_BITMAP_9_BY_15, brancos[i]);
	}
	
	char jogador_preto[] = "preto";
	char jogador_branco[] = "branco";
	char* jogador;
	if(jogador_ativo == BRANCO)jogador=jogador_branco;
	else jogador=jogador_preto;
	glRasterPos2i((1+LADO_TABULEIRO)*LADO_CASA, LADO_CASA+32);
	for(i=0;i<strlen(jogador);i++){
		glutBitmapCharacter(GLUT_BITMAP_9_BY_15, jogador[i]);
	}
}

void popup(const char *texto){
	const int x=3*YMAX/8,w=YMAX/4,y=3*YMAX/8,h=YMAX/4;
	glColor3ub(63,127,63);
	glBegin(GL_QUADS);
		glVertex2i(x,y);
		glVertex2i(x,y+h);
		glVertex2i(x+w,y+h);
		glVertex2i(x+w,y);
	glEnd();
	
	int linha=2;
	int coluna=4;
	int i;
	glColor3ub(255,255,255);
	for(i=0;i<strlen(texto);++i){
		glRasterPos2i(x+coluna*9, y+linha*15);
		if(texto[i] == '\n'){
			++linha;
			coluna=4;
		} else {	
			glutBitmapCharacter(GLUT_BITMAP_9_BY_15, texto[i]);
			coluna++;
			if((coluna+4)*9 >= w){
				++linha;
				coluna=4;
			}
		}
	}
}

GLuint carregarTextura(const char *CAMINHO){
    GLuint textura = SOIL_load_OGL_texture(
        CAMINHO,
        SOIL_LOAD_AUTO,
        SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS
	);
    if (textura == 0) {
        printf("Erro do SOIL: '%s'\n", SOIL_last_result());
        exit(1);
    }
    return textura;
}

void desenhaTextura(GLuint textura){
	
    glColor3f(1, 1, 1);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, textura);
    glBegin(GL_QUADS);
        // Associamos um canto da textura para cada vértice
        glTexCoord2f(0, 0); glVertex2d(0,0);
        glTexCoord2f(0, 1); glVertex2d(0,YMAX);
        glTexCoord2f(1, 1); glVertex2d(XMAX,YMAX);
        glTexCoord2f(1, 0); glVertex2d(XMAX,0);
    glEnd();
    glDisable(GL_TEXTURE_2D);
    
}

