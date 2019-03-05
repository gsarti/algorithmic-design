# Matrix Multiplication

The naïve implementation of the matrix multiplication algorithm has complexity <img src="/tex/90846c243bb784093adbb6d2d0b2b9d0.svg?invert_in_darkmode&sanitize=true" align=middle width=43.02219404999999pt height=26.76175259999998pt/>.

To make it more efficient, we may apply a **Divide and Conquer** strategy by splitting the two squared matrices in <img src="/tex/63bb9849783d01d91403bc9a5fea12a2.svg?invert_in_darkmode&sanitize=true" align=middle width=9.075367949999992pt height=22.831056599999986pt/> blocks of size <img src="/tex/6f9bad7347b91ceebebd3ad7e6f6f2d1.svg?invert_in_darkmode&sanitize=true" align=middle width=7.7054801999999905pt height=14.15524440000002pt/>. The value of the block <img src="/tex/34787a737f93a895f3ca427befc45c25.svg?invert_in_darkmode&sanitize=true" align=middle width=22.504257599999992pt height=22.465723500000017pt/> will be given by:

<p align="center"><img src="/tex/5f83d2aa5f2bbbe8415acd14ccdc4d49.svg?invert_in_darkmode&sanitize=true" align=middle width=143.71903755pt height=19.4813124pt/></p>

The products can be computed recursively, by splitting subsequent blocks in more blocks using the basic recursive algorithm that splits a matrix in four blocks. At each level of recursive splitting, we are dividing by two the size of the matrix on which we are operating.

Since each block C_{ij} for a block requires eight multiplications, the complexity at the i-th level of recursion is

<p align="center"><img src="/tex/b26a0ddf55b243e0bc8c697f1a0dfccd.svg?invert_in_darkmode&sanitize=true" align=middle width=239.48106929999997pt height=29.47417935pt/></p>

Since we are performing binary splitting, the height of the recursion tree is <img src="/tex/7b85e54feb1e67c7e5a0c33fe3d1738b.svg?invert_in_darkmode&sanitize=true" align=middle width=51.06374789999999pt height=24.65753399999998pt/>

<p align="center"><img src="/tex/d8d23469335269a7d624966b988d6b82.svg?invert_in_darkmode&sanitize=true" align=middle width=160.62790754999997pt height=21.7509732pt/></p>
<p align="center"><img src="/tex/d4eeebcc2e3a1b3bce2dec55723c6c75.svg?invert_in_darkmode&sanitize=true" align=middle width=109.21196385pt height=21.7509732pt/></p>
<p align="center"><img src="/tex/9460cfac11dca5ffb36407b203240867.svg?invert_in_darkmode&sanitize=true" align=middle width=139.61579445pt height=38.361919199999996pt/></p>
<p align="center"><img src="/tex/af15b7d02b6890b6aff567c929ae25b3.svg?invert_in_darkmode&sanitize=true" align=middle width=160.70265254999998pt height=19.526994300000002pt/></p>
<p align="center"><img src="/tex/f39ca9bb636b3a5be7b7ee7b0a9f8bd3.svg?invert_in_darkmode&sanitize=true" align=middle width=184.71489465pt height=16.7872782pt/></p>
<p align="center"><img src="/tex/917a05b27d399283d84bb39fe84208e3.svg?invert_in_darkmode&sanitize=true" align=middle width=157.2755547pt height=18.312383099999998pt/></p>

This doesn't held better complexity than the previous algorithm, but can be reformulated using **Strassen's Algorithm** in order to reduce the number of multiplications (recursive calls) and increasing the number of sums, which are anyways of fixed complexity <img src="/tex/7f673488709d91c2cf326d97e5a437c3.svg?invert_in_darkmode&sanitize=true" align=middle width=42.81220349999999pt height=26.76175259999998pt/>.

The new complexity equation is:

<p align="center"><img src="/tex/c1aa47e5b7208ce8dec759d0b33eeed4.svg?invert_in_darkmode&sanitize=true" align=middle width=210.77631135pt height=29.47417935pt/></p>

since the products have been reduced to 7. The final asymptotic complexity of Strassen algorithm is <img src="/tex/a0bf961bafa7f3792db19e25f604a91a.svg?invert_in_darkmode&sanitize=true" align=middle width=81.87828495pt height=27.91243950000002pt/>.

The algorithm is not in-place, a.k.a. it requires a non-constant amount of additional memory. This shows how a careful handling of the auxiliary memory may make the difference in implementation, simply by reducing the number of recursive calls.