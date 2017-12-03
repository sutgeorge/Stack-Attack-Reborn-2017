OBJS = src/main.c src/player.c src/crane.c

CC = gcc

LINKER_FLAGS = -lSDL2 -lSDL2_image

OBJ_NAME = StackAttack

all: $(OBJS)
	$(CC) $(OBJS) $(LINKER_FLAGS) -o $(OBJ_NAME)
