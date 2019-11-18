CC=g++
CFLAGS=-std=c++11 -Wall

bms:
	$(CC) $(CFLAGS) bms.cpp dmx.cpp -o bms1

clean:
	rm *.o	bms1