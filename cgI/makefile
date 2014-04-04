IDIR = ./include
SDIR = ./src
ODIR = ./obj

CC = g++
CFLAGS = -lglut -lGL -lGLU -I$(IDIR)

_DEPS = Instancia.h
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ = main_feito.o Instancia.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

$(ODIR)/%.o: $(SDIR)/%.cpp $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

main_feito: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

.PHONY: clean

clean:
	rm -f $(ODIR)/*.o 
