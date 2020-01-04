FROM gcc
WORKDIR /app
COPY . .
RUN make
CMD ["./histogram", "input_files/input.txt"]
