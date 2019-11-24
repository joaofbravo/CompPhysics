ROOTINC = $(shell root-config --cflags)
ROOTLIB = $(shell root-config --libs)
HEADERINC = -I ../../headers/

WARNINGS = -Wshadow -Wfloat-equal -Wconversion -Wdouble-promotion
WARNINGS_EXTRA = -Wall -Wextra -Wshadow -Wfloat-equal -Wconversion -Wdouble-promotion

CC = $(shell root-config --cxx) -std=c++11 $(HEADERINC) $(ROOTINC)

.PHONY: warn warnall debug clean cleanlocal cleanlib

########################################

run: testeqsolver.exe
	@echo "\n" $< "\n"
	@./$<

testeqsolver.exe: testeqsolver.o ../../libs/libEqSolver.a ../../libs/libFCmatrix.a ../../libs/libVec.a
	@echo Linking $@ from $(notdir src/$^)
	@$(CC) -o $@ $^

compilelib:	../../libs/libEqSolver.a	

../../libs/libEqSolver.a: EqSolver.o
	@echo Compiling Library $(notdir src/$@)
	@ar rv $@ $^
	@ranlib $@

../../libs/libVec.a:
	@$(MAKE) -C ../../lab6/ex42/ compilelib

../../libs/libFCmatrix.a:
	@$(MAKE) -C ../../lab7/ex45/ compilelib

%.o: %.C %.h
	@echo Compiling $(notdir src/$^)
	@$(CC) -c $< -o $@

%.o: %.C
	@echo Compiling $(notdir src/$^)
	@$(CC) -c $< -o $@

warn:
	@echo "\n" -WARNINGS "\n"
	$(eval CC += $(WARNINGS))

warnall:
	@echo "\n" -WARNINGS EXTRA "\n"
	$(eval CC += $(WARNINGS_EXTRA))

debug: 
	@echo "\n" -DDEBUG "\n"
	$(eval CC += -DDEBUG)

clean: cleanlocal cleanlib
	@$(MAKE) -C ../../lab6/ex42/ cleanlib
	@$(MAKE) -C ../../lab7/ex45/ cleanlib

cleanlocal:	
	@echo Cleaning...
	@rm -f *.o
	@rm -f *.exe
	@rm -f *~

cleanlib:
	@rm -f EqSolver.o
	rm -f ../../libs/libEqSolver.a