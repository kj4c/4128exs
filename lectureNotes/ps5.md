# TODO:

# TIPS:
- need to know single source shortest path
unweighted: BFS
non-negative weights: dijkstra
negative weight, find negative cycles: bellman-ford

all pairs shortest path: floyd-warshall

Jzzhu & Cities, President's path
jzzhu shows how to manipulate dijkstra algo
president's path shows how to manipulate floyd-warshall


### Jumping on Walls

just a bfs where if the place you wanna jump to is not spikey then you can
also keep track of the level at each jump.

main thing was constructing the graph
instead of doing two rows, just make jump (n steps) to indicate the next row
then use % to come back down.

### Jzzhu and Cities

So we wanna find the trains that can be closed so that the shortest path remains unchanged

So clsoe every train then dijkstra from city one to every other spot.
You wanna use the priority queue to sort by the weights AND also putting non Trains first,
this way if there are two edges, same weights, one a train one not, then it will put the other edge first
So, given that you've seen this vertex before, it would indicate that this train is not needed.

```cpp
 // just to prioritse lower edge weights and also put non train edges first.
struct CompareEdge {
    bool operator()(const edge& e1, const edge& e2) {
        if (get<1>(e1) == get<1>(e2)) {
            return get<2>(e1) > get<2>(e2);
        }
        return get<1>(e1) > get<1>(e2);
    }
};
```

### Greg and Graph
A play on the floyd warshall algorithm, since its removing a vertex each time
and then recalculating the shortest path between all vertices.

Instead, do it in the reverse, instead of deleting, we add from the back
so if greg deletes node 3 1 2, instead we  start with an empty graph and
add in the nodes 2 1 3. then floyd warshall can run all this in an O(n^3)

The key thing to note that we still update the distance from that point to every graph,
we only ignore the nodes that were not activated if we are summing up the weights.

### Complete the Graph
some weights erased, need to find the shortest path between vertices s and t
such taht it is equal to L.

This one so hard man

Okay basically, set all the empty weights to have an initial value of 1,
then we wanna dijkstra to prioritise using empty edges before normal edges.

If we find that the shortest path found is < L and you dont use empty weights
already automatic not possible.

If find that shortest path > L and you use empty weights then its possible.

then now given that path we found is possible, we make every other empty weight
to be infinity, this limits the future dijkstra problems to not look at them.

Now we just constantly dumping the rest of the remaining weights to one of the empty edges,
then run dijkstra again, keep dump and run keep dump and run until we reach it.


### President's Path
Find number of roads that lie on all shortest paths from s to t.
Use floyd warshall to first find the minimum distance for each pair of points
Then find the number of edges that are coming from u, going into v WHICH CONTRIBUTE to the minimum path.
This find the number of direct edges that are going into all sinks

Then you find each node that contributes to the shortest path, counting the sum 
of the inEdges for every node.

Modification on floyd warshall.



