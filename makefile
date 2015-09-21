all: main.c minimax.o tabuleiro.o graficos.o menu.o splash.o
	gcc -O3 -Wall -o tester tabuleiro.o graficos.o menu.o minimax.o splash.o main.c -lm -lGL -lglut -lSDL -lSOIL -lSDL_mixer
	
menu.o: menu.c
	gcc -c -o menu.o menu.c
	
tabuleiro.o: tabuleiro.c
	gcc -c -o tabuleiro.o tabuleiro.c

graficos.o: graficos.c
	gcc -c -o graficos.o graficos.c

minimax.o: minimax.c
	gcc -c -o minimax.o minimax.c

splash.o: splash.c
	gcc -c -o splash.o splash.c

clean:
	rm *.o tester
