# Heaps

A heap is a data structure totally ordered w.r.t a relation <img src="/tex/markdowns/tex/a40cf44401e8d184f6e1662d21b4d61b.svg?invert_in_darkmode&sanitize=true" align=middle width=12.785434199999989pt height=20.908638300000003pt/> (a generalization of comparison, can be <img src="/tex/markdowns/tex/c85a67d18322c7784f40a29a9fd19c86.svg?invert_in_darkmode&sanitize=true" align=middle width=12.785434199999989pt height=20.908638300000003pt/> in min-heaps and <img src="/tex/markdowns/tex/a27bd5e00db840936296ead0783388e7.svg?invert_in_darkmode&sanitize=true" align=middle width=12.785434199999989pt height=20.908638300000003pt/> in max-heaps). They are used to implement priority queues.

Binary heaps are usually represented as trees, which can be converted from arrays (see slides). The characterizing relation, called **heap property**, is valid only hierarchically and not between siblings nodes (as opposed to binary trees, where we have that the rightmost node is > than the leftmost on the same level).

In the Heapify method presented in slides, <img src="/tex/markdowns/tex/a40cf44401e8d184f6e1662d21b4d61b.svg?invert_in_darkmode&sanitize=true" align=middle width=12.785434199999989pt height=20.908638300000003pt/> represent the relation of the heap and there is an error in the comparison: it is `H[j]` <img src="/tex/markdowns/tex/a40cf44401e8d184f6e1662d21b4d61b.svg?invert_in_darkmode&sanitize=true" align=middle width=12.785434199999989pt height=20.908638300000003pt/> `H[m]` instead of `H[j]` <img src="/tex/markdowns/tex/a40cf44401e8d184f6e1662d21b4d61b.svg?invert_in_darkmode&sanitize=true" align=middle width=12.785434199999989pt height=20.908638300000003pt/> `m`.

* Binary heap has height <img src="/tex/markdowns/tex/2f154d01749e01a0a601ac00b55c8f0c.svg?invert_in_darkmode&sanitize=true" align=middle width=38.278313699999984pt height=22.831056599999986pt/>
  
* Level <img src="/tex/markdowns/tex/2f2322dff5bde89c37bcae4116fe20a8.svg?invert_in_darkmode&sanitize=true" align=middle width=5.2283516999999895pt height=22.831056599999986pt/> contains <img src="/tex/markdowns/tex/dbfbc774c0df39e0608c7005591cefd8.svg?invert_in_darkmode&sanitize=true" align=middle width=12.442998149999992pt height=27.91243950000002pt/> nodes at most.
  
* Each call at heapify cost at most <img src="/tex/markdowns/tex/2f154d01749e01a0a601ac00b55c8f0c.svg?invert_in_darkmode&sanitize=true" align=middle width=38.278313699999984pt height=22.831056599999986pt/>.

* Thus, the total cost of building a heap has a cost of **at most** <img src="/tex/markdowns/tex/e858a3b440ea6ca779c9d19a4a87e190.svg?invert_in_darkmode&sanitize=true" align=middle width=303.43146899999994pt height=31.780732499999996pt/>

* The number of nodes having height h is <img src="/tex/markdowns/tex/d874267a25a0978f46377bebcb39a767.svg?invert_in_darkmode&sanitize=true" align=middle width=41.295274349999985pt height=24.65753399999998pt/> at most.

* Heapify perform at most <img src="/tex/markdowns/tex/b398c91d807c0a0ca02008ddb9f353d4.svg?invert_in_darkmode&sanitize=true" align=middle width=32.10988604999999pt height=22.831056599999986pt/> operations:

<p align="center"><img src="/tex/markdowns/tex/83a351cd62f3db18b86e6fe96b964be9.svg?invert_in_darkmode&sanitize=true" align=middle width=461.65479194999995pt height=43.715357399999995pt/></p>

Since <img src="/tex/markdowns/tex/508e38f7de9e78e2d3f296c24de0443e.svg?invert_in_darkmode&sanitize=true" align=middle width=119.69231009999997pt height=28.92634470000001pt/> when <img src="/tex/markdowns/tex/33412ef745465ed0a3ba81fa120b3eec.svg?invert_in_darkmode&sanitize=true" align=middle width=38.82599489999999pt height=21.18721440000001pt/> and we used <img src="/tex/markdowns/tex/b5b2f7c7587c5e3990e3bf8076c34787.svg?invert_in_darkmode&sanitize=true" align=middle width=39.13192964999999pt height=27.77565449999998pt/> since it is a binary heap.

## Decreasing a key w.r.t. <img src="/tex/markdowns/tex/a40cf44401e8d184f6e1662d21b4d61b.svg?invert_in_darkmode&sanitize=true" align=middle width=12.785434199999989pt height=20.908638300000003pt/>: Complexity

While heapify proceeds from the root to the leaves of the heap,
the procedure to preserve the heap property after decreasing a
key value w.r.t. <img src="/tex/markdowns/tex/a40cf44401e8d184f6e1662d21b4d61b.svg?invert_in_darkmode&sanitize=true" align=middle width=12.785434199999989pt height=20.908638300000003pt/> (increase for <img src="/tex/markdowns/tex/a27bd5e00db840936296ead0783388e7.svg?invert_in_darkmode&sanitize=true" align=middle width=12.785434199999989pt height=20.908638300000003pt/>, decrease for <img src="/tex/markdowns/tex/c85a67d18322c7784f40a29a9fd19c86.svg?invert_in_darkmode&sanitize=true" align=middle width=12.785434199999989pt height=20.908638300000003pt/>) moves the problem up to the root by performing switches.

Since the complexity of a switch is constant and the height of the tree is <img src="/tex/markdowns/tex/6931c25b0d6a07c96e4160eac934c79d.svg?invert_in_darkmode&sanitize=true" align=middle width=33.83944574999999pt height=22.831056599999986pt/>, the total complexity is <img src="/tex/markdowns/tex/0d4b7f5b66e994af32a32cfa26868d53.svg?invert_in_darkmode&sanitize=true" align=middle width=59.62030469999999pt height=24.65753399999998pt/>.

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

Heap sort has complexity  <img src="/tex/markdowns/tex/ff514eba41c59f90c20d895e80719763.svg?invert_in_darkmode&sanitize=true" align=middle width=72.2268393pt height=24.65753399999998pt/>, but the creation of the heap with complexity <img src="/tex/markdowns/tex/272e3ab168729ac17efd78e4c03be40f.svg?invert_in_darkmode&sanitize=true" align=middle width=35.43774299999999pt height=24.65753399999998pt/> should be also taken into account.