include $(LZLIB_HOME)/env/__lz.mk

PROGS= test

#LDFLAG=$(LZLIB_LIB)/liblztypeconv.a
LDFLAG=$(LZLIB_HOME)/liblzlib.a


# Default Rules:
.c:
	$(CC) -o $(CFLAGS) $(LFLAGS) $< -o $@

all: $(PROGS)

$(PROGS): test.c
	$(CC) -o $@ $@.c $(CFLAGS) $(LFLAGS) $(LDFLAG)


clean:
	-rm -f $(PROGS) *.o
