# Vantage-Point-Tree
Shared memory vantage point tree implementation, given a data set of d-dimensional points 𝑋. The structure is used to perform the 𝑘 nearest neighbor search (kNN) of the points on the vantage-point tree as introduced in the publication:
*Peter N Yianilos,[a link](http://web.cs.iastate.edu/~honavar/nndatastructures.pdf) Data structures and algorithms for nearest neighbor search in general metric spaces, In
Fourth annual ACM-SIAM symposium on Discrete algorithms. Society for Industrial and Applied Mathe-
matics Philadelphia, volume 93, pages 311–321, 1993.*
# How it works
The algorithm is based on a very simple idea: select a point as the vantage point, compute the distance of every point
to the vantage point and split the points according to the median distance.

And then repeat the same on the inner and outer partitions until no point is left, to build a balanced binary tree.
