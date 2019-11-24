HEADINC = -I headers/
ROOTINC = $(shell root-config --cflags)
ROOTLIB = $(shell root-config --libs)

WARNINGS    = -Wshadow -Wfloat-equal -Wconversion -Wdouble-promotion
WARNS_EXTRA = -Wall -Wextra -Wshadow -Wfloat-equal -Wconversion -Wdouble-promotion

CC = $(shell root-config --cxx) -std=c++11 $(HEADINC) $(ROOTINC)
RM = rm -f

########## Files

LIBS        = libTools.a libFunc.a libInterpol.a libMatrix.a libFCg.a

TOOLS_OBJS  = FCtools.o

MTRX_OBJS   = Vec.o FCmatrix.o FCmatrixFull.o FCmatrixBanded.o EqSolver.o

INTRPL_OBJS = DataPoints.o Interpolator.o LagrangeInterpolator.o \
			  NewtonInterpolator.o NevilleInterpolator.o \
			  Spline3Interpolator.o

FUNC_OBJS   = Func1D.o Derivator.o Integrator.o

OTHR_OBJS   = 

MAINS       = Temperatura.o Movimento.o

.PRECIOUS: %.exe %.o
.PHONY: all Temperatura Movimento libsall warn warnall debug cleanall clean clean% cleanlibs

##############################

all: $(MAINS:%.o=%.exe)
	@echo "All execs compiled."

Temperatura: Temperatura.exe
	@echo "\n" $(<F) "\n"
	@./$<

Movimento: Movimento.exe
	@echo "\n" $(<F) "\n"
	@./$<

%.exe: %.o $(OTHR_OBJS) $(LIBS)
	@echo Linking $(@F) from $(^F)
	@$(CC) -o $@ $^ $(ROOTLIB)

########## Libs

libsall: $(LIBS)
	@echo "All libs compiled."

libFCg.a: cFCgraphics.o
	@echo Compiling Library $(@F)
	@ar rv $@ $^
	@ranlib $@

libTools.a: $(TOOLS_OBJS)
	@echo Compiling Library $(@F)
	@ar rv $@ $^
	@ranlib $@

libMatrix.a: $(MTRX_OBJS)
	@echo Compiling Library $(@F)
	@ar rv $@ $^
	@ranlib $@

libInterpol.a: $(INTRPL_OBJS)
	@echo Compiling Library $(@F)
	@ar rv $@ $^
	@ranlib $@

libFunc.a: $(FUNC_OBJS)
	@echo Compiling Library $(@F)
	@ar rv $@ $^
	@ranlib $@

########## Object Files

%.o: %.C headers/%.h
	@echo Compiling $(^F)
	@$(CC) -c $< -o $@

%.o: %.C
	@echo Compiling $(^F)
	@$(CC) -c $< -o $@

########## Options

warn:
	@echo "\n" -WARNINGS "\n"
	$(eval CC += $(WARNINGS))

warnall:
	@echo "\n" -WARNINGS EXTRA "\n"
	$(eval CC += $(WARNS_EXTRA))

debug:
	@echo "\n" -DDEBUG "\n"
	$(eval CC += -DDEBUG)

########## Clean

cleanall: clean cleanlibs
	@true

clean:
	@echo Cleaning...
	$(RM) *.o
	$(RM) *.exe
	$(RM) *~

clean%:
	@echo Cleaning $(patsubst clean%,%,$@) in project folders...
	@$(RM) $(patsubst clean%, *%*.o, $@)
	@$(RM) $(patsubst clean%, *%*.exe, $@)
	@$(RM) $(patsubst clean%, *%*.a ,$@)

cleanlibs:
	@echo Cleaning Libraries...
	$(RM) *.a