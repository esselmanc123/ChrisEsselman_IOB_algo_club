/*
Psuedocode

1. Save the k-1 mers of the set of kmers
2. Draw a multi-graph (try doing this using a linked list)
https://www.bitdegree.org/learn/linked-list-c-plus-plus

a. vertices - k-1mers
b. edge - both nodes make up original sequence

3. Guarunteed to have a Eulerian trail (visit every edge once). Follow it to construct the final sequence
Hierholzer's algorithm below
https://algorithms.discrete.ma.tum.de/graph-algorithms/hierholzer/index_en.html


*/