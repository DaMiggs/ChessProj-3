CC = gcc
CFLAGS = -I. -g -w
DEPS = chess.h
OBJ = chess.o move.o show.o capture.o

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

chess: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

clean:
		rm -rf chess
		rm -rf *.o
		
x:
		make
		./chess -r -i d2d4,d7d5,e2e4,d5xe4,Ng1h3,Ke8d7,Qd1d3 -w miguel -b mike
exec:
		./chess