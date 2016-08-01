# BDUtils Makefile for all sub-projects
#
# @file
#

#include version

DOCS = doc
RPM = build
PROJECTS = bdls
EVERYTHING = $(PROJECTS) $(DOCS) $(RPM)

.PHONY: all $(EVERYTHING)

all: $(EVERYTHING)

$(EVERYTHING): 
	${MAKE} -C $@
