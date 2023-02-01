CC=g++
CFLAGS=-O3 -Wall -Wpedantic
LDFLAGS= -lSDL2 -lSDL2_image -lSDL2_ttf

SOURCES=src/core/checkcrossing.cpp src/core/core.cpp src/core/rand.cpp $\
	src/types/alienabc.cpp $\
	src/types/alien.cpp $\
	src/types/alienlazer.cpp $\
	src/types/alienstorage.cpp $\
	src/types/arrstorageabc.cpp $\
	src/types/baselazer.cpp $\
	src/types/borderclass.cpp $\
	src/types/complexobject.cpp $\
	src/types/diecomplex.cpp $\
	src/types/dieobject.cpp $\
	src/types/elementaryobject.cpp $\
	src/types/engine_.cpp $\
	src/types/firstfleet.cpp $\
	src/types/gameclass.cpp $\
	src/types/gamefleetabc.cpp $\
	src/types/gameInfoClass.cpp $\
	src/types/gui.cpp $\
	src/types/herolazer.cpp $\
	src/types/herolazerstorage.cpp $\
	src/types/nhero.cpp $\
	src/types/partone.cpp $\
	src/types/sdlclass.cpp $\
	src/types/sdltypes.cpp $\
	src/types/skyclass.cpp $\
	src/types/texturescollection_load.cpp $\
	src/types/texturescollection.cpp $\
	src/main.cpp
OBJECTS=$(SOURCES:.cpp=.o) 
EXECUTABLE=prog

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(OBJECTS) $(LDFLAGS)  -o $@

.cpp.o:
	$(CC) $(CFLAGS)  -c -o $@ $<

clean:
	rm -rf src/core/*.o src/types/*.o prog