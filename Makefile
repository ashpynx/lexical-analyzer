CC = gcc 
CFLAGS = -Wall --std=c11 


ifeq ($(OS),Windows_NT)
		
		EXT = .exe
		RM = del /Q /F
else

		EXT = 
		RM = rm -rf


endif


ALLSRC= $(wildcard src/*.c)
HEADERS = $(wildcard src/*.h)


SRC = $(filter-out src/reader.c,$(ALLSRC))

all: lex$(EXT) reader$(EXT)

lex$(EXT) : $(SRC) $(HEADERS)
	$(CC) $(CFLAGS) -o lex$(EXT) $(SRC)

reader$(EXT) : $(SRC) $(HEADERS)
	$(CC) $(CFLAGS) -o reader$(EXT) src/reader.c src/token.c src/file.c 

clean :
	$(RM) lex$(EXT) reader$(EXT)
