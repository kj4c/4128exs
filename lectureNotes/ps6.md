# TODO:
- learn more about what min cut actually means vs max flow
- project selection, image segmentation
- power transmission, magic potion (flow graph construction)
- delivery bears (binary searching)
- oil skimming (bipartite)

# TIPS:
optimisation problems (wadatmean)
if they dont allow a greedy or DP solution then use flow, this is noticable when you there is no useful order.

know how to construct multiple sources & sinks
doing two direction for undirected graphs
bipartite matching

MINCUT = MAX FLOW

### Cops and Robbers
So we wanna find the min cut.
Since if you block the cheapest entrance, every other block that is after that path would not be reachable anyways
so we just wnana find the cheapest thing in the edge
so
Bank -> cost 9 -> cost 7 -> cost 3 -> cost 10 -> exit
if we just block cost 3, then that would prevent the exiting of anything else,
obviously the further we block then the most paths to look at as you can go left n right n such.

Thats why we do max flow, which finds the min cut (minimum edges to block off).

To do this we construct an in-n-out vertex for each node, where capacity is the cost of blocking that node
and the outgoing and ingoing is juts inifnity as we do not care.

Then attach all boundary nodes to the sink.
Souce to the bank.

### Magic Potion

n heroes and m monsters, each hero fight monsters,
can take potion to attack one more fella.

so we wanna connect source to each hero with capacity one,
connect source to magic potion with capacity k,
magic potion to each hero with a one as well.

then hero to each monster they can fight.

for some reason we wanna make a magic potion node?

### Oil Skimming
We wanna find a way to split it so that every oil part connects with every oil.
Whats the difference? They are adjacent. 

If they are adjacent then split into even n odd cells where even connects to odds.

This way we form a bipartite graph and can find the num of oil areas we can clean up

### Delivery Bears
Binary Search + Flow.

Just try 100 lawl for precision.

So we reconsturcting the graph each time. To find number of bears we can send where each bear must hold X weight
We binary search given lower bound = 0 and upperbound = capacity of outgoing edges from source.

To find how many bears can be sent, we do for each edge divide the capacity by the binary searched weight for each bear
to carry, the divided value = how many bears can be sent along this path.

THen max flow is total bears that were able to be sent, if its >= x then increase weight
if its < x then decrease weight.

```cpp

    for (int i = 0; i < 100; i++) {
        FlowNetwork flow_graph(n);
        // how much an indiivual bear should carry
        mid = (left + right) / 2;

        for (auto& edge : edges) {
            // to from
            int a = edge[0], b = edge[1];
            double divided_capacity = edge[2] / mid;
            flow_graph.add_edge(a, b, divided_capacity);
        }

        // max flow will be
        max_flow = flow_graph.dinic(0, n - 1);

        // each edge represents maximum amount of bears that can cross
        // the edge
        // max flow indicates if we can send at least X bears, if its >= x
        // try to look for a higher bound
        if (max_flow >= x) {
            left = mid;
        } else {
            right = mid;
        }
    }
```
### Evacuation
Teaches about precomputing the possibility to add an edge

So you find the time for the reactor to bfs and contaminate each cell
Find the bfs for each scientist to reach each cell.

Add an edge for flow given that the scientist can reach that cell b4 contamination

When bfs for the scientist, if you end up dying without reacihng a pod, then
stop the bfs from further exploring!!!

Just return for each scientist cell, every capsule they can reach,
dont care about the inner edges juts immediate connection with cap INFINITY, USEFUL TIP.

Then just find max flow.

Direction helpful ting this for reactor
```cpp
vector<pair<int, int>> directions = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};

pair<int, int> direc = directions[d];
int nx = x + direc.first;
int ny = y + direc.second;

if (nx >= 0 && nx < n && ny >= 0 && ny < n) {
    if (scis[nx][ny] != 'Y' && scis[nx][ny] != 'Z' && contamTime[nx][ny] == INF) {
        contamTime[nx][ny] = contamTime[x][y] + 1;
        q.push({nx, ny});
    }
}

```