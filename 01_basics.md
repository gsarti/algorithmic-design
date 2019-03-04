# Algorithms Fundamentals

## The Halting Problem and Computational Models

Let *h* be the function that establishes whether any program p executed with inputs i ends or run forever.

For any *f(a,b)*, we define a *gf(i)* such that it returns 0 if *f(i,i) = 0* and infinity otherwise.

The Halting problem is a computer science counterpart of Godel's Theorem.

The **Church-Turing Thesis** states that every effectively calculable function is computable, i.e. there exists an implementation for any given algorithm. For this reason, we can infer that all reasonable computational models (which allow some standard minor operations, such as assignment, looping, etc.) are equivalent and thus we can use the easiest ones for our purposes.

Our computational model (The **Random Access Machine, RAM**) includes variables to store data, arrays, int and float constants, algebraic functions, assignment, pointers (without pointer arithmetic), conditional and loop statements, procedures and functions. However, the RAM model doesn't have the hardware limitations, memory hierarchy and execution time that we find in real hardware, since it represents a generalization of the latter.

## Time Complexity

To measure the efficiency of a program, we may use **execution time**. For algorithms this is not a realistic estimation since it relies heavily on hardware and context (language, compiles, memory handling, CPU, size of inputs, etc.).

For algorithms, we may use **scalability** instead, since it measures the capacity of a system of handling input growth for a range of inputs, estimating the relation between input size and execution time.

In order to estimate scalability, we are simply looking at **asymptotic behaviour**, excluding constants and using the big O notation.

If we have a constant and an input value for a function *g(n)* such that g is <= than a *f(n)* for all values of n after the input value, then we say that *g(n)* belongs to O(f(n)). O notation sets an upper bound for the growth of complexity in a program.

Big omega notation is the same concept, but in the best case scenario when f shrinks instead of when g grows, setting a lower bound. Finally, big Theta notation is the intersection between the two previous concepts, defining the exact behaviour of a function.

## Other Notions

### Abstract Data Types

