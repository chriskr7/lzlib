include $(LZLIB_HOME)/env/__lz.mk

LIBARC=liblztypeconv.a

LIBSRC=lz_typeconv.c

OBJSRC=$(LIBSRC:.c=.o)

# Default Rules:
.c:
	$(CC) -o $(CFLAGS) $(LFLAGS) $< -o $@
.c.a:
	$(CC) -c $(CFLAGS)
	@ar rv $(LIBARC) $*.o
	@rm -f $*.o

all: $(LIBARC)

$(LIBARC): $(LIBSRC)
	$(CC) -c $(CFLAGS) $(LFLAGS) $(LIBSRC)
	@ar rv $(LIBARC) $(OBJSRC)
	@rm -f $(OBJSRC)
	@cp $(LIBARC) $(LZLIB_HOME)/lz_typeconv/lib
	@rm -f $(LIBARC)

install: all
	@cp $(LZLIB_HOME)/lz_typeconv/lib/$(LIBARC) $(LZLIB_LIB)

clean:
	-rm -f $(LZLIB_HOME)/lz_typeconv/lib/$(LIBARC) *.o
