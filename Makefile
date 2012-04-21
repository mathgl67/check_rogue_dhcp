
PROG_NAME=check_rogue_dhcp
OBJECTS=crd_message.o crd_socket.o crd.o
CC=gcc
CFLAGS=-g -Wall
LDFLAGS=

all : $(PROG_NAME)

clean :
	@rm -f $(OBJECTS)

distclean : clean
	@rm $(PROG_NAME)

$(PROG_NAME): $(OBJECTS)
	$(CC) $(LDFLAGS) -o $(PROG_NAME) $(OBJECTS)

%.o : %.c %.h config.h
	$(CC) $(CFLAGS) -c $< -o $@
	




