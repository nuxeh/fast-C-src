CC=gcc
CFLAGS=-O3
TARGETS=fast_detect
SRCS=fast_detect.c \
	fast.c \
	fast_9.c \
	fast_10.c \
	fast_11.c \
	fast_12.c \
	nonmax.c

all: $(TARGETS)

fast_detect: $(SRCS)
	$(CC) $(CFLAGS) $(SRCS) -o $@

clean:
	rm -rf *.o $(TARGETS)
