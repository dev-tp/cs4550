CC := g++
CFLAGS := -Wall
LDLIBS := -lGL -lGLU -lglut

test: test-gl.cc
	$(CC) $(CFLAGS) $< $(LDLIBS) -o $@

clean:
	rm -rf test
