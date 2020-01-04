CFLAGS = gcc -g
OBJ = histogram.o

# Automatic substitution using suffix rules to
# make .o files from either .c or .cpp files
%.o: %.c
	${CFLAGS} -c $< 

%.o: %.cpp
	${CFLAGS} -c $<

# Build program based on the required .o files

app: ${OBJ}
	${CFLAGS} -o histogram ${OBJ}

clean:
	rm ${OBJ}
	rm histogram

