OBJS=vector.o
BIN=vector

all: $(OBJS)
	$(CC) $(CFLAGS) $^ -o $(BIN)

clean:
	$(RM) $(OBJS) $(BIN)

proper: all
	$(RM) $(OBJS)
