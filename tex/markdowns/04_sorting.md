# Searching and Sorting

Complexity in unsorted array: at least <img src="/tex/markdowns/tex/1f08ccc9cd7309ba1e756c3d9345ad9f.svg?invert_in_darkmode&sanitize=true" align=middle width=35.64773519999999pt height=24.65753399999998pt/> (scan all elements).

Complexity in sorted array: <img src="/tex/markdowns/tex/a1c8c40a7a2b24c00df91cd27124a705.svg?invert_in_darkmode&sanitize=true" align=middle width=57.27448814999999pt height=24.65753399999998pt/> with dichotomic search.

## Insertion sort

Switch places when right elements is smaller than left element, iterating through the whole array. Complexity: <img src="/tex/markdowns/tex/3987120c67ed5a9162aa9841b531c3a9.svg?invert_in_darkmode&sanitize=true" align=middle width=43.02219404999999pt height=26.76175259999998pt/> (n to iterate through the array, n to switch elements in the worst case).

## Quick sort

Select pivot, split array in two subarrays (with all elements respectively smaller and greater than pivot) and recursively apply the same procedure on these subarrays.

Complexity to perform the splitting in subarrays: <img src="/tex/markdowns/tex/1f08ccc9cd7309ba1e756c3d9345ad9f.svg?invert_in_darkmode&sanitize=true" align=middle width=35.64773519999999pt height=24.65753399999998pt/>. Can be done in place (see slides).

Worst case total complexity: <img src="/tex/markdowns/tex/3987120c67ed5a9162aa9841b531c3a9.svg?invert_in_darkmode&sanitize=true" align=middle width=43.02219404999999pt height=26.76175259999998pt/> if one of the subarrays is always empty since it becomes <img src="/tex/markdowns/tex/0a6cb93c79a502663a84ff57cac45ca3.svg?invert_in_darkmode&sanitize=true" align=middle width=188.70811409999996pt height=24.65753399999998pt/>.

Best case: When the splitting procedure produces two arrays which have constant ratio, for all subtree we have to perform n operations for the splitting and the number of subtrees approaches <img src="/tex/markdowns/tex/ee20768d0c86e301b4af834ddb6892e6.svg?invert_in_darkmode&sanitize=true" align=middle width=31.49362919999999pt height=22.831056599999986pt/>, so the complexity is <img src="/tex/markdowns/tex/ba689f0cdda81112bf45ac0b1235ed86.svg?invert_in_darkmode&sanitize=true" align=middle width=66.9313722pt height=24.65753399999998pt/> (<img src="/tex/markdowns/tex/974e3d119012c30d00d6969d1aa35330.svg?invert_in_darkmode&sanitize=true" align=middle width=155.07711284999996pt height=24.65753399999998pt/>).

## Heapsort

Any sorting algorithm using comparisons can be modeled as a decision-tree model, with a number of leaves (that represent all possible permutations of elements in the array to be sorted) equal to <img src="/tex/markdowns/tex/50c0357224674ab662b8ea5e5ca3eb8a.svg?invert_in_darkmode&sanitize=true" align=middle width=14.433101099999991pt height=22.831056599999986pt/> and thus the minimum complexity for the worst case scenario in any case is <img src="/tex/markdowns/tex/ff514eba41c59f90c20d895e80719763.svg?invert_in_darkmode&sanitize=true" align=middle width=72.2268393pt height=24.65753399999998pt/>.

By introducing ad-hoc constraints such as a bounded domain and a uniform distribution of the array values, we can achieve sorting in linear time.

## Select

We can find the ith element in an unsorted array by applying the partition algorithm we used in quicksort to partition. In the worst case (the splitting between values smaller and greater than the pivot is unbalanced) the complexity is <img src="/tex/markdowns/tex/3987120c67ed5a9162aa9841b531c3a9.svg?invert_in_darkmode&sanitize=true" align=middle width=43.02219404999999pt height=26.76175259999998pt/>. To avoid this, we should choose optimally the pivot by splitting the array in chunks and use as pivot the median of medians of all chunks. In this case, the complexity becomes, for example:

<p align="center"><img src="/tex/markdowns/tex/f6436ee36de5a515c956d9ecb683d30d.svg?invert_in_darkmode&sanitize=true" align=middle width=412.5167772pt height=49.315569599999996pt/></p>

for a vector splitted in 5 chunks, where <img src="/tex/markdowns/tex/4425d93979137ec4ba1f42e5a06647e0.svg?invert_in_darkmode&sanitize=true" align=middle width=58.21977974999998pt height=24.65753399999998pt/> is the complexity of sorting each chunk and <img src="/tex/markdowns/tex/e8fda6d16a7cf323e7bb4362e91f3eac.svg?invert_in_darkmode&sanitize=true" align=middle width=158.49753314999998pt height=24.65753399999998pt/> is an upper bound for the number of elements smaller or equall to the selected pivot <img src="/tex/markdowns/tex/0e51a2dede42189d77627c4d742822c3.svg?invert_in_darkmode&sanitize=true" align=middle width=14.433101099999991pt height=14.15524440000002pt/>.

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