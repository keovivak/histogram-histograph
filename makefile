CFLAGS = gcc -g
OBJ = wordcountfreq.o

# Automatic substitution using suffix rules to
# make .o files from either .c or .cpp files
%.o: %.c
	${CFLAGS} -c $< 

%.o: %.cpp
	${CFLAGS} -c $<

# Build program based on the required .o files

wordcount: ${OBJ}
	${CFLAGS} -o wordcountfreq ${OBJ}


clean:
	rm ${OBJ}
	rm wordcountfreq

