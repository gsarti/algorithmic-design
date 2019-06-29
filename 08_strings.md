# String-matching

An **alphabet** <img src="/tex/813cd865c037c89fcdc609b25c465a05.svg?invert_in_darkmode&sanitize=true" align=middle width=11.87217899999999pt height=22.465723500000017pt/> is a set of symbols e.g. <img src="/tex/60a1e3987b77417a66bd95a94c7d94b4.svg?invert_in_darkmode&sanitize=true" align=middle width=101.07479249999999pt height=24.65753399999998pt/>

A **string** is a sequence of symbols contained in an alphabet.

<img src="/tex/2c5a8059590679076dd3b434439e0a64.svg?invert_in_darkmode&sanitize=true" align=middle width=18.607373399999986pt height=22.63846199999998pt/> is the set of all strings built on alphabet <img src="/tex/813cd865c037c89fcdc609b25c465a05.svg?invert_in_darkmode&sanitize=true" align=middle width=11.87217899999999pt height=22.465723500000017pt/>, including the empty string <img src="/tex/7ccca27b5ccc533a2dd72dc6fa28ed84.svg?invert_in_darkmode&sanitize=true" align=middle width=6.672392099999992pt height=14.15524440000002pt/>.

Two strings <img src="/tex/dc9ac8e54deb7e41242c2e7bfe2f96fc.svg?invert_in_darkmode&sanitize=true" align=middle width=64.04858954999999pt height=22.63846199999998pt/> can be concatenated as <img src="/tex/65f1b48fb5f326a680b0f7393b9d8b6d.svg?invert_in_darkmode&sanitize=true" align=middle width=18.044213549999988pt height=14.15524440000002pt/>.

If two strings are both prefixes or suffixes of the same string and one is smaller than the other, then one is necessarily the prefix/suffix of the other.

We can say that a string <img src="/tex/df5a289587a2f0247a5b97c1e8ac58ca.svg?invert_in_darkmode&sanitize=true" align=middle width=12.83677559999999pt height=22.465723500000017pt/> (pattern) occurs inside a longer string <img src="/tex/2f118ee06d05f3c2d98361d9c30e38ce.svg?invert_in_darkmode&sanitize=true" align=middle width=11.889314249999991pt height=22.465723500000017pt/> (text) if we can find a slice of <img src="/tex/2f118ee06d05f3c2d98361d9c30e38ce.svg?invert_in_darkmode&sanitize=true" align=middle width=11.889314249999991pt height=22.465723500000017pt/> such that:

<p align="center"><img src="/tex/b9d233783348e8132f1b1799a3f5af06.svg?invert_in_darkmode&sanitize=true" align=middle width=158.6791239pt height=16.438356pt/></p>

Where <img src="/tex/6f9bad7347b91ceebebd3ad7e6f6f2d1.svg?invert_in_darkmode&sanitize=true" align=middle width=7.7054801999999905pt height=14.15524440000002pt/> is the **shift** (positive integer) for <img src="/tex/df5a289587a2f0247a5b97c1e8ac58ca.svg?invert_in_darkmode&sanitize=true" align=middle width=12.83677559999999pt height=22.465723500000017pt/> in <img src="/tex/2f118ee06d05f3c2d98361d9c30e38ce.svg?invert_in_darkmode&sanitize=true" align=middle width=11.889314249999991pt height=22.465723500000017pt/> and <img src="/tex/0e51a2dede42189d77627c4d742822c3.svg?invert_in_darkmode&sanitize=true" align=middle width=14.433101099999991pt height=14.15524440000002pt/> is the length of <img src="/tex/df5a289587a2f0247a5b97c1e8ac58ca.svg?invert_in_darkmode&sanitize=true" align=middle width=12.83677559999999pt height=22.465723500000017pt/>. A shift is called **valid** if the aforementioned equation is verified.

The string-matching problems requires to find all the valid shifts for a pattern <img src="/tex/df5a289587a2f0247a5b97c1e8ac58ca.svg?invert_in_darkmode&sanitize=true" align=middle width=12.83677559999999pt height=22.465723500000017pt/> inside a text <img src="/tex/2f118ee06d05f3c2d98361d9c30e38ce.svg?invert_in_darkmode&sanitize=true" align=middle width=11.889314249999991pt height=22.465723500000017pt/>.

The easiest way to solve the problem is to proceed iteratively by selecting a shift, trying to match the characters when possible.

```pseudocode
DEF Naive_PM(T, P)
    Valid <- []
    FOR S <- 0 UP TO |T| - |P|:
        q <- 1
        WHILE q < |P| AND T[s+q] = P[q]:
            q <- q+1
        END WHILE
        IF q > |P| THEN # We matched all characters
            Valid.APPEND(S)
        ENDIF
    ENDFOR
ENDDEF
```

