LIBDIRS:=-L./bin/lib
LIBS:=-llibreerp-utils -lsoci_core -lsoci_mysql -ldl -lmysqlclient
INC:=-Iinclude -Ilib/include

LIB:=$(wildcard ./lib/src/*.cpp)
LIBHDRS:=$(wildcard ./lib/include/*.hpp)
MAIN:=$(wildcard ./src/*.cpp)
MAINHDRS:=$(wildcard ./include/*.hpp)
LIBOBJS:=$(patsubst ./lib/src/%.cpp,./bin/lib/%.o,$(LIB))
MAINOBJS:=$(patsubst ./src/%.c,./bin/%.o,$(MAIN))


all : sdk libreerp

libreerp : $(MAINOBJS)
	gcc $(wildcard ./bin/*.o) -o ./bin/exe/libreerp $(LIBDIRS) $(LIBS)

sdk : $(LIBOBJS)
	ar rcs ./bin/lib/liblibreerp-utils.a $(wildcard ./bin/lib/*.o)

./bin/lib/%.o : ./lib/src/%.c
	gcc -c $< -o $@ $(INC) $(shell mysql_config --cflags) -g

$(LIBOBJS) : | ./bin/lib
./bin/%.o : ./src/%.c
	gcc -c $< -o $@ $(INC) $(shell mysql_config --cflags) -g
$(MAINOBJS) : | ./bin