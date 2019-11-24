ROOTINC = $(shell root-config --cflags)
ROOTLIB = $(shell root-config --libs)

HEADERINC = -I ../../headers/
FCLIB = -L ../../libs/ -lFCg
VECLIB = -L ../../libs/ -lVec

WARNINGS = -Wall -Wextra -Wshadow -Wfloat-equal -Wconversion -Wdouble-promotion

CC = $(shell root-config --cxx) -std=c++11 $(HEADERINC) $(ROOTINC)

.PHONY: warn debug clean

########################################

run: testvec.exe
	@echo "\n" $< "\n"
	@./$<

testvec.exe: testvec.o Vec.o FCtools.o
	@echo Linking $@ from $(notdir src/$^)
	@$(CC) -o $@ $^

compilelib:	../../libs/libVec.a

../../libs/libVec.a: Vec.o
	@echo Compiling Library $(notdir src/$@)
	@ar rv $@ $^
	@ranlib $@

%.o: %.C %.h
	@echo Compiling $(notdir src/$^)
	@$(CC) -c $< -o $@

%.o: %.C
	@echo Compiling $(notdir src/$^)
	@$(CC) -c $< -o $@
	
warn:
	@echo "\n" -WARNINGS "\n"
	$(eval CC += $(WARNINGS))

debug: 
	@echo "\n" -DDEBUG "\n"
	$(eval CC += -DDEBUG)

clean: cleanlocal cleanlib

cleanlocal:	
	@echo Cleaning... 
	@rm -f *.o
	@rm -f *.exe
	@rm -f *~

cleanlib:
	@rm -f Vec.o
	@rm -f ../../libs/libVec.a