# String-matching

An **alphabet** $\Sigma$ is a set of symbols e.g. $\{0, 1, a, \dots, z\}$

A **string** is a sequence of symbols contained in an alphabet.

$\Sigma^*$ is the set of all strings built on alphabet $\Sigma$, including the empty string $\epsilon$.

Two strings $x,y \in \Sigma^*$ can be concatenated as $xy$.

If two strings are both prefixes or suffixes of the same string and one is smaller than the other, then one is necessarily the prefix/suffix of the other.

We can say that a string $P$ (pattern) occurs inside a longer string $T$ (text) if we can find a slice of $T$ such that:

$$T[s+1 \dots s+m] = P$$

Where $s$ is the **shift** (positive integer) for $P$ in $T$ and $m$ is the length of $P$. A shift is called **valid** if the aforementioned equation is verified.

The string-matching problems requires to find all the valid shifts for a pattern $P$ inside a text $T$.

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

The complexity is $O(|P| * |T|)$, which may be fine for small patterns but for large ones may be inefficient.

A better idea is to look for repetition inside prefixes and suffixes of the pattern. We can exploit repetition inside the pattern in order to reduce the number of matchings.

E.g. Let's assume to have matched $P_5 = [a, b, a, b, a]$, where $P_3 = [a,b,a]$ is the largest pattern to be both prefix and suffix of the pattern. For $P_3$ the largest pattern to satisfy the same condition is $P_1 = [a]$, while for $P_1$ it is $\epsilon$.

In this process, we are finding $\pi^*[q] = \{\pi[q], \pi^2[q], \dots, \pi^t[q]\}$ (the set of all prefixes of $P_q$ that are also suffixes for it.)

Knowing that if a $\pi[q] > 0$ then $\pi[q] - 1 \in \pi^*[q-1]$, where $\pi^*[q]$ is the result of the **Prefix-function iteration lemma**, the set of all the prefixes of $P_q$.

We then have that:

$\pi[q] = 0 \;\;\;\;\;\;\;\;\;\;\;\;\;\;\;\;\;\;\;\;\;\;\;\;\;\;\;\;\;\;\;\; \text{if}  \;\;\;\; E_{q-1} = 0$
$\pi[q] = 1 + \max\{k \in E_{q-1}\} \;\;\;\; \text{otherwise}$


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

Since the number of executions of the while loop is bounded by the number of times $k$ gets increased, we have that the complexity is equal to $\Theta(|P|)$.
