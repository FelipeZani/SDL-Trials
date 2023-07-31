CC = g++
CFLAGS = -I$(IDIR)
LDFLAGS = -L./include/lib -lSDL2 -lSDL2_ttf -lSDL2_image
IDIR = ./include/headers/%.h
SRCDIR = ./src/

SOURCES = $(wildcard $(SRCDIR)*.cpp)

all: main

main: $(SOURCES)
	$(CC) $(SOURCES) $(CFLAGS) $(LDFLAGS) -o $@

run:
	./main
clean:
	rm main