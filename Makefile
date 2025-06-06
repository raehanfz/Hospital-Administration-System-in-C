CFLAGS = -Iinclude -Wall -Wextra -g
SRCS = testing.c src/dokter.c src/jadwal.c
OBJ = $(SRCS:.c=.o)
EXEC = testing

all: $(EXEC)

$(EXEC): $(OBJ)
	gcc $(OBJ) -o $@

%.o: %.c
	gcc $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(EXEC)

run: $(EXEC)
	./$(EXEC)

.PHONY: all clean run
