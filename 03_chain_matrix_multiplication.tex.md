# Chain Matrix Multiplication

We want to reduce the total number of scalar product performed for the multiplication of a chain of given matrices $A_1, A_2, \dots, A_n$ through applying optimal parenthesizations.

The ideal way to perform this is to recursively compute optimal parenthesizations and use dynamic programming to avoid the number of possible parenthesization to explode.

We recursively compute the product of all matrices between $A_i$ and $A_j$ by assuming that the optimal split is $(A_i \dots A_k)(A_{k+1} \dots A_j)$ with k ranging from $i$ to $j-1$ and summing the recursively computed product between $A_i$ and $A_k$, between $A_{k+1}$ and $A_j$ and the total number of scalar products needed to compute the product between the two recursive subproblems (represented by the dimensions of the resulting matrices $p_{i-1}$, $p_k$ and $p_j$). The product of those matrices is then minimized w.r.t. $k$. The stopping condition is that the product is 0 when $i = j$, which represent the case in which we are simply trying to compute the product between two matrices, in which the number of scalar product is given simply by the scalar products between the two matrices (no recursive subproblems).

We use a matrix $m$ to store the number of multiplication computed that way and a matrix $s$ to store the k that minimizes the number of multiplication for the current subproblem (e.g. k = 3 means that we obtain the best parenthesization by placing a parenthesis after the third element of the chain).

Inside $m$, in position $(i,j)$ i will find the minimal number of scalar multiplications needed to solve the chain matrix multiplication between matrices $A_i$ and $A_j$ of the original chain $A_1 \dots A_i \dots A_j \dots A_n$.

The complexity of the algorithm is $O(n^3)$.