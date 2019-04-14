CC = gcc
CFLAG = -std=c99
OBJS = main.o elf_head.o

all: my_readelf

my_readelf: $(OBJS)
	$(CC) -o my_readelf $^

%.o: %.c
	gcc -c -o $@ $< $(CFLAG)

clean:
	rm -f *.o my_readelf
