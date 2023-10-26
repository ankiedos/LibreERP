include config.mk

build : build-interface build-user
	ar -rcs $(PROJECT_ROOT)/bin/core/lib$(BASE_NAME)-repos.a $(PROJECT_ROOT)/bin/core/repos-*.o
build-interface :
	g++ -c $(PROJECT_ROOT)/core/repos/irepository.cpp -o $(PROJECT_ROOT)/bin/core/repos-irepository.o -I$(PROJECT_ROOT)/core
build-user :
	g++ -c $(PROJECT_ROOT)/core/repos/user-repository.cpp -o $(PROJECT_ROOT)/bin/core/repos-user.o -I$(PROJECT_ROOT)/core