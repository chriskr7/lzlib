include $(LZLIB_HOME)/env/__lz.mk

PROGS= test

LDFLAG=$(LZLIB_HOME)/lz_datetime/lib/liblzdt.a $(LZLIB_HOME)/lz_typeconv/lib/liblztypeconv.a


# Default Rules:
.c:
	$(CC) -o $(CFLAGS) $(LFLAGS) $< -o $@

all: $(PROGS)

$(PROGS): test.c
	$(CC) -o $@ $@.c $(CFLAGS) $(LFLAGS) $(LDFLAG)

clean:
	-rm -f $(PROGS) *.o
