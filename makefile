

CC = g++
CFLAGS = -g
DEPS = MainDriver.o Huffman.o frequencycounter.o Node.o 

Huffman: $(DEPS)
	$(CC) $(CFLAGS) -o $@ $(DEPS)

MainDriver.o: main.cpp
	$(CC) $(CFLAGS) -c -o $@ $<

#General rule for all other files with header to generate 
%.o: %.cpp %.h
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -rf *.o compressor
