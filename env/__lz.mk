/******************************************************************************/
/*  File        : __lz.mk                                                     */
/*  Description : lzlib makefile environment                                  */
/*  Author      : LaZy                                                        */
/*  Contacts    : chriskr7@gmail.com                                          */
/******************************************************************************/

#
# Compile Environment
#

TARGET = LINUX

XCC = g++

# Home Path
LZLIB_HOME = $(LZLIB_DIR)/bp
LZLIB_CHOME = $(LZLIB_HOME)

# Other Path
LZLIB_LIB = $(LZLIB_HOME)/lib
LZLIB_ENV = $(LZLIB_HOME)/env
LZLIB_INC = $(LZLIB_HOME)/inc
LZLIB_SRC = $(LZLIB_HOME)/src

# Boost Path
BOOST_PATH = $(LZLIB_HOME)/boost/stage/lib
BOOST_INC = $(LZLIB_HOME)/boost/

#OPT Mode Define
LINUX.OMODE = -w -fPIC

#Debug Optioin
LINUX.DEBUG_OPT = -g -DDEBUG

#THREAD Compile Option Define
LINUX.THREAD.CFLAGS = -D_THREAD_SAFE -D_GNU_SOURCE

#Compile Option Define
LINUX.CFLAGS = -I$(LZLIB_INC) $($(TARGET).OMODE) $($(TARGET).THREAD.CFLAGS) $($(TARGET).PTHREAD.LFLAGS)
LINUX.DCFLAGS = -I$(LZLIB_INC) $($(TARGET).OMODE) $($(TARGET).THREAD.CFLAGS) $($(TARGET).DEBUG_OPT)
LINUX.CPPFLAGS = -I$(BOOST_INC) $(LINUX.CFLAGS) -L/usr/lib/gcc/x86_64-redhat-linux/4.1.1/libstdc++.so
LINUX.DCPPFLAGS = -I$(BOOST_INC) $(LINUX.CFLAGS) $($(TARGET).DEBUG_OPT) -L/usr/lib/gcc/x86_64-redhat-linux/4.1.1/libstdc++.so


#PTHREAD Load Option Define
LINUX.PTHREAD.LFLAGS=-lpthread -ldl -lrt

#SOCKET Load Option Define
LINUX.SOCKET.LFLAGS=-lnsl

#ISAM Load Option Define
LINUX.CISAM.LFLAGS=-lisam

#MATH Load Option
LINUX.MATH.LFLAGS=-lm

#Load Option Define
LINUX.LFLAGS=$($(TARGET).PTHREAD.LFLAGS) $($(TARGET).SOCKET.LFLAGS) $($(TARGET).MATH.LFLAGS -L$(LZLIB_LIB)

CFLAGS=$(LINUX.DCFLAGS)
CPPFLAGS=$(LINUX.CPPFLAGS)
DCPPFLAGS=$(LINUX.DCPPFLAGS)
LFLAGS=$(LINUX.LFLAGS)

