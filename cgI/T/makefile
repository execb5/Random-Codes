IDIR = ./include
SDIR = ./src
ODIR = ./obj
LDIR = ./lib

CC = g++
CFLAGS = -Wall -lglut -lGL -lGLU -I$(IDIR) 

_DEPS = bibutil.h
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ = main.o bibutil.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

_LIB = libim_capture libjpeg-8b
LIB = $(patsubst %,$(LDIR)/%,$(_LIB))

$(ODIR)/%.o: $(SDIR)/%.cpp -l$(LDIR) $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

main: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

.PHONY: clean

clean:
	rm -f $(ODIR)/*.o 
	rm -f main
