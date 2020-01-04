FROM gcc:4.9
WORKDIR /app
COPY . .
RUN make
CMD ["./histogram", "input_files/input.txt"]
