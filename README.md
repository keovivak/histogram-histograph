# histogram-histograph

To run program:

```
$ gcc -o histogram histogram.c
$ ./histogram <filename>
```
or
```
$ make
$ ./histogram <filename>
```

If you have docker available:

```
$ docker build -t histogram:v1
$ docker run -it histogram:v1
```
or if you want to specify a different file in the same directory
```
$ docker run -it histogram:v1 ./histogram <filename>
```

alternatively if you want to run it but don't want to change default input file
```
$ docker-compose up
```



