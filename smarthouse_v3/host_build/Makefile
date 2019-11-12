PREFIX=../
CC=gcc
INCLUDE_DIRS=-I$(PREFIX)/src/common -I$(PREFIX)/src/smarthouse_host/ 
CC_OPTS=-Wall -Ofast -std=gnu99 $(INCLUDE_DIRS)


LIBS=-lpthread -lreadline 

#dovrebbero essere i file .o che lavorano con i threads? 
LOBJS = smarthouse_client.o\
	packet_handler.o\
	serial_linux.o\
#	deferred_packet_handler.o\
#	orazio_print_packet.o\

OBJS =  smarthouse_shell_globals.o\
#	shell_commands.o\
#	ventry.o\
#	orazio_shell_commands.o\
#	orazio_ws_server.o


HEADERS = smarthouse_client.h\
	smarthouse_shell_globals.h\
#	shell_commands.h\
	serial_linux.h\
	packet_handler.h\
	smarthouse_packets.h\
	packet_header.h\
	packet_operations.h\

BINS=smarthouse

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

