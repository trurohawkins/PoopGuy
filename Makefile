CC = gcc -c -g
GLW = -lglu32 -lopengl32 -lfreeglut
GLL = -lglfw -lGL -lGLEW -lglut -lm
GF = formglfw/
FD = form/
AD = actor/
ACD = $(AD)acts/
GD = graphics/
ID = $(GD)input/
SHD = $(GD)shaders/
HD = helper/

PoopGuy: main.o libFormGlfw.a
	gcc -o PoopGuy main.o libFormGlfw.a $(GLL)

windows: main.o libform.a libglut.a
	gcc -o PoopGuy main.o libform.a libglut.a $(GLW)

main.o: main.c
	$(CC) -Wextra -Wall main.c

libFormGlfw.a: FormGlfw.o Form.o helper.o glfwMain.o Shaders.o Input.o Anim.o
	ar rs libFormGlfw.a FormGlfw.o Form.o helper.o glfwMain.o Shaders.o Input.o Anim.o 

FormGlfw.o: $(GF)FormGlfw.c $(GF)FormGlfw.h $(GF)Player.c $(GF)Player.h $(GF)poopPlayer.c $(GF)poopPlayer.h $(GF)PlayerManager.h $(GF)PlayerManager.c
	$(CC) $(GF)FormGlfw.c

libform.a: Form.o helper.o
	ar rs libform.a Form.o helper.o

Form.o:  $(FD)Form.c $(FD)Form.h $(FD)World.c $(FD)World.h $(AD)Eco.c $(AD)Eco.h $(AD)Action.c $(AD)Action.h $(AD)Actor.c $(AD)Actor.h $(AD)PoopGuy.c $(AD)PoopGuy.h  $(AD)ActorList.h $(AD)ActorList.c $(ACD)actList.c $(ACD)actList.h $(ACD)gravity.c $(ACD)gravity.h $(ACD)jump.c $(ACD)jump.h $(ACD)eatPoop.h $(ACD)eatPoop.c $(ACD)control.c $(ACD)control.h $(FD)procGen.c $(FD)procGen.h $(FD)Value.h $(FD)Value.c
	$(CC) $(FD)Form.c 

libglfw.a: glfwMain.o Shaders.o Input.o Anim.o
	ar rs libglfw.a glfwMain.o Shaders.o Input.o Anim.o

glfwMain.o: $(GD)glfwMain.c $(GD)glfwMain.h
	$(CC) $(GD)glfwMain.c

Shaders.o: $(SHD)Shaders.c $(SHD)Shaders.h
	$(CC) $(SHD)Shaders.c

Graphics.o: $(GD)Graphics.c $(GD)Graphics.h
	$(CC) $(GD)Graphics.c

Anim.o: $(GD)Anim.c $(GD)Anim.h $(GD)AnimList.c $(GD)AnimList.h
	$(CC) $(GD)Anim.c

Input.o: $(ID)Input.c $(ID)Input.h $(ID)Joystick.c $(ID)Joystick.h
	${CC} ${ID}Input.c

helper.o: $(HD)helper.c $(HD)helper.h $(HD)list.c $(HD)list.h
	$(CC) $(HD)helper.c

clean:
	rm *.o *.a

fclean:
	rm *.o *.a
	rm PoopGuy

mclean:
	rm vgcore*
