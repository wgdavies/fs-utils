# FSLS Makefile
#
# @file
#

#include version

SOURCES = fsls.c
OBJECTS = quickcount.o getdirent.o
HEADERS = fsls.h

DevFLAGS = -g -Wall -I. -include $(HEADERS)
ProdFLAGS = -O3 -I. -include $(HEADERS)
CFLAGS = $(DevFLAGS)
LDFLAGS = -lpopt
CC = c99
OUTPUT = -o fsls

DOCS = doc
RPM = build
PROJECT = fsls
EVERYTHING = $(PROJECT) $(DOCS) $(RPM)

all: $(PROJECT)

fsls : $(OBJECTS)

$(OBJECTS) : $(HEADERS)

$(EVERYTHING) :
	${MAKE} -C $@

.PHONY : clean

clean : 
	-rm -f $(PROJECT) $(OBJECTS)
