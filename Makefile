CC = gcc -c -g -I/usr/include/freetype2
LC = gcc -c -g 
WC = x86_64-w64-mingw32-gcc -c -g
RELEASELIBS = -l:libglfw3.a -lm -ldl -lpthread -l:libfreetype.a -l:libcglm.a
DEVLIBS = -lglfw -lGL -lm -ldl -lfreetype -lcglm
GLW = -lglfw3 -lopengl32 -lgdi32 
GF = formglfw/
FD = form/
AD = actor/
ACD = $(AD)acts/
GD = graphics/
ID = $(GD)input/
SHD = $(GD)shaders/
TD = $(GD)text/
HD = helper/

PoopGuy: main.o libFormGlfw.a glad.o
	gcc -o  PoopGuy main.o glad.o libFormGlfw.a  $(DEVLIBS)

standalone: main.o libFormGlfw.a glad.o
	gcc -o PoopGuy main.o glad.o libFormGlfw.a $(RELEASELIBS) 

windows: setWindows main.o libFormGlfw.a glad.o
	x86_64-w64-mingw32-gcc -o PoopGuy -static main.o glad.o libFormGlfw.a $(GLW)

setWindows:
	$(eval CC := $(WC))

whiteLayers: $(HD)ImageProcessor/main.c libglfw.a glad.o
	gcc -o $(HD)ImageProcessor/whiteLayers -g $(HD)ImageProcessor/main.c glad.o libglfw.a -lm -lglfw -lGL -ldl

main.o: main.c
	$(CC) -Wextra -Wall main.c -lcglm

libFormGlfw.a: FormGlfw.o Form.o helper.o glfwMain.o Shaders.o Input.o Anim.o Text.o Camera.o
	ar rs libFormGlfw.a FormGlfw.o Form.o helper.o glfwMain.o Shaders.o Input.o Anim.o Text.o Camera.o

FormGlfw.o: $(GF)FormGlfw.c $(GF)FormGlfw.h $(GF)Player.c $(GF)Player.h $(GF)poopPlayer.c $(GF)poopPlayer.h $(GF)PlayerManager.h $(GF)PlayerManager.c $(AD)Cloud.c $(AD)Cloud.h $(GF)DrawWorld.c $(GF)DrawWorld.h $(GF)WorldView.c $(GF)WorldView.h $(GF)god.h $(GF)god.c
	$(CC) -I/usr/include/freetype2 $(GF)FormGlfw.c

libform.a: Form.o helper.o
	ar rs libform.a Form.o helper.o

Form.o:  $(FD)Form.c $(FD)Form.h $(FD)World.c $(FD)World.h $(AD)Eco.c $(AD)Eco.h $(AD)Action.c $(AD)Action.h $(AD)Actor.c $(AD)Actor.h $(AD)PoopGuy.c $(AD)PoopGuy.h  $(AD)ActorList.h $(AD)ActorList.c $(ACD)actList.c $(ACD)actList.h $(ACD)gravity.c $(ACD)gravity.h $(ACD)jump.c $(ACD)jump.h $(ACD)eatPoop.h $(ACD)eatPoop.c $(ACD)control.c $(ACD)control.h $(FD)procGen.c $(FD)procGen.h $(FD)Value.h $(FD)Value.c $(FD)Cell.c $(FD)Cell.h $(FD)FormSpawner.h $(FD)FormSpawner.c
	$(CC) $(FD)Form.c 

libglfw.a: glfwMain.o Shaders.o Input.o Anim.o Text.o Camera.o
	ar rs libglfw.a glfwMain.o Shaders.o Input.o Anim.o Text.o Camera.o

glfwMain.o: $(GD)glfwMain.c $(GD)glfwMain.h $(SHD)glslLib.c 
	$(CC) $(GD)glfwMain.c

Shaders.o: $(SHD)Shaders.c $(SHD)Shaders.h 
	$(CC) $(SHD)Shaders.c

$(SHD)glslLib.c: $(SHD)matVS.glsl $(SHD)matFS.glsl $(SHD)textureVS.glsl $(SHD)textureFS.glsl $(SHD)singleTextureVS.glsl $(SHD)singleTextureFS.glsl $(SHD)textVS.glsl $(SHD)textFS.glsl
	cd $(SHD); ./glslToC glslLib.c matVS.glsl matFS.glsl textureVS.glsl textureFS.glsl singleTextureVS.glsl singleTextureFS.glsl textVS.glsl textFS.glsl

Graphics.o: $(GD)Graphics.c $(GD)Graphics.h
	$(CC) $(GD)Graphics.c

Anim.o: $(GD)Anim.c $(GD)Anim.h $(GD)AnimList.c $(GD)AnimList.h $(GD)TextureManager.c $(GD)TextureManager.h $(GD)UI.c $(GD)UI.h $(GD)Tile.c $(GD)Tile.h
	$(CC) $(GD)Anim.c

Text.o: $(TD)Text.c $(TD)Text.h $(TD)TextInput.c $(TD)TextInput.h
	$(CC) $(TD)Text.c -l:libfreetype.a -lcglm

Input.o: $(ID)Input.c $(ID)Input.h $(ID)Joystick.c $(ID)Joystick.h
	$(CC) $(ID)Input.c

Camera.o: $(GD)Camera.c $(GD)Camera.h
	$(CC) $(GD)Camera.c

glad.o: $(GD)glad.c $(GD)glad.h $(GD)khrplatform.h
	$(CC) $(GD)glad.c -ldl

helper.o: $(HD)helper.c $(HD)helper.h $(HD)list.c $(HD)list.h $(HD)binaryWriter.h $(HD)binaryWriter.c
	$(CC) $(HD)helper.c

clean:
	rm *.o *.a

fclean:
	rm *.o *.a
	rm PoopGuy*

mclean:
	rm vgcore*
