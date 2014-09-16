include $(LZLIB_HOME)/env/__lz.mk

LIBARC=liblzdt.a

LIBSRC=lz_datetime.c

OBJSRC=$(LIBSRC:.c=.o)

LDFLAG=$(LZLIB_HOME)/lz_typeconv/lib/liblztypeconv.a

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
	@cp $(LIBARC) $(LZLIB_HOME)/lz_datetime/lib
	@rm -f $(LIBARC)

install: all
	cp $(LIBARC) $(LZLIB_LIB)
	# rm -f $(LIBARC)

clean:
	-rm -f $(PROGS) *.o
