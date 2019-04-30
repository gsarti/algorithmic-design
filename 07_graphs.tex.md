# Graphs

In the depth-first search, numbers on the nodes represent the finding time and finishing time of the node. When a node isn't connected to any white node, the backtracking moves back in the graph of a node and colors the node black.

A **Strongly Connected Component (SCC)** is a sub-graph s.t. for every pair of nodes in it, there is a path from one to the other and vice versa (no path = zero-length path = each node is a basic SCC by itself). To identify them, we may use Depth-First Search to spot loops. The **Minimum discovery time (lowlink)** of a subtree is the minimum among the discovery times in the subtree. If the discovery time of a child node in a subtree is greater than the one of its parent, we have that there must be either a back edge connecting them, or a forward edge connecting to a different SCC.

The discovery time and the lowlink of the first node to be visited by DFS in a SCC are intuitively the same. All the nodes having discovery time higher than their own lowlink belong to the same SCC as the node having that lowlink as discovery time.

If we perform the DFS traversal and list all nodes in order of finishing time (from lower to higher), we can use a stack to iteratively spot SCCs, removing them from the stack.

## Shortest Paths

We used BFS to build the tree of shortest paths from a node to all other nodes on unweighted (plain) graphs. The time required to compute the shortest path in that setting was $O(|V| + |E|)$, and the processing of grey nodes was handled by a FIFO queue.

In the case where a node is close to source but with a high weight label on its edge, while another longer path that connects it to source has total label weight which is smaller, we see that raw BFS is not apt for shortest pathfinding in weighted graphs.

Instead, we want to pre-label our nodes with a candidate distance while they are grey, and each time another smaller candidate distance is computed for that node (coming from a new path), it replaces the old one until we get the final distance. At each step we extract from the queue the node with smallest distance from the source and finalize it. This is known as **Dijkstra's Algorithm**.

The Dijkstra's Algorithm has time complexity $O(|V| + |E| + \log|V|)$ when a Fibonacci heap is used to store the nodes and works **only for edges having positive labels**.

How to compute all shortest paths between all nodes in a graph? A possible approach would be to run Dijkstra for all nodes, but there are more efficient ways to do so.

In the Floyd-Warshall's algorithm, we have three matrices:

* The **adjacency matrix**, which represent the weights of each connection between nodes (row represent the from-node index, column the to-node index)

* The $\Pi^{(n)}$ **matrix** is the matrix containing all the predecessors for each shortest path at step $n$. At the first step, it contains all the predecessors for all the edges in graph (NULL when there is no edge, row_id when there is a connection).

* The $D^{(n)}$ **matrix** that contains the minimum lenghts all nodes in the graph (row represent the from-node index, column the to-node index)

The complexity of Floyd-Warshall is $\Theta(|V|^3)$ while the Dijkstra-based approach implemented with a Fibonacci heap has complexity $O(|V|(|V| \log (|V| + |E|)$, which is cubic w.r.t. edges only in the worst case scenario. The reason to use Floyd-Warshall then is to deal with negative-weighted paths, which Dijkstra's algorithm cannot manage.

## Routing

The routing problem is similar to the **Single Source Shortest Path (SSSP)** problem: instead of using a single source to find shortest path to all destinations, we use all possible paths to find the shortest way from a source to a single destination.

We see that plain Dijkstra is not optimal since it looks in all directions We can use a light version of the Dijkstra's algorithm ( called **A* algorithm**to perform routing: the best complexity will be the same as for SSSP.

Since to compute shortest paths in real life we also have to take in account the topology of the territory connecting the two locations, the A* algorithm must take in account a heuristic distance which can be whichever fitting distance (Euclidean, Manhattan, Chebyshev).

This approach allows to reduce the number of queue extractions performed by the Dijkstra's algorithm dramatically.

Routing techniques can be applied to many fields:

* Routing of internet packets between servers

* Parcel delivers

* Travelers commuting

