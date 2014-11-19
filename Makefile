include $(LZLIB_HOME)/env/__lz.mk

LIBARC=liblzlib.a

LIBSRC=$(LZLIB_HOME)/lz_hashmap/src/lz_hashmap.c\
	$(LZLIB_HOME)/lz_datetime/src/lz_datetime.c\
	$(LZLIB_HOME)/lz_typeconv/src/lz_typeconv.c\
	$(LZLIB_HOME)/lz_logger/src/lz_logger.c

OBJSRC=$(LZLIB_HOME)/lz_hashmap.o\
	$(LZLIB_HOME)/lz_datetime.o\
	$(LZLIB_HOME)/lz_typeconv.o\
	$(LZLIB_HOME)/lz_logger.o

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

clean:
	-rm -f $(LZLIB_HOME)/$(LIBARC) *.o
