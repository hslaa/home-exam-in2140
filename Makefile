CCFLAGS= -g 

all: routing_server node

routing_server: util/logger.c core/routing_server.c
	gcc util/logger.c core/routing_server.c $(CCFLAGS) -o routing_server

node: <Her skal alle c-filer som node avhenger av>
	gcc <Her skal alle c-filer som node avhenger av> $(CCFLAGS) -o node


run: all
	bash run.sh

clean:
	rm -f routing_server
	rm -f node
