#ifndef __GRAFICOS_H__
#define __GRAFICOS_H__

#include <string.h>
#include <math.h>
#include <GL/glut.h>
#include "tabuleiro.h"

#define YMAX 600
#define XMAX 800

#define LADO_CASA (XMAX<YMAX?XMAX:YMAX)/(LADO_TABULEIRO+1)



void desenhaTabuleiro();
void desenhaPontuacao();
void popup(const char *texto);

#endif
