CC = gcc -c -g
GLW = -lglu32 -lopengl32 -lfreeglut
GLL = -lGL -lglut -lGLU -lm
FD = form/
AD = actor/
ACD = $(AD)acts/
GD = graphicsSource/
HD = helper/

PoopGuy: main.o libform.a
	gcc -o PoopGuy main.o libform.a $(GLL)

windows: main.o libform.a
	gcc -o PoopGuy main.o libform.a $(GLW)

main.o: main.c
	$(CC) -Wextra -Wall main.c

libform.a: Form.o Graphics.o helper.o
	ar rs libform.a Form.o Graphics.o helper.o

Form.o: $(FD)FormGraphics.c $(FD)FormGraphics.h $(FD)Form.c $(FD)Form.h $(FD)World.c $(FD)World.h $(AD)Action.c $(AD)Action.h $(AD)Actor.c $(AD)Actor.h $(AD)Player.h $(AD)Player.c $(AD)ActorList.h $(AD)ActorList.c $(ACD)actList.c $(ACD)actList.h $(ACD)gravity.c $(ACD)gravity.h $(ACD)jump.c $(ACD)jump.h $(ACD)eatPoop.h $(ACD)eatPoop.c $(ACD)control.c $(ACD)control.h
	$(CC) $(FD)Form.c 

Graphics.o: $(GD)Graphics.c $(GD)Graphics.h
	$(CC) $(GD)Graphics.c

helper.o: $(HD)helper.c $(HD)helper.h $(HD)list.c $(HD)list.h
	$(CC) $(HD)helper.c

clean:
	rm *.o *.a

fclean:
	rm *.o *.a
	rm PoopGuy
