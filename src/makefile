captcha3d: main.o zbuffer.o illumination.o transformations.o param.o
	gcc -Wall main.o zbuffer.o illumination.o transformations.o param.o -lcv -lhighgui -lm -o ../bin/captcha3d -O2

main.o: main.c main.h zbuffer.h data.h param.h
	gcc -Wall -o main.o -c main.c -O2

zbuffer.o: zbuffer.c zbuffer.h illumination.h transformations.h data.h
	gcc -Wall -o zbuffer.o -c zbuffer.c -O2

illumination.o: illumination.c illumination.h data.h
	gcc -Wall -o illumination.o -c illumination.c -O2

transformations.o: transformations.c transformations.h data.h
	gcc -Wall -o transformations.o -c transformations.c -O2
	
param.o: param.c param.h data.h
	gcc -Wall param.c -o param.o -c -O2

clean:
	rm *.o
