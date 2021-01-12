CC = gcc -c -g
GL = -lglut -lGL -lGLU
FD = form/
GD = graphicsSource/

PoopGuy: main.o libgraphics.a
	gcc -o PoopGuy main.o libgraphics.a $(GL)

main.o: main.c
	$(CC) -Wextra -Wall main.c

libgraphics.a: FormGraphics.o
	ar rs libgraphics.a FormGraphics.o

FormGraphics.o: $(FD)FormGraphics.c $(FD)FormGraphics.h $(GD)Graphics.c $(GD)Graphics.h $(FD)Form.c $(FD)Form.h
	$(CC) $(FD)FormGraphics.c $(GL)

clean:
	rm *.o *.a

fclean:
	rm *.o *.a
	rm PoopGuy
