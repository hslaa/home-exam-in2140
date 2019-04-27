CCFLAGS = -g -Wall -Wextra -Wpedantic -std=c99

all: routing_server node

UTILS = core/network.c core/protocol.c util/transmission.c util/q.c util/sssp.c util/helpers.c util/print_lib.c



routing_server: $(UTILS) core/routing_server.c
	gcc -D_POSIX_C_SOURCE=200809L $(UTILS) core/routing_server.c $(CCFLAGS) -o routing_server

node: $(UTILS) core/node.c 
	gcc -D_POSIX_C_SOURCE=200809L $(UTILS) core/node.c $(CCFLAGS) -o node


run: all
	bash run_1.sh 54321
	bash run_2.sh 12345
clean:
	rm -f routing_server
	rm -f node


