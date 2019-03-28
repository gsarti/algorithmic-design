# Heaps

A heap is a data structure totally ordered w.r.t a relation $\preceq$ (a generalization of comparison, can be $\leq$ in min-heaps and $\geq$ in max-heaps). They are used to implement priority queues.

Binary heaps are usually represented as trees, which can be converted from arrays (see slides). The characterizing relation, called **heap property**, is valid only hierarchically and not between siblings nodes (as opposed to binary trees, where we have that the rightmost node is > than the leftmost on the same level).

In the Heapify method presented in slides, $\preceq$ represent the relation of the heap and there is an error in the comparison: it is `H[j]` $\preceq$ `H[m]` instead of `H[j]` $\preceq$ `m`.

* Binary heap has height $log_2 \space n$
  
* Level $l$ contains $2^l$ nodes at most.
  
* Each call at heapify cost at most $log_2 \space n$.

* Thus, the total cost of building a heap has a cost of **at most** $\Sigma_{l=0}^{log_2n}2^l \times c \times \log_2 n =  n \space log_2 \space n \in O(n \space log \space n)$

* The number of nodes having height h is $[\frac{n}{2^{h+1}}]$ at most.

* Heapify perform at most $c * h$ operations:

$$\Sigma_{h =0}^{log_2 n} \frac{n}{2^{h+1}}*c*h \leq cn \Sigma_{h=0}^\infty \frac{h}{2^h} = cn \frac{\frac{1}{2}}{(1 - \frac{1}{2})^2} = 2*c*n \in O(n)$$

Since $\Sigma_{h=0}^\infty \frac{h}{2^h} = \frac{a}{(1-a)^2}$ when $a < 1$ and we used $a = \frac{1}{2}$ since it is a binary heap.

## Decreasing a key w.r.t. $\preceq$: Complexity

While heapify proceeds from the root to the leaves of the heap,
the procedure to preserve the heap property after decreasing a
key value w.r.t. $\preceq$ (increase for $\geq$, decrease for $\leq$) moves the problem up to the root by performing switches.

Since the complexity of a switch is constant and the height of the tree is $\log n$, the total complexity is $O(\log n)$.

```
DEF DecreaseKey(H, i, value):
    IF H[i] <= value:
        ERROR("I can only decrease key values")
    ENDIF
    H[i] <- value
    WHILE NOT (IsRoot(i) OR H[Parent(i)] <= H[i])
        Swap(H, i, Parent(i))
        i <- Parent(i)
    ENDWHILE
ENDDEF
```

## Heap Sort

Heap sort has complexity  $O(n \log n)$, but the creation of the heap with complexity $\Theta(n)$ should be also taken into account.