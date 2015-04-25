overide CFLAGS+="-t -0"
CC=gcc $(CFLAGS)
OBJECTS=sync.o main.o

mylocks: $(OBJECTS) 
	$(CC) $(OBJECTS) -lpthread -o mylocks
clean:
	rm -f mylocks $(OBJECTS) 
run: mylocks
	./mylocks
