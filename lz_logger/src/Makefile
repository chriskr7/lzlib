include $(LZLIB_HOME)/env/__lz.mk

LIBARC=liblzlog.a

LIBSRC=lz_logger.c

OBJSRC=$(LIBSRC:.c=.o)

LDFLAG=$(LZLIB_LIB)/liblztypeconv.a $(LZLIB_LIB)/liblzdt.a

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
	@cp $(LIBARC) $(LZLIB_HOME)/lz_logger/lib
	@rm -f $(LIBARC)

install: all
	@cp $(LZLIB_HOME)/lz_logger/lib/$(LIBARC) $(LZLIB_LIB)

clean:
	-rm -f $(LZLIB_HOME)/lz_logger/lib/$(LIBARC) *.o
