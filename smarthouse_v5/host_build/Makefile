PREFIX=../
CC=gcc
INCLUDE_DIRS=-I $(PREFIX)/src/common -I $(PREFIX)/src/smarthouse_host/ 
CC_OPTS=-Wall -Ofast -std=gnu99 $(INCLUDE_DIRS)
#aggiungere allastringa di compilazione -D DEBUG_ERR_COMUNICATION per stampare le printf di debug

LIBS=-lpthread -lreadline 

#dovrebbero essere i file .o che lavorano con i threads? 
LOBJS =	serial_linux.o\
	packet_handler.o\

OBJS =  smarthouse_host_globals.o\
	smarthouse_shell.o\
#	shell_commands.o\
#	ventry.o\
#	orazio_shell_commands.o\
#	orazio_ws_server.o


HEADERS =	serial_linux.h\
	smarthouse_host_globals.h\
	smarthouse_shell.h\
	packet_handler.h\
	packet_header.h\
	smarthouse_packets.h\
	packet_operations.h\

BINS=host_smarthouse

.phony:	clean all

all:	$(BINS) 

#common objects
%.o:	$(PREFIX)/src/common/%.c 
	$(CC) $(CC_OPTS) -c  $<

#client 
%.o:	$(PREFIX)/src/smarthouse_host/%.c 
	$(CC) $(CC_OPTS) -c  $<

host_smarthouse: host_smarthouse.o $(OBJS) $(LOBJS)
	$(CC) $(CC_OPTS) -o $@ $< $(OBJS) $(LOBJS) $(LIBS)

clean:
	rm -rf $(OBJS) $(BINS) *~ *.d *.o


