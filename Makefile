CC = gcc -c -g
GL = -lglut -lGL -lGLU
FD = form/
GD = graphicsSource/

PoopGuy: main.o libform.a
	gcc -o PoopGuy main.o libform.a $(GL)

main.o: main.c
	$(CC) -Wextra -Wall main.c

libform.a: Form.o Graphics.o
	ar rs libform.a Form.o Graphics.o

Form.o: $(FD)FormGraphics.c $(FD)FormGraphics.h $(FD)Form.c $(FD)Form.h
	$(CC) $(FD)Form.c $(GL)

Graphics.o: $(GD)Graphics.c $(GD)Graphics.h
	$(CC) $(GD)Graphics.c $(GL)

clean:
	rm *.o *.a

fclean:
	rm *.o *.a
	rm PoopGuy
