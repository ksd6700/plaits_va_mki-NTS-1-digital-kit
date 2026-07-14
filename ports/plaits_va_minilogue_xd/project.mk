# #############################################################################
# Project Customization
# #############################################################################

PROJECT = plaits_va_minilogue_xd

UCSRC =

MUTABLEDIR = $(PROJECTDIR)/../../external/eurorack

UCXXSRC = \
	../../src/logue-v1/unit.cpp \
	../../src/logue-v1/plaits_virtual_analog_engine.cpp \
	../../src/logue-v1/stmlib_units.cpp

UINCDIR = $(MUTABLEDIR)

UDEFS = -DTEST=0

ULIB = 

ULIBDIR =
