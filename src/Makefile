CFLAGS	= -std=c99 -Wall -Wextra -O3
LDFLAGS	=
LIBS	=

mus2mid: main.c mus2mid.c
	gcc $(CFLAGS) $(LDFLAGS) -o $@ $^ $(LIBS)

clean:
	rm -f mus2mid
