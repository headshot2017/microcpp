# makefile for libpng
# Copyright (C) 2002, 2006 Glenn Randers-Pehrson
# Copyright (C) 1995 Guy Eric Schalnat, Group 42, Inc.
# For conditions of distribution and use, see copyright notice in png.h

# where make install puts libpng.a and png.h
prefix=/usr/local
INCPATH=$(prefix)/include
LIBPATH=$(prefix)/lib

# override DESTDIR= on the make install command line to easily support
# installing into a temporary location.  Example:
#
#    make install DESTDIR=/tmp/build/libpng
#
# If you're going to install into a temporary location
# via DESTDIR, $(DESTDIR)$(prefix) must already exist before
# you execute make install.
DESTDIR=

# Where the zlib library and include files are located
#ZLIBLIB=/usr/local/lib
#ZLIBINC=/usr/local/include
ZLIBLIB=../zlib-1.2.3
ZLIBINC=../zlib-1.2.3

CC=arm-eabi-gcc
AR_RC=arm-eabi-ar rc
MKDIR_P=mkdir
LN_SF=ln -sf
RANLIB=arm-eabi-ranlib
RM_F=rm -f

CFLAGS=-I$(ZLIBINC) -Os # -g -DPNG_DEBUG=5
LDFLAGS=-L. -L$(ZLIBLIB) -lpng -lz -lm

#OBJS = png.o pngset.o pngget.o pngrutil.o pngtrans.o pngwutil.o \
#	pngread.o pngrio.o pngwio.o pngwrite.o pngrtran.o \
#	pngwtran.o pngmem.o pngerror.o pngpread.o
OBJS = png.o pngset.o pngget.o pngrutil.o pngtrans.o \
	pngread.o pngrio.o pngrtran.o \
	pngmem.o pngerror.o pngpread.o

all: libpng.a

libpng.a: $(OBJS)
	$(AR_RC) $@  $(OBJS)
	$(RANLIB) $@
	cp libpng.a ../

pngtest: pngtest.o libpng.a
	$(CC) -o pngtest $(CFLAGS) pngtest.o $(LDFLAGS)

test: pngtest
	./pngtest

install: libpng.a
	-@$(MKDIR_P) $(DESTDIR)$(INCPATH)
	-@$(MKDIR_P) $(DESTDIR)$(INCPATH)/libpng
	-@$(MKDIR_P) $(DESTDIR)$(LIBPATH)
	-@$(RM_F) $(DESTDIR)$(INCPATH)/png.h
	-@$(RM_F) $(DESTDIR)$(INCPATH)/pngconf.h
	cp png.h $(DESTDIR)$(INCPATH)/libpng
	cp pngconf.h $(DESTDIR)$(INCPATH)/libpng
	chmod 644 $(DESTDIR)$(INCPATH)/libpng/png.h
	chmod 644 $(DESTDIR)$(INCPATH)/libpng/pngconf.h
	(cd $(DESTDIR)$(INCPATH); ln -f -s libpng/* .)
	cp libpng.a $(DESTDIR)$(LIBPATH)
	chmod 644 $(DESTDIR)$(LIBPATH)/libpng.a

clean:
	$(RM_F) *.o libpng.a pngtest pngout.png

DOCS = ANNOUNCE CHANGES INSTALL KNOWNBUG LICENSE README TODO Y2KINFO
writelock:
	chmod a-w *.[ch35] $(DOCS) scripts/*

# DO NOT DELETE THIS LINE -- make depend depends on it.

png.o: png.h pngconf.h
pngerror.o: png.h pngconf.h
pngrio.o: png.h pngconf.h
pngwio.o: png.h pngconf.h
pngmem.o: png.h pngconf.h
pngset.o: png.h pngconf.h
pngget.o: png.h pngconf.h
pngread.o: png.h pngconf.h
pngrtran.o: png.h pngconf.h
pngrutil.o: png.h pngconf.h
pngtest.o: png.h pngconf.h
pngtrans.o: png.h pngconf.h
pngwrite.o: png.h pngconf.h
pngwtran.o: png.h pngconf.h
pngwutil.o: png.h pngconf.h
pngpread.o: png.h pngconf.h

