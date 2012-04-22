
PROG_NAME=check_rogue_dhcp
OBJECTS=build/crd_options.o build/crd_message.o build/crd_socket.o build/crd.o
CC=gcc
CFLAGS=-g -Wall
LDFLAGS=

all : $(PROG_NAME)

clean :
	@rm -rf build 

distclean : clean
	@rm $(PROG_NAME)

$(PROG_NAME): $(OBJECTS)
	$(CC) $(LDFLAGS) -o $(PROG_NAME) $(OBJECTS)

build_dir:
	mkdir -p build

build/%.o : src/%.c src/%.h src/config.h build_dir
	$(CC) $(CFLAGS) -c $< -o $@


