CC=gcc
LIBNAME=libmybuffer
LIB=$(LIBNAME).so.1.0
CFLAGS= -Wall 
OBJS = buffile.o iobuffer.o recfile.o
POINTER= libmybuffer.so libmybuffer.so.1
INCDIR=../include
LIBDIR=../lib

$(LIB): $(OBJS)
	$(CC) -fPIC -shared -Wl,-soname=libmybuffer.so.1 $(OBJS) -o $@ -lc
	cp $(LIB) $(LIBDIR)
	ln -s $(LIBDIR)/$(LIBNAME).so.1.0 $(LIBDIR)/$(LIBNAME).so
	ln -s $(LIBDIR)/$(LIBNAME).so.1.0 $(LIBDIR)/$(LIBNAME).so.1	

%.o: %.cpp
	$(CC) -fPIC -c $(CFLAGS) -I$(INCDIR) -o $@ $<

clean:
	-rm -rf $(OBJS) $(LIB) $(LIBDIR)/$(LIBNAME).so*
