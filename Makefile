CCFLAGS = -g -Wall -Wextra -Wpedantic -std=c99

all: routing_server node

UTILS = util/q.c util/sssp.c util/helpers.c util/print.c util/print_lib.c util/logger.c


routing_server: $(UTILS) core/routing_server.c
	gcc $(UTILS) core/routing_server.c $(CCFLAGS) -o routing_server

node: $(UTILS) core/node.c 
	gcc $(UTILS) core/node.c $(CCFLAGS) -o node


run: all
	bash run.sh

clean:
	rm -f routing_server
	rm -f node
