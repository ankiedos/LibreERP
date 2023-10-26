include config.mk

build : build-user
	ar -rcs $(PROJECT_ROOT)/bin/core/lib$(BASE_NAME)-models.a $(PROJECT_ROOT)/bin/core/models-*.o
build-user :
	g++ -c $(PROJECT_ROOT)/core/models/user.cpp -o $(PROJECT_ROOT)/bin/core/models-user.o -I$(PROJECT_ROOT)/core