# Dynamic indexes

In a setting where the data present in a specific context is going to change often, we need a new data structure to perform the addition, the removal and the querying in the most efficient way (e.g. without having to pass through the whole structure to reorganize data after addition/deletion).

## Binary Search Trees (BST)

The tree is made by nodes having a **key** and a **value**, a **left and right child** (which will be set to NIL if they are not present), and possibly a **parent node**. The tree itself should have a **root** node, which is connected to all others hierarchically.

**Removing a node from BST:**

```pseudocode
DEF Transplant(T,x,y)
    IF x.Parent = NIL
        T.Root <- y
    ENDIF
    y.Parent <- x.Parent
    IF IsRightChild(x)
        y.Parent.Right <- y
    ELSE
        y.Parent.Left <- y
    ENDIF
ENDDEF
```

The strategy to delete a node with two children is to proceed in its right subtree to find the leftmost child (at most a child on the right), moving this node in the place of the one we want to delete and moving up the whole subtree from where the node has been moved.

BSTs without balancing may perform at worst as linked lists. However, balancing is an expensive operation if it's done globally. Thus, we may want to try and balance only the unbalanced part of the tree.

## Red-Black Trees

All nodes are either red or black. Root is black, all leaves (NIL) are black and all red nodes must have black children. Branches starting from any node must have the same number of black children.

Any RBT with n internal nodes has height of at most $2 \log_2(n+1)$ nodes. The ratio between the height of two branches should be at most $2$.
