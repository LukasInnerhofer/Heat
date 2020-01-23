# Directories
EXAMPLEDIR := examples
TESTDIR := $(EXAMPLEDIR)/test
TESTEXEDIR := $(TESTDIR)/exe
TESTSRCDIR := $(TESTDIR)/src
TESTOBJDIR := $(TESTDIR)/obj
LIBDIR := lib
OBJDIR := obj
SRCDIR := src
INCDIR := inc

SRCEXT := cpp
OBJEXT := o

TESTEXE := $(TESTEXEDIR)/test.exe
TESTSRC := $(wildcard $(TESTSRCDIR)/*.cpp)
TESTOBJ := $(patsubst $(TESTSCRDIR)/%,$(TESTOBJDIR)/%,$(patsubst %.cpp,%.o,$(TESTSRC)))

LIB := $(LIBDIR)/heat.lib
SRC := $(wildcard $(SRCDIR)/*.cpp)
OBJ := $(patsubst $(SRCDIR)/%,$(OBJDIR)/%,$(SRC:.$(SRCEXT)=.$(OBJEXT)))

CXX = g++
AR = ar
CXXFLAGS = -Wall
ARFLAGS = rvs

test: $(LIB) $(TESTOBJ)
	$(CXX) $(CXXFLAGS) -o $(TESTEXE) $(LIB) $(TESTOBJ) -I$(INCDIR)

lib: $(LIB)

$(LIB): $(OBJ)
	$(AR) $(ARFLAGS) $(LIB) $<

$(OBJ): $(SRC)
	$(CXX) $(CXXFLAGS) -c -o $@ $< -I$(INCDIR)

$(TESTOBJ): $(TESTSRC)
	$(CXX) $(CXXFLAGS) -c -o $@ $< -I$(INCDIR)

clean:
	del $(LIBDIR)\heat.lib $(OBJDIR)\*.o $(EXAMPLEDIR)\test\exe\test.exe $(EXAMPLEDIR)\test\obj\*.o