CC := g++
CFLAGS := -Wall -c
LDLIBS := -lGL -lGLU -lglut

BLDDIR := build
SRCDIR := src

SOURCES := $(wildcard $(SRCDIR)/*.cc)
OBJECTS := $(SOURCES:$(SRCDIR)/%.cc=$(BLDDIR)/%.o)

all: $(BLDDIR) lab-one lab-two

lab-one: $(addprefix $(BLDDIR)/, lab-one.o opengl-window.o)
	$(CC) $^ $(LDLIBS) -o $(BLDDIR)/$@

lab-two: $(addprefix $(BLDDIR)/, lab-two.o opengl-window.o)
	$(CC) $^ $(LDLIBS) -o $(BLDDIR)/$@

test: test/test-gl.cc $(BLDDIR)/opengl-window.o
	$(CC) $^ $(LDLIBS) -o $(BLDDIR)/$@

$(OBJECTS): $(BLDDIR)/%.o : $(SRCDIR)/%.cc
	$(CC) $(CFLAGS) $< -o $@

$(BLDDIR):
	mkdir -p $@

clean:
	rm -rf $(BLDDIR)/*
