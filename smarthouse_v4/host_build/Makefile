PREFIX=../
CC=gcc
INCLUDE_DIRS=-I$(PREFIX)/src/common -I$(PREFIX)/src/smarthouse_host/ 
CC_OPTS=-Wall -Ofast -std=gnu99 $(INCLUDE_DIRS)


LIBS=-lpthread -lreadline 

#dovrebbero essere i file .o che lavorano con i threads? 
LOBJS = packet_handler.o\
	serial_linux.o\

OBJS =  #	shell_commands.o\
#	ventry.o\
#	orazio_shell_commands.o\
#	orazio_ws_server.o


HEADERS = serial_linux.h\
	packet_handler.h\
	packet_header.h\
	packet_operations.h\

BINS=smarthouse_host.out

.phony:	clean all

all:	$(BINS) 

#common objects
%.o:	$(PREFIX)/src/common/%.c 
	$(CC) $(CC_OPTS) -c  $<

#client 
%.o:	$(PREFIX)/src/smarthouse_host/%.c 
	$(CC) $(CC_OPTS) -c  $<

smarthouse: smarthouse.o $(OBJS) $(LOBJS)
	$(CC) $(CC_OPTS) -o $@ $< $(OBJS) $(LOBJS) $(LIBS)

clean:
	rm -rf $(OBJS) $(BINS) *~ *.d *.o