The complexity is <img src="/tex/8b7f03fd57291fc826f519f4a7432961.svg?invert_in_darkmode&sanitize=true" align=middle width=84.29680379999998pt height=24.65753399999998pt/>, which may be fine for small patterns but for large ones may be inefficient.

A better idea is to look for repetition inside prefixes and suffixes of the pattern. We can exploit repetition inside the pattern in order to reduce the number of matchings.

E.g. Let's assume to have matched <img src="/tex/c64ab8e64d47bd29db74a391fdee3ee8.svg?invert_in_darkmode&sanitize=true" align=middle width=118.37877314999999pt height=24.65753399999998pt/>, where <img src="/tex/b1d567073cbaf70fc3c213b525b50837.svg?invert_in_darkmode&sanitize=true" align=middle width=88.02305654999998pt height=24.65753399999998pt/> is the largest pattern to be both prefix and suffix of the pattern. For <img src="/tex/638b19a3067e22632f9c720fbf5d22c8.svg?invert_in_darkmode&sanitize=true" align=middle width=17.10619349999999pt height=22.465723500000017pt/> the largest pattern to satisfy the same condition is <img src="/tex/b43b54261c0b32011c9e6edba901f1f6.svg?invert_in_darkmode&sanitize=true" align=middle width=57.667339949999985pt height=24.65753399999998pt/>, while for <img src="/tex/197fa3a18e4a8b8c7df669d007476133.svg?invert_in_darkmode&sanitize=true" align=middle width=17.10619349999999pt height=22.465723500000017pt/> it is <img src="/tex/7ccca27b5ccc533a2dd72dc6fa28ed84.svg?invert_in_darkmode&sanitize=true" align=middle width=6.672392099999992pt height=14.15524440000002pt/>.

In this process, we are finding <img src="/tex/8346dd1f7ac0ba3697aff26be7e11f8f.svg?invert_in_darkmode&sanitize=true" align=middle width=210.99307679999998pt height=26.76175259999998pt/> (the set of all prefixes of <img src="/tex/58b27195f98e451041ebabd2e132b174.svg?invert_in_darkmode&sanitize=true" align=middle width=16.99148549999999pt height=22.465723500000017pt/> that are also suffixes for it.)

Knowing that if a <img src="/tex/b44f7051b6e0dcaaf30ce173a5e587c7.svg?invert_in_darkmode&sanitize=true" align=middle width=57.15746354999998pt height=24.65753399999998pt/> then <img src="/tex/42691275df434b4a7634fe200d7a9422.svg?invert_in_darkmode&sanitize=true" align=middle width=138.31027484999998pt height=24.65753399999998pt/>, where <img src="/tex/13dd0e24b4d310d8e4a279880a28b172.svg?invert_in_darkmode&sanitize=true" align=middle width=34.57771184999999pt height=24.65753399999998pt/> is the result of the **Prefix-function iteration lemma**, the set of all the prefixes of <img src="/tex/58b27195f98e451041ebabd2e132b174.svg?invert_in_darkmode&sanitize=true" align=middle width=16.99148549999999pt height=22.465723500000017pt/>.

We then have that:

<img src="/tex/76e96d979867dbb2b52ee6872fa6f769.svg?invert_in_darkmode&sanitize=true" align=middle width=297.48392355000004pt height=24.65753399999998pt/>
<img src="/tex/ed888af3503304254110267229287e8c.svg?invert_in_darkmode&sanitize=true" align=middle width=275.6497755pt height=24.65753399999998pt/>


A pseudocode version of the algorithm:

```pseudocode
DEF Compute_Prefix_Function(P)
    Pi <- INIT_ARRAY(|P|)
    Pi[1] <- 0
    k <- 0
    FOR q <- 2 UP TO |P|
        WHILE k > 0 AND P[k + 1] != P[q]
            k <- Pi[k]
        ENDWHILE
        IF P[k + 1] = P[q]
            k += 1
        ENDIF
        Pi[q] <- k
    ENDFOR
    RETURN Pi
ENDDEF
```

Since the number of executions of the while loop is bounded by the number of times <img src="/tex/63bb9849783d01d91403bc9a5fea12a2.svg?invert_in_darkmode&sanitize=true" align=middle width=9.075367949999992pt height=22.831056599999986pt/> gets increased, we have that the complexity is equal to <img src="/tex/b421f4be0c830927725d62c23f0d95a4.svg?invert_in_darkmode&sanitize=true" align=middle width=47.54008709999999pt height=24.65753399999998pt/>.
