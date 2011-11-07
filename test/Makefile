CC = g++ -O3
LD = g++

GENHEADERS = ../src/myrng.h RNGTests.h
GENSOURCES = 
GENFILES = $(GENHEADERS) $(GENSOURCES)

MTHEADERS = ../src/MTEngine.h ../src/myrngMT.h
MTSOURCES = ../src/MTEngine.cpp  ../src/myrngMT.cpp
MTFILES = $(GENFILES) $(MTHEADERS) $(MTSOURCES)

WELLHEADERS = ../src/WELLEngine.h ../src/myrngWELL.h
WELLSOURCES = ../src/WELLEngine.cpp  ../src/myrngWELL.cpp
WELLFILES = $(GENFILES) $(WELLHEADERS) $(WELLSOURCES)

MTOBJS = testMT.o myrngMT.o MTEngine.o
WELLOBJS = testWELL.o myrngWELL.o WELLEngine.o
OBJS = $(MTOBJS) $(WELLOBJS)

all: test

test: testWELL testMT
	
testWELL: $(WELLOBJS)
	$(LD) -o testWELL $(WELLOBJS)

testMT: $(MTOBJS)
	$(LD) -o testMT $(MTOBJS)

testMT.o: testMT.cpp $(MTFILES)
	$(CC) -O3 -c testMT.cpp

testWELL.o: testWELL.cpp $(WELLFILES)
	$(CC) -O3 -c testWELL.cpp

myrngWELL.o WELLEngine.o: $(WELLFILES)
	$(CC) -O3 -c $(WELLSOURCES)

myrngMT.o MTEngine.o: $(MTFILES)
	$(CC) -O3 -c $(MTSOURCES)

clean:
	rm *.o testWELL testMT
