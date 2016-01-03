CC=gcc
CFLAGS=-O3 -Wall
LIBS=-lopencv_core -lopencv_highgui -lopencv_imgproc

captcha3d: main.o zbuffer.o illumination.o transformations.o param.o
	g++ $(CFLAGS) main.o zbuffer.o illumination.o transformations.o param.o $(LIBS) -lm -o ../bin/captcha3d

main.o: main.c main.h zbuffer.h data.h param.h
	$(CC) $(CFLAGS) -o main.o -c main.c

zbuffer.o: zbuffer.c zbuffer.h illumination.h transformations.h data.h
	$(CC) $(CFLAGS) -o zbuffer.o -c zbuffer.c 

illumination.o: illumination.c illumination.h data.h
	$(CC) $(CFLAGS) -o illumination.o -c illumination.c

transformations.o: transformations.c transformations.h data.h
	$(CC) $(CFLAGS) -o transformations.o -c transformations.c
	
param.o: param.c param.h data.h
	$(CC) $(CFLAGS) param.c -o param.o -c

clean:
	rm *.o
