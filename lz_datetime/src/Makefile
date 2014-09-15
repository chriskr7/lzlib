include $(LZLIB_HOME)/env/__lz.mk

LIBARC=liblzdt.a

LIBSRC=lz_datetime.c

OBJSRC=$(LIBSRC:.c=.o)

LIBINC=-I$(LZLIB_HOME)/lz_datetime/inc

# Default Rules:
.c:
	$(CC) -o $(CFLAGS) $(LFLAGS) $< -o $@
.c.a:
	$(CC) -c $(CFLAGS)
	ar rv $(LIBARC) $*.o
	rm -f $*.o

all: $(LIBARC)

$(LIBARC): $(LIBSRC)
	$(CC) -c $(CFLAGS) $(LIBINC) $(LFLAGS) $(LIBSRC)
	@ar rv $(LIBARC) $(OBJSRC)
	@rm -f $(OBJSRC)

install: all
	cp $(LIBARC) $(LZLIB_LIB)
	# rm -f $(LIBARC)

clean:
	-rm -f $(PROGS) *.o
