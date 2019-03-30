CCFLAGS= -g 

all: routing_server node

routing_server: util/logger.c core/routing_server.c
	gcc util/logger.c core/routing_server.c $(CCFLAGS) -o routing_server

node: util/logger.c core/node.c 
	gcc util/logger.c core/node.c $(CCFLAGS) -o node


run: all
	bash run.sh

clean:
	rm -f routing_server
	rm -f node
