#ifndef __GRAFICOS_H__
#define __GRAFICOS_H__

#include "tabuleiro.h"
#include "soil/src/SOIL.h"
#include <string.h>
#include <math.h>
#include <GL/glut.h>

#define YMAX 600
#define XMAX 800

#define LADO_CASA (XMAX<YMAX?XMAX:YMAX)/(LADO_TABULEIRO+1)

GLuint carregarTextura(const char *caminho);
void desenhaTextura(GLuint textura);

void desenhaTabuleiro();
void desenhaPontuacao();
void popup(const char *texto);

#endif
