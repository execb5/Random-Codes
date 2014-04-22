IDIR = ./include
SDIR = ./src
ODIR = ./obj

CC = g++
CFLAGS = -lglut -lGL -lGLU -I$(IDIR)

_DEPS = GameObject.h Enemy.h MrTetragon.h Plataform.h Goal.h
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ = main.o GameObject.o Enemy.o MrTetragon.o Plataform.o Goal.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

$(ODIR)/%.o: $(SDIR)/%.cpp $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

main: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

.PHONY: clean

clean:
	rm -f $(ODIR)/*.o 
