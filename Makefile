include config.mk

core : core-build core-test
	make -f core/Makefile all

core-build :
	make -f core/Makefile build
core-test :
	make -f core/Makefile test