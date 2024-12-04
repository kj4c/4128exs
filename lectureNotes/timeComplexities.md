### **Graphs**

1. **Kruskal's Algorithm**:
   - **Time Complexity**: \( O(E \log E) \)
   - **Description**: Finds the Minimum Spanning Tree (MST) of a graph by sorting edges and adding them in increasing weight order, using a union-find structure.

2. **Prim's Algorithm**:
   - **Time Complexity**: \( O(E + V \log V) \) with a priority queue.
   - **Description**: Finds the MST by starting from a node and adding the minimum-weight edge that connects the tree to a new vertex.

3. **Breadth-First Search (BFS)**:
   - **Time Complexity**: \( O(V + E) \)
   - **Description**: Explores the shortest path in an unweighted graph layer by layer.

4. **Depth-First Search (DFS)**:
   - **Time Complexity**: \( O(V + E) \)
   - **Description**: Explores as far as possible along each branch before backtracking.

5. **Lowest Common Ancestor (LCA)**:
   - **Time Complexity**: \( O(\log N) \) per query (after \( O(N \log N) \) preprocessing with Binary Lifting).
   - **Description**: Finds the lowest common ancestor of two nodes in a tree.

6. **Tarjan's Algorithm**:
   - **Time Complexity**: \( O(V + E) \)
   - **Description**: Finds strongly connected components (SCCs) in a directed graph using DFS.

7. **Dijkstra's Algorithm**:
   - **Time Complexity**: \( O(E + V \log V) \) with a priority queue.
   - **Description**: Finds the shortest path from a source node to all other nodes in a graph with non-negative edge weights.

8. **Bellman-Ford Algorithm**:
   - **Time Complexity**: \( O(V \cdot E) \)
   - **Description**: Finds shortest paths from a source node to all nodes in a graph, handling negative weights.

9. **Floyd-Warshall Algorithm**:
   - **Time Complexity**: \( O(V^3) \)
   - **Description**: Computes shortest paths between all pairs of vertices in a graph.

---

### **Maths**

1. **Is a Prime Number**:
   - **Time Complexity**: \( O(\sqrt{N}) \)
   - **Description**: Checks if a number is prime by testing divisors up to its square root.

2. **Prime Factorization**:
   - **Time Complexity**: \( O(\sqrt{N}) \) for trial division; faster with precomputed primes.
   - **Description**: Breaks a number into its prime factors.

3. **Sieve of Eratosthenes**:
   - **Time Complexity**: \( O(N \log \log N) \)
   - **Description**: Precomputes prime numbers up to \( N \).

4. **Goldbach's Conjecture**:
   - **Time Complexity**: Depends on the sieve; \( O(N \log \log N) \) for preprocessing primes.
   - **Description**: States that every even number greater than 2 is the sum of two primes (verified for specific \( N \)).

5. **GCD (Greatest Common Divisor)**:
   - **Time Complexity**: \( O(\log \min(A, B)) \)
   - **Description**: Finds the greatest common divisor of two numbers using the Euclidean algorithm.

6. **Matrix Multiplication**:
   - **Time Complexity**: \( O(N^3) \), faster with Strassen's or other advanced algorithms.
   - **Description**: Multiplies two \( N \times N \) matrices.

7. **Matrix Exponentiation**:
   - **Time Complexity**: \( O(N^3 \log P) \)
   - **Description**: Computes \( A^P \) for an \( N \times N \) matrix \( A \) efficiently using repeated squaring.

---

### **Flow**

1. **Dinic's Algorithm**:
   - **Time Complexity**: \( O(V^2 \cdot E) \) or better for unit-capacity graphs.
   - **Description**: Computes the maximum flow in a graph using level graphs and blocking flows.

---

### **Computational Geometry**

1. **Convex Hull**:
   - **Time Complexity**: \( O(N \log N) \)
   - **Description**: Finds the smallest convex polygon that contains all points in a set.

2. **Cross Product**:
   - **Time Complexity**: \( O(1) \)
   - **Description**: Computes the vector cross product to determine orientation or area.

---

### **Dynamic Programming**

1. **Knapsack Problem**:
   - **Time Complexity**: \( O(N \cdot W) \), where \( W \) is the capacity.
   - **Description**: Finds the maximum value that can be achieved in a knapsack with weight constraints.

2. **Bitmask DP**:
   - **Time Complexity**: \( O(2^N \cdot N) \)
   - **Description**: Solves problems involving subsets, like TSP or subset partitioning, using bitmasks.

3. **Traveling Salesperson Problem (TSP)**:
   - **Time Complexity**: \( O(2^N \cdot N) \) with DP.
   - **Description**: Finds the shortest route visiting all nodes exactly once and returning to the start.

4. **Segment Cover**:
   - **Time Complexity**: \( O(N^2) \) or \( O(N \log N) \) with greedy techniques.
   - **Description**: Finds the minimal set of segments to cover a range or interval.