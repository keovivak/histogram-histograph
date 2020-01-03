FROM gcc:4.9
WORKDIR /myapp
COPY . .
RUN gcc -o myapp wordcountfreq.c
CMD ["./myapp", "pangrams1.txt"]
