#ifndef __SPLASH_H__
#define __SPLASH_H__
#include <string.h>
#include "graficos.h"


void initSplash(const char **CAMINHO_TEXTURA, void (*onBegin)(int), int argb, void (*onEnd)(int), int arge);
void desenhaSplash();


void splash();
void splashReverso();

#endif
