.PHONY: clean all run
.DEFAULT_GOAL := all

BIN_NAME=tetris

CC=g++

ODIR=obj
BDIR=bin

CFLAGS= -g
INCS=
LIBS=

SRCS=$(wildcard *.cpp)
OBJS=$(patsubst %.cpp,$(ODIR)/%.o,$(filter-out $(patsubst %,%.cpp,$(BIN_NAME)), $(SRCS)))
BINS=$(patsubst %,$(BDIR)/%,$(BIN_NAME))

.depend: $(SRCS)
	$(CC) $(CFLAGS) -MM $^ > ./.depend
	sed -i.bak -e 's/^/${ODIR}\//' ./.depend && rm ./.depend.bak

-include .depend

$(BDIR) $(ODIR):
	mkdir -p $@

$(ODIR)/%.o: %.cpp | $(ODIR)
	$(CC) -c -o $@ $< $(CFLAGS) $(INCS)

$(BINS): $(BDIR)/%: $(ODIR)/%.o $(OBJS) | $(BDIR)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

all: $(BINS)

clean:
	rm -rf $(ODIR) $(BDIR)
	rm -f .depend

run: $(BINS)
	./$(BDIR)/$(BIN_NAME)
