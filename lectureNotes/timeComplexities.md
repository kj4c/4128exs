### **Heap (Min-Heap/Max-Heap)**

1. **Insertion**: \( O(\log N) \)
   - Adds a new element to the heap while maintaining the heap property.
2. **Deletion (Remove Min/Max)**: \( O(\log N) \)
   - Removes the smallest (min-heap) or largest (max-heap) element from the heap.
3. **Peek (Get Min/Max)**: \( O(1) \)
   - Returns the smallest (min-heap) or largest (max-heap) element without removing it.
4. **Build Heap**: \( O(N) \)
   - Constructs a heap from an unsorted array.

---

### **Range Tree (Segment Tree)**

1. **Build**: \( O(N) \)
   - Constructs the tree for a range query.
2. **Point Update**: \( O(\log N) \)
   - Updates a single element in the range.
3. **Range Query**: \( O(\log N) \)
   - Finds the result of a query (e.g., sum, min, max) over a subrange.

---

### **Union-Find (Disjoint Set Union, DSU)**

1. **Find (with path compression)**: \( O(\alpha(N)) \)
   - Finds the representative of a set containing an element, with \( \alpha(N) \) being the inverse Ackermann function (very small for practical inputs).
2. **Union (with union by rank)**: \( O(\alpha(N)) \)
   - Merges two sets into one, optimizing by rank/size.
3. **Connected (Are in Same Set)**: \( O(\alpha(N)) \)
   - Determines if two elements belong to the same set.

---

### **Stack**

1. **Push**: \( O(1) \)
   - Adds an element to the top of the stack.
2. **Pop**: \( O(1) \)
   - Removes the top element of the stack.
3. **Top/Peek**: \( O(1) \)
   - Returns the top element without removing it.

---

### **Set (Ordered Set, typically implemented as a balanced binary search tree)**

1. **Insertion**: \( O(\log N) \)
   - Adds an element in sorted order.
2. **Deletion**: \( O(\log N) \)
   - Removes an element while maintaining order.
3. **Find**: \( O(\log N) \)
   - Checks if an element exists.

---

### **Map (Ordered Map, typically implemented as a balanced binary search tree)**

1. **Insertion**: \( O(\log N) \)
   - Adds a key-value pair while maintaining order.
2. **Deletion**: \( O(\log N) \)
   - Removes a key-value pair.
3. **Access by Key**: \( O(\log N) \)
   - Finds a value associated with a key.

---

### **Unordered Map (Hash Map)**

1. **Insertion**: \( O(1) \) (average), \( O(N) \) (worst-case with hash collisions)
   - Adds a key-value pair.
2. **Deletion**: \( O(1) \) (average), \( O(N) \) (worst-case)
   - Removes a key-value pair.
3. **Access by Key**: \( O(1) \) (average), \( O(N) \) (worst-case)
   - Finds a value associated with a key.

---

### **Sparse Table**

1. **Build**: \( O(N \log N) \)
   - Constructs the table for range queries.
2. **Range Query (e.g., min, max)**: \( O(1) \)
   - Computes the result of a query over a range (non-updatable).

---

### **Prefix Sum**

1. **Build**: \( O(N) \)
   - Precomputes cumulative sums up to each index.
2. **Range Query**: \( O(1) \)
   - Computes the sum of elements in a subrange.
3. **Update**: \( O(N) \) (for standard prefix sums)
   - Updates a single element and recomputes prefix sums (not efficient; Fenwick Tree or Segment Tree is better for updates).

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
   - **Time Complexity**: \( O(V * E) \)
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
   - **Time Complexity**: \( O(V^2 * E) \) or better for unit-capacity graphs.
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
   - **Time Complexity**: \( O(N * W) \), where \( W \) is the capacity.
   - **Description**: Finds the maximum value that can be achieved in a knapsack with weight constraints.

2. **Bitmask DP**:
   - **Time Complexity**: \( O(2^N * N) \)
   - **Description**: Solves problems involving subsets, like TSP or subset partitioning, using bitmasks.

3. **Traveling Salesperson Problem (TSP)**:
   - **Time Complexity**: \( O(2^N * N) \) with DP.
   - **Description**: Finds the shortest route visiting all nodes exactly once and returning to the start.

4. **Segment Cover**:
   - **Time Complexity**: \( O(N^2) \) or \( O(N \log N) \) with greedy techniques.
   - **Description**: Finds the minimal set of segments to cover a range or interval.