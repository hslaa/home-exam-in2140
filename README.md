# An emulation of routing and forwarding
Repository for the take home exam in IN2140 ( Introduction to Operating Systems and Data Communication)

## Summary

compile the program with
    
    make all

run both test scripts with
    
    make run

if you see an error in the log files regarding failure to bind port, you need to change the base ports in the make file. 



### routing_server

usage: ./routing_server \<Port> \<Number of nodes>

#### Known Issues
    * Some memory might not get free'd if the program exits because of an error
    * The program validates connections between nodes that doesn't match, this _might_ lead to an error if a intermediate node quits before all messages are delivered.
    
    




### node

usage: node \<Port> \<OwnAddress> \<NeighbourAddress>:<weight> ... 


#### Known Issues

    * The nodes should in a better way validate that it has sent/received the full packet. (UDP)


