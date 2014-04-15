IDIR = ./include
SDIR = ./src
ODIR = ./obj

CC = g++
CFLAGS = -lglut -lGL -lGLU -I$(IDIR)

_DEPS = GameObject.h
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ = main_feito.o GameObject.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

$(ODIR)/%.o: $(SDIR)/%.cpp $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

main_feito: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

.PHONY: clean

clean:
	rm -f $(ODIR)/*.o 
