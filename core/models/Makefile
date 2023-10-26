include config.mk

build : build-address build-user
	ar -rcs $(PROJECT_ROOT)/bin/core/lib$(BASE_NAME)-models.a $(PROJECT_ROOT)/bin/core/models-*.o
build-address :
	g++ -c $(PROJECT_ROOT)/core/models/address.cpp -o $(PROJECT_ROOT)/bin/core/models-address.o -I$(PROJECT_ROOT)/core
build-user :
	g++ -c $(PROJECT_ROOT)/core/models/user.cpp -o $(PROJECT_ROOT)/bin/core/models-user.o -I$(PROJECT_ROOT)/core