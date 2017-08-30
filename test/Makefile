BUILDDIR := ../build
CC := g++
CFLAGS := -Wall
LDLIBS := -lGL -lGLU -lglut

test: test-gl.cc $(BUILDDIR)
	$(CC) $(CFLAGS) $< $(LDLIBS) -o $@
	mv $@ $(BUILDDIR)

$(BUILDDIR):
	mkdir -p $(BUILDDIR)

clean:
	rm -rf $(BUILDDIR)/test
