# Sistemas Operacionais - Trabalho 2
# Autor: Lucas Corrêa Macedo

CC=g++
CFLAGS=-Wall -std=c++11 -pthread
LD=g++
LFLAGS=-Wall -std=c++11 -pthread

EXECS = mandelbrot
OBJS = main.o Pixel.o Image.o

all: $(EXECS)

.cpp.o:
	$(CC) $(CFLAGS) -o $@ -c $<

$(EXECS): $(OBJS)
	$(LD) $(LFLAGS) -o $@ $(OBJS)

clean:
	rm -f $(EXECS) $(OBJS)
