# Copyright (C) 2016 Tristan Miller <psychonaut@nothingisreal.com>
#  
# This file is free software; the author gives unlimited permission to
# copy and/or distribute it, with or without modifications.
# 
# This program is distributed in the hope that it will be useful, but
# WITHOUT ANY WARRANTY, to the extent permitted by law; without even
# the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
# PURPOSE.

docfiles = cheops.tex

if HAVE_PDFLATEX
doc_DATA = cheops.pdf
docfiles += cheops.pdf
MANNAME = cheops
MANTEXSRC = $(MANNAME).tex
MANAUX = $(MANNAME).aux
MANPDF = $(MANNAME).pdf

CLEANFILES = $(MANPDF) $(MANNAME).log $(MANNAME).idx $(MANAUX)

$(MANPDF): $(srcdir)/$(MANTEXSRC)
	$(PDFLATEX) $<
	$(PDFLATEX) $<
endif

dist_doc_DATA = $(docfiles)
