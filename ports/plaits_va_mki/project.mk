# #############################################################################
# Project Customization
# #############################################################################

PROJECT = plaits_va_mki

UCSRC =

MUTABLEDIR = $(PROJECTDIR)/../../external/eurorack

UCXXSRC = \
	src/unit.cpp \
	src/plaits_virtual_analog_engine.cpp \
	src/stmlib_units.cpp

UINCDIR = $(MUTABLEDIR)

UDEFS = -DTEST=0

ULIB = 

ULIBDIR =
