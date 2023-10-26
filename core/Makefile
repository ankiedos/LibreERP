include config.mk

all : build test

build :
	make -f core/utils/Makefile build
	make -f core/models/Makefile build
	make -f core/repos/Makefile build
	make -f core/queries/Makefile build

test : build-tests run-tests
build-tests :
	make -f core/tests/Makefile build
run-tests :
	make -f core/tests/Makefile run