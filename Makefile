CC := g++
CFLAGS := -std=c++11 -Wall -c
LDLIBS := -lGL -lGLU -lglut

BLDDIR := build
SRCDIR := src

SOURCES := $(wildcard $(SRCDIR)/*.cc)
OBJECTS := $(SOURCES:$(SRCDIR)/%.cc=$(BLDDIR)/%.o)

all: $(BLDDIR) lab-one lab-two lab-three lab-four lab-five

lab-one: $(addprefix $(BLDDIR)/, lab-one.o opengl-window.o)
	$(CC) $^ $(LDLIBS) -o $(BLDDIR)/$@

lab-two: $(addprefix $(BLDDIR)/, lab-two.o opengl-window.o)
	$(CC) $^ $(LDLIBS) -o $(BLDDIR)/$@

lab-three: $(addprefix $(BLDDIR)/, lab-three.o opengl-window.o)
	$(CC) $^ $(LDLIBS) -o $(BLDDIR)/$@

lab-four: $(addprefix $(BLDDIR)/, lab-four.o opengl-window.o)
	$(CC) $^ $(LDLIBS) -o $(BLDDIR)/$@

lab-five: $(addprefix $(BLDDIR)/, lab-five.o opengl-window.o)
	$(CC) $^ $(LDLIBS) -o $(BLDDIR)/$@

test: test/test-gl.cc $(BLDDIR)/opengl-window.o
	$(CC) $^ $(LDLIBS) -o $(BLDDIR)/$@

$(OBJECTS): $(BLDDIR)/%.o : $(SRCDIR)/%.cc
	$(CC) $(CFLAGS) $< -o $@

$(BLDDIR):
	mkdir -p $@

clean:
	rm -rf $(BLDDIR)/*
