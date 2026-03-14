CC = gcc 

CFLAGS = -Wall -Wall --std=c11

SRC= $(wildcard src/*.c)

OUT= lex

$(OUT) : $(SRC)
	$(CC) $(CFLAGS) -o $(OUT) $(SRC)
	

clean :
	rm -rf $(OUT)
