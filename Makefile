ODIR=.
LDIR =./lib
IDIR =./include
CC=g++
CFLAGS= -g -Wall -I$(IDIR)

_DEPS = cIndex.h
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ = main.o cIndex.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

target = main

$(target): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^

$(ODIR)/%.o: %.cpp $(DEPS)
	$(CC) $(CFLAGS) -c -o $@ $<

.PHONY: clean

clean:
	rm -f $(ODIR)/*.o *~ $(INCDIR)/*~ $(target)
