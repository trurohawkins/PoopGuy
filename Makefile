CC = gcc -c -g
GLW = -lglu32 -lopengl32 -lfreeglut
GLL = -lGL -lglut -lm
FD = form/
AD = actor/
ACD = $(AD)acts/
GD = graphicsSource/
HD = helper/

PoopGuy: main.o libform.a libglut.a
	gcc -o PoopGuy main.o libform.a libglut.a $(GLL)

windows: main.o libform.a libglut.a
	gcc -o PoopGuy main.o libform.a libglut.a $(GLW)

main.o: main.c FormGraphics.c FormGraphics.h
	$(CC) -Wextra -Wall main.c

libform.a: Form.o helper.o
	ar rs libform.a Form.o helper.o

Form.o:  $(FD)Form.c $(FD)Form.h $(FD)World.c $(FD)World.h $(AD)Action.c $(AD)Action.h $(AD)Actor.c $(AD)Actor.h $(AD)Player.h $(AD)Player.c $(AD)ActorList.h $(AD)ActorList.c $(ACD)actList.c $(ACD)actList.h $(ACD)gravity.c $(ACD)gravity.h $(ACD)jump.c $(ACD)jump.h $(ACD)eatPoop.h $(ACD)eatPoop.c $(ACD)control.c $(ACD)control.h
	$(CC) $(FD)Form.c 

libglut.a: Graphics.o GlutProcess.o
	ar rs libglut.a Graphics.o GlutProcess.o

GlutProcess.o: $(GD)GlutProcess.c $(GD)GlutProcess.h
	$(CC) $(GD)GlutProcess.c

Graphics.o: $(GD)Graphics.c $(GD)Graphics.h
	$(CC) $(GD)Graphics.c

helper.o: $(HD)helper.c $(HD)helper.h $(HD)list.c $(HD)list.h
	$(CC) $(HD)helper.c

clean:
	rm *.o *.a

fclean:
	rm *.o *.a
	rm PoopGuy

mclean:
	rm vgcore*
