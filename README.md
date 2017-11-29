fiboheap
========

C++ STL-like Fibonacci heap and queue for fast priority queues with mutable keys.

This is a header-only implementation of:
* Fibonacci Heap: a fast heap with mutable keys;
  Implementation follows Cormen et al. (2009) "Fibonacci Heaps," in Introduction to Algorithms, 3rd ed. Cambridge: MIT Press, pp. 505-530.
* Fibonacci Queue: a priority queue based on Fibonacci heap. This is basically a Fibonacci heap with an added fast store for retrieving nodes, and decrease their key as needed. Useful for search algorithms (e.g. Dijkstra, heuristic, ...).

The heap and queues are targeted at projects that are relunctant to rely on Boost for a simple Fibonacci heap or queue.

Compile with:
```
make
```

Performance on an `Intel Core i7-7820HQ CPU @ 3.9GHz`:
```
Fib push time delta: 0.804602
STL push time delta: 0.150856
Fib read time delta: 3.1695
STL read time delta: 1.60995e-07

```
