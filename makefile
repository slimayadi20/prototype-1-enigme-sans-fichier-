jeu:main.o 
	gcc main.o -o jeu -lm -ldl -lSDL -lSDL_image -lSDL_ttf -lSDL_mixer -g
main.o:main.c
	gcc -c main.c -g
enigme.o:enigme.c
	gcc -c enigme.c -g
