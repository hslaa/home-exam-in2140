# An emulation of routing and forwarding
Repository for the take home exam in IN2140 ( Introduction to Operating Systems and Data Communication)

## Summary

### routing_server

usage: ./routing_server \<Port> \<Number of nodes>

The routing server waits for every node to connect to the server using TCP, providing their neighbouring nodes for the routing server. After every node has connected and provided their neighbouring nodes, the routing_server calculates single source shortest path (SSSP) to every node from the Node 1 using Dijkstra's Algorithm.

After calculating the shortest paths, the server creates a routing table and sends this to the node. This routing table contains pairs (destination:next hop). 

### node

usage: node \<Port> \<OwnAddress> \<NeighbourAddress>:<weight> ... 

