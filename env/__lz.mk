################################################################################
##  File        : __lz.mk                                                     ##
##  Description : controlp makefile environment                               ##
##  Author      : LaZyDev                                                     ##
##  Contacts    : chriskr7@gmail.com                                          ##
################################################################################

# Shell
SHELL=/bin/bash

#
# Compile Environment
#

TARGET = $(shell $(LZLIB_HOME)/env/check_machine.sh)

XCC = g++

# Home Path
LZLIB_CHOME = $(LZLIB_HOME)

# Other Path
LZLIB_LIB = $(LZLIB_HOME)/lib
LZLIB_ENV = $(LZLIB_HOME)/env
# LZLIB_INC = $(LZLIB_HOME)/inc
# LZLIB_SRC = $(LZLIB_HOME)/src

#OPT Mode Define
Linux.OMODE = -w -fPIC
Darwin.OMODE = -w -fPIC

#Debug Optioin
Linux.DEBUG_OPT = -g -DDEBUG
Darwin.DEBUG_OPT = -g -DDEBUG

#THREAD Compile Option Define
Linux.THREAD.CFLAGS = -D_THREAD_SAFE -D_GNU_SOURCE
Darwin.THREAD.CFLAGS = -D_THREAD_SAFE -D_GNU_SOURCE

#PTHREAD Load Option Define
Linux.PTHREAD.LFLAGS=-lpthread -ldl -lrt
Darwin.PTHREAD.LFLAGS=-lpthread -ldl

#SOCKET Load Option Define
Linux.SOCKET.LFLAGS=-lnsl
Darwin.SOCKET.LFLAGS=

#ISAM Load Option Define
Linux.CISAM.LFLAGS=-lisam
Darwin.CISAM.LFLAGS=-lisam

#MATH Load Option
Linux.MATH.LFLAGS=-lm
Darwin.MATH.LFLAGS=-lm

#Compile Option Define
# CFLAGS = -I$(CP_INC) $($(TARGET).OMODE) $($(TARGET).THREAD.CFLAGS) $($(TARGET).PTHREAD.LFLAGS)
CFLAGS = $($(TARGET).OMODE) $($(TARGET).THREAD.CFLAGS) $($(TARGET).PTHREAD.LFLAGS)
DCFLAGS = $($(TARGET).OMODE) $($(TARGET).THREAD.CFLAGS) $($(TARGET).DEBUG_OPT)
LFLAGS=$($(TARGET).PTHREAD.LFLAGS) $($(TARGET).SOCKET.LFLAGS) $($(TARGET).MATH.LFLAGS -L$(CP_LIB)
# CPPFLAGS = -I$(BOOST_INC) $(Linux.CFLAGS) -L/usr/lib/gcc/x86_64-redhat-Linux/4.1.1/libstdc++.so
# DCPPFLAGS = -I$(BOOST_INC) $(Linux.CFLAGS) $($(TARGET).DEBUG_OPT) -L/usr/lib/gcc/x86_64-redhat-Linux/4.1.1/libstdc++.so
