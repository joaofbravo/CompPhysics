ROOTINC = $(shell root-config --cflags)
ROOTLIB = $(shell root-config --libs)
HEADERINC = -I ../../headers/

WARNINGS = -Wshadow -Wfloat-equal -Wconversion -Wdouble-promotion
WARNINGS_EXTRA = -Wall -Wextra -Wshadow -Wfloat-equal -Wconversion -Wdouble-promotion

CC = $(shell root-config --cxx) -std=c++11 $(HEADERINC) $(ROOTINC)

.PRECIOUS: run% test%.exe
.PHONY: warn warnall debug clean cleanlocal cleanlib
.SUFFIXES:

########################################

run%: test%.exe
	@echo "\n" $< "\n"
	@./$<

test%.exe: test%.o ../../libs/libFCmatrix.a ../../libs/libEqSolver.a ../../libs/libVec.a
	@echo Linking $@ from $(notdir src/$^)
	@$(CC) -o $@ $^

compilelib: ../../libs/libFCmatrix.a

../../libs/libFCmatrix.a: FCmatrix.o FCmatrixFull.o FCmatrixBanded.o
	@echo Compiling Library $(notdir src/$@)
	@ar rv $@ $^
	@ranlib $@

../../libs/libVec.a:
	@$(MAKE) -C ../../lab6/ex42/ compilelib

../../libs/libEqSolver.a:
	@$(MAKE) -C ../../lab7/ex46/ compilelib

%.o: %.C %.h
	@echo Compiling1 $(notdir src/$^)
	@$(CC) -c $< -o $@

%.o: %.C
	@echo Compiling2 $(notdir src/$^)
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
	@$(MAKE) -C ../../lab7/ex46/ cleanlib

cleanlocal:
	@echo Cleaning...
	@rm -f *.o
	@rm -f *.exe
	@rm -f *~

cleanlib:
	@echo Cleaning...
	@rm -f FCmatrix.o
	@rm -f FCmatrixFull.o
	@rm -f FCmatrixBanded.o
	rm -f ../../libs/libFCmatrix.a