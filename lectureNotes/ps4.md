# TODO:
- look into DFS more and how it is used for lecture examples
- look into how to compute the LCA!
- look into Bridge Finding.

# TIPS:
- need to know DFS, DAGs, SCCs, MST
- DFS on tree is very useful
- LCA IS VERY useful

### Hierachy
Its a MST but with a twist
every person can only have one supervisor, so keeping a supervisors array
where if they already have one then no connection.

### Useful Decomposition
split edges into simple path so each two path have one common vertex.

to see if its possible, if we find that there are two nodes with an indegree more than 2
it is never possible to split it up.

then edge case, if the given graph has no center means its a tree so just print out everything
in the tree.

else, print the stuff c oming out the central node

### Bertwon roads
connected graph, make all edges one-directional, whether it point left or right up to you,
just need to make sure that you can get from one junction to any other junciton.

This is a bridge finding algorithm, just loop and point down point down and see which edge
does not lead you back up then that is the bridge.

dont really understand bridge finding code much will resaerch later


### BRIDGE FINDING.


### Coloring edges
color edges in k colors, make it no cycles formed
min possible k, trick is you can only colour it with two colors.
Make downedges and whenever there is an upedge color it to be the opposite of the parent edge.

cool trick is 3 - parentColor, where parentColor is 1 or 2, makes sure it always alternates.

DFS from every single node for some reason...


### MST for each edge
Need to do binary lifting to find the LCA
using union find.

first find the default mst weight, then find the parents of each edge
by doing binary lifting. 
The parent of u at depth 2^i 
parent[u][0] is the immediate parent of u
parent[u][1] is the 2nd ancestor
parent[u][2] is the fourth ancestor so on.

so for the ith ancestor its derrived from the 2^(i - 1)-th ancestor's 2^i-1 ancestor.
so lets say
i = 4
so parent[u][4] = parent[parent[u][3]][3]
the sixteenth ancestor is the eighth's ancestors eigth's ancestor? 
ohhh so its the eight's ancestors eighth's ancestor 8 + 8 = 16.

if you wanna find the j-th ancestor but its not a power of two,
you break down that nuimber into a power of 2
so 12 = 2^3 + 2^2
so jump to the 2^3 ancestor then jump to the 2^2

using bitset this can work

```cpp
int find_kth_ancestor(int u, int k) {
    for (int i = 0; i < LOG; i++) {
        if (k & (1 << i)) {  // Check if the i-th bit is set in k
            u = parent[u][i]; // Jump to the 2^i-th ancestor
            if (u == -1) return -1; // If no ancestor exists, terminate early
        }
    }
    return u; // Return the final ancestor after all jumps
}
```

back to the problem, we keep track of the maxedge found to help later
also keep track of how deep the shit goes,

wanna binary lift everything up till you reach the same death.

then find the max edge while doing so, and then the formula would be
the original weight + the weight of this edge minus the heaviest_edge
found in the process of LCA from u to v where u to v is the edge to add
