ROOTINC = $(shell root-config --cflags)
ROOTLIB = $(shell root-config --libs)

run: prat9.exe
	@echo "\n" $^ "\n"
	./prat9.exe

prat9.exe: main.o ZeroFunctor.o
	@echo Linking $@ from $^
	g++ -std=c++11 -o $@ $^ $(ROOTLIB)

main.o: main.C
ZeroFunctor.o: ZeroFunctor.C ZeroFunctor.h

.C.o:
	@echo Building $@ from $< ... 
	g++ -std=c++11 -c -Wall $<  $(ROOTINC)

clean: 
	@echo Cleaning the directory.
	rm -f *.o
	rm -f *.exe
	rm -f *~