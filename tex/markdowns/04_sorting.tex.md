# Searching and Sorting

Complexity in unsorted array: at least $O(n)$ (scan all elements).

Complexity in sorted array: $O(log n)$ with dichotomic search.

## Insertion sort

Switch places when right elements is smaller than left element, iterating through the whole array. Complexity: $O(n^2)$ (n to iterate through the array, n to switch elements in the worst case).

## Quick sort

Select pivot, split array in two subarrays (with all elements respectively smaller and greater than pivot) and recursively apply the same procedure on these subarrays.

Complexity to perform the splitting in subarrays: $O(n)$. Can be done in place (see slides).

Worst case total complexity: $O(n^2)$ if one of the subarrays is always empty since it becomes $T_Q(n) = T_q(n-1) + \Theta(n)$.

Best case: When the splitting procedure produces two arrays which have constant ratio, for all subtree we have to perform n operations for the splitting and the number of subtrees approaches $log n$, so the complexity is $\Theta(n\space log \space n)$ ($O(n \space log \space n) = \Omega(n \space log \space n)$).

## Heapsort

Any sorting algorithm using comparisons can be modeled as a decision-tree model, with a number of leaves (that represent all possible permutations of elements in the array to be sorted) equal to $n!$ and thus the minimum complexity for the worst case scenario in any case is $O(n \log n)$.

By introducing ad-hoc constraints such as a bounded domain and a uniform distribution of the array values, we can achieve sorting in linear time.

## Select

We can find the ith element in an unsorted array by applying the partition algorithm we used in quicksort to partition. In the worst case (the splitting between values smaller and greater than the pivot is unbalanced) the complexity is $O(n^2)$. To avoid this, we should choose optimally the pivot by splitting the array in chunks and use as pivot the median of medians of all chunks. In this case, the complexity becomes, for example:

$$T_S(n) = \begin{cases} \Theta(1) & \text{if}\; n = 1 \\ T_S(\lceil n/5 \rceil) + T_S(7n/10 + 6) + \Theta(n) & \text{otherwise}\end{cases}$$

for a vector splitted in 5 chunks, where $T_S(n/5)$ is the complexity of sorting each chunk and $T_S(7n/10 + 6) + \Theta(n)$ is an upper bound for the number of elements smaller or equall to the selected pivot $m$.

The algorithm is optimal for chunk size of 5, and is useful to upper bound the number of operations.

```
DEF SELECT_PIVOT(A, l = 1, c=|A|)
    FOR i <- 0 UP TO (r-l)/5
        INSERTION_SORT(A, 5*i+l, MIN(5*i+l+4, r))
    ENDFOR

    FOR i <- 0 UPTO (r-l)/5
        SWAP(A, l+i, MAX(5*i+l+2), r))
    ENDFOR
    RETURN SELECT(A, ((r-l)/5 + 1)/2, l , l+ (r-l)/5)
ENDDEF
```