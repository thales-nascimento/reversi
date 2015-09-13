all: main.c tabuleiro.o graficos.o menu.o
	gcc -o tester tabuleiro.o graficos.o menu.o main.c -lm -lGL -lglut
	
menu.o: menu.c
	gcc -c -o menu.o menu.c
	
tabuleiro.o: tabuleiro.c
	gcc -c -o tabuleiro.o tabuleiro.c

graficos.o: graficos.c
	gcc -c -o graficos.o graficos.c

clean:
	rm *.o tester
