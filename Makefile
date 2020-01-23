CC=gcc
CFLAGS=-Wall -g

all: beam

beam: beam.o client.o server.o assets.o
	$(CC) $(CFLAGS) beam.o client.o server.o assets.o -o beam

#beam.o: beam.c
#	$(CC) $(CFLAGS) -c beam.c

#server.o: server.c
#	$(CC) $(CFLAGS) -c server.c

#client.o: client.c
#	$(CC) $(CFLAGS) -c client.c

#assets.o: assets.c
#	$(CC) $(CFLAGS) -c assets.c

#Automatic Variables
%.o: %.c
	$(CC) $(CFLAGS) -c $^

clean:
	rm *.o beam
