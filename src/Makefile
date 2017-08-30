CC := g++
CFLAGS := -Wall
LDLIBS := -lGL -lGLU -lglut

lab-one: lab-one.cc bin
	$(CC) $(CFLAGS) $< $(LDLIBS) -o $@
	mv $@ bin

bin:
	mkdir bin

clean:
	rm -rf bin/*
