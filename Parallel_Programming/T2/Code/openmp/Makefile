CC = gcc
CCFLAGS = -Wall
LDFLAGS = -fopenmp
TARGET = ompsimple openmp_dot_prod

%.o: %.c
	$(CC) $(CCFLAGS) -c $<

%: %.o
	$(CC) $(LDFLAGS) $^ -o $@

all: $(TARGET)

# Dependencias

openmp_dot_prod: openmp_dot_prod.c
ompsimple: ompsimple.c

clean:
	rm -f *.o *~ $(TARGET)
