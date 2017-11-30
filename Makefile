OBJS = main.c

CC = gcc

LINKER_FLAGS = -lSDL2

OBJ_NAME = StackAttack

all: $(OBJS)
	$(CC) $(OBJS) $(LINKER_FLAGS) -o $(OBJ_NAME)
