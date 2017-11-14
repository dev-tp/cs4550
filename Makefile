CC := g++
CFLAGS := -std=c++11 -Wall -c -g
LDLIBS := -lGL -lGLU -lglut

BLDDIR := build
SRCDIR := src

SOURCES := $(wildcard $(SRCDIR)/*.cc)
OBJECTS := $(SOURCES:$(SRCDIR)/%.cc=$(BLDDIR)/%.o)

all: $(BLDDIR) lab-1-practice lab-1 lab-2-practice lab-2 lab-3 lab-4 lab-5 \
 lab-6 lab-8 lab-9 homework-1 homework-2

homework-1: $(BLDDIR)/homework-1.o
	$(CC) $^ $(LDLIBS) -o $(BLDDIR)/$@

homework-2: $(BLDDIR)/homework-2.o
	$(CC) $^ $(LDLIBS) -o $(BLDDIR)/$@

lab-1-practice: $(addprefix $(BLDDIR)/, lab-1-practice.o opengl-window.o)
	$(CC) $^ $(LDLIBS) -o $(BLDDIR)/$@

lab-1: $(addprefix $(BLDDIR)/, lab-1.o opengl-window.o)
	$(CC) $^ $(LDLIBS) -o $(BLDDIR)/$@

lab-2-practice: $(addprefix $(BLDDIR)/, lab-2-practice.o opengl-window.o)
	$(CC) $^ $(LDLIBS) -o $(BLDDIR)/$@

lab-2: $(addprefix $(BLDDIR)/, lab-2.o opengl-window.o)
	$(CC) $^ $(LDLIBS) -o $(BLDDIR)/$@

lab-3: $(addprefix $(BLDDIR)/, lab-3.o opengl-window.o)
	$(CC) $^ $(LDLIBS) -o $(BLDDIR)/$@

lab-4: $(BLDDIR)/lab-4.o
	$(CC) $^ $(LDLIBS) -o $(BLDDIR)/$@

lab-5: $(BLDDIR)/lab-5.o
	$(CC) $^ $(LDLIBS) -o $(BLDDIR)/$@

lab-6: $(addprefix $(BLDDIR)/, lab-6.o mesh.o)
	$(CC) $^ $(LDLIBS) -o $(BLDDIR)/$@

lab-8: $(addprefix $(BLDDIR)/, lab-8.o camera.o)
	$(CC) $^ $(LDLIBS) -o $(BLDDIR)/$@

lab-9: $(addprefix $(BLDDIR)/, lab-9.o camera.o)
	$(CC) $^ $(LDLIBS) -o $(BLDDIR)/$@

test: test/test-gl.cc $(BLDDIR)/opengl-window.o
	$(CC) $^ $(LDLIBS) -o $(BLDDIR)/$@

$(OBJECTS): $(BLDDIR)/%.o : $(SRCDIR)/%.cc
	$(CC) $(CFLAGS) $< -o $@

$(BLDDIR):
	mkdir -p $@

clean:
	rm -rf $(BLDDIR)/*
