ROOTINC = $(shell root-config --cflags)
ROOTLIB = $(shell root-config --libs)

CC = g++ -std=c++11 -c $(ROOTINC)

test: tMfull.exe

tMfull.exe: tMfull.o FCmatrixFull.o  FCmatrix.o   Vec.o 
	g++  $^ -o $@ $(ROOTLIB) 

tMfull.o: tMfull.C
FCmatrixFull.o: FCmatrixFull.C FCmatrixFull.h
FCmatrix.o: FCmatrix.C FCmatrix.h
Vec.o: Vec.C Vec.h

.C.o:
	@echo building $@ from $< "\n"
	$(CC) $<

clean:
	@echo cleaning... "\n"
	rm -f *.o