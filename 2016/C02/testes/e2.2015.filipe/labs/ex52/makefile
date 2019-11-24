ROOTINC = $(shell root-config --cflags)
ROOTLIB = $(shell root-config --libs)
HEADERINC = -I ../../headers/

WARNINGS = -Wshadow -Wfloat-equal -Wconversion -Wdouble-promotion
WARNINGS_EXTRA = -Wall -Wextra -Wshadow -Wfloat-equal -Wconversion -Wdouble-promotion

CC = $(shell root-config --cxx) -std=c++11 $(HEADERINC) $(ROOTINC)

.PRECIOUS: run% test%.exe %.o
.PHONY: warn warnall debug clean cleanlocal cleanlib
.SUFFIXES:
########################################

run%: test%.exe
	@echo "\n" $< "\n"
	@./$<

test%.exe: test%.o ../../libs/libFunctor.a ../../libs/libInterpolator.a ../../libs/libEqSolver.a ../../libs/libFCmatrix.a ../../libs/libVec.a ../../libs/libFCg.a 
	@echo Linking $@ from $(notdir src/$^)
	@$(CC) -o $@ $^  $(ROOTLIB)

compilelib: ../../libs/libFunctor.a

../../libs/libFunctor.a: Func1D.o Integrator.o Derivator.o
	@echo Compiling Library $(notdir src/$@)
	@ar rv $@ $^
	ranlib $@

../../libs/libVec.a: 
	@$(MAKE) -C ../ex42/ compilelib	

../../libs/libFCmatrix.a: 
	@$(MAKE) -C ../ex45/ compilelib

../../libs/libEqSolver.a: 
	@$(MAKE) -C ../ex46/ compilelib

../../libs/libInterpolator.a: 
	@$(MAKE) -C ../ex49/ compilelib

../../libs/libFCg.a: 
	@$(MAKE) -C ../../ libs/libFCg.a

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
	@$(MAKE) -C ../ex42/ cleanlib
	@$(MAKE) -C ../ex45/ cleanlib
	@$(MAKE) -C ../ex46/ cleanlib
#	@$(MAKE) -C ../../libs/FCg/ cleanlib

cleanlocal:
	@echo Cleaning...
	@rm -f *.o
	@rm -f *.exe
	@rm -f *~

cleanlib:
	@rm -f *.o
	rm -f ../../libs/libFunctor.a