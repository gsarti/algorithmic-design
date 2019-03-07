# Matrix Multiplication

The naïve implementation of the matrix multiplication algorithm has complexity $O(n^3)$.

To make it more efficient, we may apply a **Divide and Conquer** strategy by splitting the two squared matrices in $k$ blocks of size $s$. The value of the block $C_{ij}$ will be given by:

$$C_{ij} = \Sigma_{l = 0}^k A_{il} \times B_{lj}$$

The products can be computed recursively, by splitting subsequent blocks in more blocks using the basic recursive algorithm that splits a matrix in four blocks. At each level of recursive splitting, we are dividing by two the size of the matrix on which we are operating.

Since each block C_{ij} for a block requires eight multiplications, the complexity at the i-th level of recursion is

$$T_M(n) = c(\frac{n}{2^i})^2 \times 8^i = c(n^2) \times 2^i$$

Since we are performing binary splitting, the height of the recursion tree is $log_2(n)$

$$T_M(n) = \Sigma_{i = 0}^{log_2(n)} cn^22^i$$
$$ = cn^2 \Sigma_{i = 0}^{log_2(n)}2^i$$
$$= cn^2\frac{2^{1+ log_2(n)} - 1}{2 - 1}$$
$$= cn^2(2^{(1 + log_2(n))} -1 )$$
$$=cn^2\times2\times2^{log_2(n)}- cn^2$$
$$ = 2cn^3 - cn^2 \in \Theta(n^3)$$

This doesn't held better complexity than the previous algorithm, but can be reformulated using **Strassen's Algorithm** in order to reduce the number of multiplications (recursive calls) and increasing the number of sums, which are anyways of fixed complexity $\Theta(n^2)$.

The new complexity equation is:

$$T_M(n) = 7 \times T_M(\frac{n}{2}) + \Theta(n^2)$$

since the products have been reduced to 7. The final asymptotic complexity of Strassen algorithm is $\in \Theta(n^{log_27}) \approx \Theta(n^{2.81})$ .

The algorithm is not in-place, a.k.a. it requires a non-constant amount of additional memory. This shows how a careful handling of the auxiliary memory may make the difference in implementation, simply by reducing the number of recursive calls.