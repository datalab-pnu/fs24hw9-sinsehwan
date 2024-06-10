CC=g++
CFLAGS= -Wall 
OBJS = testbtree.o
INCDIR=./include
LIBDIR=./lib
DIRS = btindex buffer fixed
MKDIR_P = mkdir -p

.PHONY: all clean mklibdir

all: mklibdir testBtree

mklibdir: $(LIBDIR)
$(LIBDIR):
	$(MKDIR_P) $(LIBDIR)

%.o: %.cpp
	$(CC) -c -I$(INCDIR) $(CFLAGS) -o $@ $<

testBtree: $(OBJS)
	@for d in $(DIRS); \
	do \
		$(MAKE) -C $$d; \
	done
	$(CC) -o testBtree $(OBJS) -L$(LIBDIR) -lmybuffer -lmyfixed -lmybtree -lc -Wl,-rpath=$(LIBDIR)

clean:
	@for d in $(DIRS); \
	do \
		$(MAKE) -C $$d clean; \
	done
	-rm -rf testBtree testbt.dat $(OBJS) 
