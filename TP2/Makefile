# $Id: Makefile,v 1.2 2004/10/12 09:06:17 marquet Exp $
##############################################################################

#ROOTDIR=/home/enseign/ASE
ROOTDIR=libhardware

CC	= gcc
CFLAGS	= -Wall -pedantic
CFLAGS  += -g -m32
#CFLAGS  = -m32
LIBDIR  = $(ROOTDIR)/lib
INCDIR  = -I$(ROOTDIR)/include
LIBS    = -L$(LIBDIR) -lhardware

###------------------------------
### Main targets
###------------------------------------------------------------
BINARIES= mkhd
OBJECTS	= $(addsuffix .o,\
	  mkhd)

all: $(BINARIES) $(OBJECTS)


###------------------------------
### Main rules
###------------------------------------------------------------
drive.o: drive.c
	$(CC) $(CFLAGS) -c drive.c $(INCDIR)

vol.o: vol.c
	$(CC) $(CFLAGS) -c vol.c $(INCDIR)

mbr.o: mbr.c
		$(CC) $(CFLAGS) -c mbr.c $(INCDIR)

mkhd.o: mkhd.c
	$(CC) $(CFLAGS) -c mkhd.c $(INCDIR)

mkhd: mkhd.o drive.o vol.o mbr.o
	$(CC) $(CFLAGS) -o mkhd mkhd.o drive.o vol.o $(LIBS)

###------------------------------
### Misc.
###------------------------------------------------------------
.PHONY: clean realclean depend
clean:
	$(RM) *.o $(BINARIES)
realclean: clean
	$(RM) vdiskA.bin vdiskB.bin
