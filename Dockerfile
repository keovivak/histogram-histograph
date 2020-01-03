FROM gcc:4.9
WORKDIR /app
COPY . .
#RUN gcc -o histogram histogram.c
RUN make
CMD ["./histogram", "input_files/pangrams1.txt"]
