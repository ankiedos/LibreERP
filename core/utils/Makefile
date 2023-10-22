include config.mk

build : build-helpers build-datastructs
	ar -rcs $(PROJECT_ROOT)/bin/core/lib$(BASE_NAME)-utils.a $(PROJECT_ROOT)/bin/core/utils-*.o

build-helpers : build-address build-email
build-address :
	g++ -c $(PROJECT_ROOT)/core/utils/address.cpp -o $(PROJECT_ROOT)/bin/core/utils-address.o -I$(PROJECT_ROOT)/core
build-email :
	g++ -c $(PROJECT_ROOT)/core/utils/e-mail.cpp -o $(PROJECT_ROOT)/bin/core/utils-e-mail.o -I$(PROJECT_ROOT)/core
	g++ -c $(PROJECT_ROOT)/core/utils/e-mail-validator.cpp -o $(PROJECT_ROOT)/bin/core/utils-e-mail-validator.o -I$(PROJECT_ROOT)/core


build-datastructs : build-glueable-vec
build-glueable-vec :
	g++ -c $(PROJECT_ROOT)/core/utils/glueable-vector.cpp -o $(PROJECT_ROOT)/bin/core/utils-glueable-vector.o -I$(PROJECT_ROOT)/core
	g++ -c $(PROJECT_ROOT)/core/utils/glueable-string-vector.cpp -o $(PROJECT_ROOT)/bin/core/utils-glueable-string-vector.o -I$(PROJECT_ROOT)/core