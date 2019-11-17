CC=g++
CFLAGS=-std=c++11 -Wall

bms: bms1
	$(CC) $(CFLAGS) bms.cpp dmx.cpp -o bms1

clean:
	rm *.o	