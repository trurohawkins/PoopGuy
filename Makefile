CC = gcc -c -g
GLW = -lglu32 -lopengl32 -lfreeglut
GLL = -lGL -lglut -lGLU
FD = form/
AD = actor/
GD = graphicsSource/

PoopGuy: main.o libform.a
	gcc -o PoopGuy main.o libform.a $(GLL)

main.o: main.c
	$(CC) -Wextra -Wall main.c

libform.a: Form.o Graphics.o
	ar rs libform.a Form.o Graphics.o

Form.o: $(FD)FormGraphics.c $(FD)FormGraphics.h $(FD)Form.c $(FD)Form.h $(FD)World.c $(FD)World.h $(AD)Action.c $(AD)Action.h $(AD)Actor.c $(AD)Actor.h $(AD)aList.c $(AD)/acts/actList.c helper.c
	$(CC) $(FD)Form.c 

Graphics.o: $(GD)Graphics.c $(GD)Graphics.h
	$(CC) $(GD)Graphics.c

clean:
	rm *.o *.a

fclean:
	rm *.o *.a
	rm PoopGuy
