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

## The Knuth-Morris-Pratt Algorithm

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

The prefix function is used to skip directly to the shift that can match at least the length of the smallest prefix-suffix of the pattern matched

Since the number of executions of the while loop is bounded by the number of times $k$ gets increased, we have that the complexity is equal to $\Theta(|P| + |T|)$. The complexity of the prefix function is $\Theta(|P|)$

## The Boyer-Moore-Galil Algorithm

The algorithm is different from the others because it performs the matching backwards. The algorithm was developed originally by Boyer and Moore having a complexity that is worse than KMP in worst case, until Galil added his rule to improve the worst case complexity. It exploits three main ingredients:

* **Good-suffix rule**: When we try to match our pattern (backwards) and there is a mismatch, we move to the left (the rightmost after the current one) inside the pattern to find another occurrence of the part that was already matched that is **preceded by a different character** or at the beginning of the pattern and try to match the newly chosen pattern backwards. Since it is basically the inverse of the prefix function, its complexity is still $\Theta(|P|)$.

* **Bad-character rule**: In addition to the good-suffix rule, when we are trying to perform the matching and there is a mismatch, we move to the left (the rightmost after the current one) inside the pattern to find the next occurrence of the character that was mismatched. If no occurrence is found, we can shift the pattern matching procedure to the character directly after the not-found character, since we know for sure that no pattern will match it. The complexity of this procedure is $\Theta(|P| + |\Sigma|)$, where $\Sigma$ is the alphabet used to build $T$.

* **Galil's rule**: If a match has been discovered and P is k-periodic (not necessarily complete, e.g. ABABA is a valid 2-periodic incomplete patter), we can shift our pattern forward by k and avoid to match all characters that were already matched in the previous step (we avoid a total of $|P| - k$ comparisons). This can be done in linear time w.r.t. the pattern length, aka $\Theta(|P|)$

We proceed as follows:

* Try to match P on T backwards with initial shift.

* If mismatch, select the largest shift among those suggested by the good-suffix and the bad-character rules.

* If a valid shift is found, apply Galil's rules.

This gives us a worst case of $\Theta(|P| + |T|)$, but most of the time in sublinear time.

## Multiple Patterns String Matching

We can use Boyer-Moore-Galil to try a multiple pattern matching (all subpatterns of a pattern), but the complexity of the approach is $O(|T| * \sum_i |P_i|)$, which isn't really optimal.

A more interesting approach is given by a tree-based solution, in which the tree contains all the paths for all possible combinations of subpatterns, having nodes with values equal to the shift needed to match the subpattern inside the pattern.

While this approach is linear w.r.t. patterns, the hard part is building a tree that conforms to the previously specified requirements.

The **active point** is the first node in the boundary path (following up the prefix functions from the longest path) that is NOT a leaf in the tree (in the example, the first left C is the active point since remounting through the prefix functions in red from the last leftmost node, it is the first one that is not a leaf). The **endpoint** is the first node coming before the active point having the added character as direct descendant.

The complexity of building a Suffix Trie is  $\Theta(\Sigma(T))$, where $\Sigma$ is the set of all substrings of T. We have that $|\Sigma(T)| \in O(|T|^2) \rightarrow O(|T|^2)$. This cost can be reduced by reducing redundancy.

Canonize steps take $O(|T|)$, while the steps to build the tree after canonizing take $\Theta(|T|)$, thus in total building the tree takes a complexity of $\Theta(n)$. This brings the total complexity for multiple pattern matching to $\Theta(|T|) + \Theta(\sum_i |P_i|)$, and the tree takes space $\Theta(|T|)$. However, this approach handles only one of the pattern valid shifts and may require up to $(2 + 1 + |\Sigma|) * |T|$ words of RAM, which can be way too much for tasks such as genome sequencing.

An approach used to fix this is **Suffix Array**, where arrays are used to store suffixes in lexicographical order and can be searched with dichotomic search.

