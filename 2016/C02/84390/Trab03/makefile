# To add new src/test/lib:
# - add in HEADINC
# - add in Files
# - add in Libs

HEADINC = -Iheaders/ -Iheaders/tools/ -Iheaders/matrix/ -Iheaders/interpol/ \
		  -Iheaders/func/ -Iheaders/ode/

ROOTINC = $(shell root-config --cflags)
ROOTLIB = $(shell root-config --libs)

WARNINGS    = -Wshadow -Wfloat-equal -Wconversion -Wdouble-promotion
WARNS_EXTRA = -Wall -Wextra -Wshadow -Wfloat-equal -Wconversion -Wdouble-promotion

CC = $(shell root-config --cxx) -std=c++11 $(HEADINC) $(ROOTINC)
RM = rm -f

########## Files

# cuidado com ordem das libs
LIBS        = libTools.a libODE.a libFunc.a libInterpol.a libMatrix.a libFCg.a

TOOLS_OBJS  = FCtools.o FCrand.o

MTRX_OBJS   = Vec.o FCmatrix.o FCmatrixFull.o FCmatrixBanded.o EqSolver.o

INTRPL_OBJS = DataPoints.o Interpolator.o LagrangeInterpolator.o \
			  NewtonInterpolator.o NevilleInterpolator.o \
			  Spline3Interpolator.o

FUNC_OBJS   = Func1D.o ZeroFinder.o Derivator.o Integrator.o IntegratorMC.o

ODE_OBJS    = ODEpoint.o ODEsolver.o ODEdrawer.o

OTHR_OBJS   = MyFormula.o

MAINS       = MonteCarlo.o Trajectoria.o mainC.o

.PRECIOUS: execs/%.exe %.exe src/%.o %.o
.PHONY: all run% %.exe libsall warn warnall debug cleanall clean clean% cleanlibs

#################### Execs

all: $(MAINS:%.o=%.exe)
	@echo "All execs compiled."

A: MonteCarlo.exe
	@echo "\n" $(<F) "\n"
	@./$<

B: Trajectoria.exe
	@echo "\n" $(<F) "\n"
	@./$<

C: mainC.exe
	@echo "\n" $(<F) "\n"
	@./$<

%.exe: %.o $(OTHR_OBJS:%=src/%) $(LIBS:%=libs/%)
	@echo Linking $(@F) from $(^F)
	@$(CC) -o $@ $^ $(ROOTLIB)

########## Libs

libsall: $(LIBS:%=libs/%)
	@echo "All libs compiled."

libs/libFCg.a: src/cFCgraphics.o
	@echo Compiling Library $(@F)
	@ar rv $@ $^
	@ranlib $@

libs/libTools.a: $(TOOLS_OBJS:%=src/tools/%)
	@echo Compiling Library $(@F)
	@ar rv $@ $^
	@ranlib $@

libs/libMatrix.a: $(MTRX_OBJS:%=src/matrix/%)
	@echo Compiling Library $(@F)
	@ar rv $@ $^
	@ranlib $@

libs/libInterpol.a: $(INTRPL_OBJS:%=src/interpol/%)
	@echo Compiling Library $(@F)
	@ar rv $@ $^
	@ranlib $@

libs/libFunc.a: $(FUNC_OBJS:%=src/func/%)
	@echo Compiling Library $(@F)
	@ar rv $@ $^
	@ranlib $@

libs/libODE.a: $(ODE_OBJS:%=src/ode/%)
	@echo Compiling Library $(@F)
	@ar rv $@ $^
	@ranlib $@

########## Object Files

src/%.o: src/%.C headers/%.h
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
	$(RM) src/*.o
	$(RM) src/*/*.o
	@$(RM) src/*~
	$(RM) *.o
	$(RM) *.exe
	@$(RM) *~

clean%:
	@echo Cleaning $(patsubst clean%,%,$@) in project folders...
	@$(RM) src/$(patsubst clean%,*%*.o,$@)
	@$(RM) src/*/$(patsubst clean%,*%*.o,$@)
	@$(RM) $(patsubst clean%,*%*.o,$@)
	@$(RM) $(patsubst clean%,*%*.exe,$@)
	@$(RM) libs/$(patsubst clean%,*%*.a,$@)

cleanlibs:
	@echo Cleaning Libraries...
	$(RM) libs/*.a