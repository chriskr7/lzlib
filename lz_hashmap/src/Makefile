include $(LZLIB_HOME)/env/__lz.mk

LIBARC=liblzhashmap.a

LIBSRC=lz_hashmap.c

OBJSRC=$(LIBSRC:.c=.o)

LDFLAG=

# Default Rules:
.c:
	$(CC) -o $(CFLAGS) $(LFLAGS) $< -o $@
.c.a:
	$(CC) -c $(CFLAGS)
	ar rv $(LIBARC) $*.o
	rm -f $*.o

all: $(LIBARC)

$(LIBARC): $(LIBSRC)
	$(CC) -c $(CFLAGS) $(LIBINC) $(LFLAGS) $(LDFLAGS) $(LIBSRC)
	@ar rv $(LIBARC) $(OBJSRC)
	@rm -f $(OBJSRC)
	@cp $(LIBARC) $(LZLIB_HOME)/lz_hashmap/lib
	@rm -f $(LIBARC)

install: all
	@cp $(LZLIB_HOME)/lz_hashmap/lib/$(LIBARC) $(LZLIB_LIB)

clean:
	-rm -f $(LZLIB_HOME)/lz_hashmap/lib/$(LIBARC) *.o
