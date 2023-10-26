include config.mk
build : build-user
	ar -rcs $(PROJECT_ROOT)/bin/core/lib$(BASE_NAME)-queries.a $(PROJECT_ROOT)/bin/core/queries-*.o
build-user :
	g++ -c $(PROJECT_ROOT)/core/queries/user-query.cpp -o $(PROJECT_ROOT)/bin/core/queries-user.o -I$(PROJECT_ROOT)/core