# branchtest2wopenmp
two small windows c programs that test some branching stuff with and without openmp

results using clang -O0/3 -march=x86-64-v4 (-fopenmp) with times from my 9950x3d
-----------------------------------------------------------------------------------------------------
|   O0:                                             |   O3:                                         |
|                                                   |                                               |
|   sorted branching:                               |   sorted branching:                           |
|   sorting time: 0.001000                          |   sorting time: 0.001000                      |
|   time: 24.658000, sum = 143810716347133          |   time : 4.970000, sum = 3167413000000        |
|                                                   |                                               |
|   sorted branching 2:                             |   sorted branching 2:                         |
|   sorting time: 0.001000                          |   sorting time: 0.001000                      |
|   time: 28.632000, sum = 3111741000000            |   time: 1.850000, sum = 3167413000000         |
|                                                   |                                               |
|   sorted branchless:                              |   sorted branchless:                          |
|   sorting time: 0.001000                          |   sorting time:0.0010000                      |
|   time: 29.768000, sum = 3111741000000            |   time: 1.853000, sum = 3167413000000         |
|                                                   |                                               |
|   unsorted branching:                             |   unsorted branching:                         |
|   time: 58.103000, sum = 3111741000000            |   time: 12.612000, sum = 143867524565520      |
|                                                   |                                               |
|   unsorted branching 2:                           |   unsorted branching 2:                       |
|   time: 76.905000, sum = 3111741000000            |   time: 1.859000, sum = 3167413000000         |
|                                                   |                                               |
|   unsorted branchless:                            |   unsorted branchless:                        |
|   time: 30.198000, sum = 3111741000000            |   time: 1.863000, sum = 3167413000000         |
|                                                   |                                               |
|----------------------------------------------------------------------------------------------------
|   O0omp:                                          |   O3omp:                                      |
|                                                   |                                               |
|   sorted branching:                               |   sorted branching:                           |
|   sorting time: 0.001264                          |   sorting time: 0.001226                      |
|   time taken: 1.784808, sum = 3137536000000       |   time: 0.458700, sum = 313753600000          |
|                                                   |                                               |
|   sorted branching 2:                             |   sorted branching 2:                         |
|   sorting time: 0.001679                          |   sorting time: 0.001711                      |
|   time taken: 2.089344, sum: 3137536000000        |   time: 0.146047, sum = 3137536000000         |
|                                                   |                                               |
|   sorted branchless:                              |   sorted branchless:                          |
|   sorting time: 0.001741                          |   sorting time: 0.001706                      |
|   time taken: 2.051072, sum: 3137536000000        |   time: 0.150383, sum = 3137536000000         |
|                                                   |                                               |
|   unsorted branching:                             |   unsorted branching:                         |
|   time taken: 1.545571, sum: 3137536000000        |   time: 0.601991, sum = 3137536000000         |
|                                                   |                                               |
|   unsorted branching 2:                           |   unsorted branching 2:                       |
|   time taken: 1.936755, sum: 3137536000000        |   time: 0.158733, sum = 3137536000000         |
|                                                   |                                               |
|   unsorted branchless:                            |   unsorted branchless:                        |
|   time taken: 2.260621, sum: 3137536000000        |   time: 0.148286, sum = 3137536000000         |
-----------------------------------------------------------------------------------------------------
