FROM gcc:4.9
COPY /src /usr/src/myapp
WORKDIR /usr/src/myapp
RUN gcc -o myapp wordcountfreq.c
CMD ["./myapp", "pangrams1.txt"]
