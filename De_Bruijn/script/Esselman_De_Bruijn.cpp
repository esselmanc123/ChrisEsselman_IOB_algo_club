/*
Psuedocode

1. Save the k-1 mers of the set of kmers
2. Draw a multi-graph (try doing this using a linked list)
https://www.bitdegree.org/learn/linked-list-c-plus-plus

a. vertices - k-1mers
b. edge - both nodes make up original sequence


***** Want to Visit Every Edge Once *******

3. Guarunteed to have a Eulerian trail (visit every edge once). Follow it to construct the final sequence
Hierholzer's algorithm below. Going to be doing a directed graph
https://algorithms.discrete.ma.tum.de/graph-algorithms/hierholzer/index_en.html

    1. Check if graph can acutally contain a Eulerian Trial
        a. At least one edge
        b. Connected
        c. All nodes have even degree (Eulerian) or Exactly 2 nodes have odd degree (semi-Eulerian)
    2. Mark every edge as unvisited
    3. If graph is Eulerian, pick random start node
    If graph is semi-Eulerian - choose one of two nodes with odd degrees
    4. See all unvisited edges and choose one randomly
    5. New node from chosen edge is new active node
    6. Check for circle (compare active node to start node)
    7. Repeat step 4, 5, 6
    8. If back in circle, integrate subtour into tour?
        - The algorithm replaces the start/end node of the subtour in the tour by all nodes of the subtour.
        - I think this is looking for if all the edges are visited?
    
    Example of not all visted below

    9. Start at arbitrary node from previous subtour that still has unvisited edges
    10. Randomly choose edge that was not part of previous tour to visit
    11. New node from chosen edge is new active node
    12. Check for circle (compare active node to start node)
    13. Repeat steps 10, 11, 12
    14. Once a circle is done repeat step 8
    15. Can just put the two subtours one after another

    Another really good website to check out
    http://debruijnsequence.org/db/home

*/

#include <iostream>
#include <fstream>
#include <string>
#include <cstring> 
#include <vector>

using namespace std;

struct Node {
    string k_one_mer;
    vector<Node *> nexts;
    vector<bool > visited;
};

void construct_graph(vector<Node> &graph, vector<string> Kmers)
{
    /*
        Psuedocode for linked list-

        - Do kind of a recursive algorithm
        1. While splitting the left and right draw and edge between the two
        2. Look for nodes that are the same and make them into one.
            - need to collapse edges as well. Pointers help with this. Keep the same number of edges but now point to collapsed node
        3. Keep doing this until have unique nodes

        Use vector erase to get rid of specific elements

        https://www.youtube.com/watch?v=f-ecmECK7lw
    */
    //Do the splitting of the kmers
    for (int i = 0; i < Kmers.size(); i++)
    {
        string left = "";
        string right = "";
        for (int j = 0; j < Kmers[1].size() - 1; j++)
        {
            left = left + Kmers[i][j];
            right = right + Kmers[i][j+1];
        }
        bool is_there_left_node = false;
        bool is_there_right_node = false;
        for (int j = 0; j < graph.size(); j++)
        {
            if (left.compare(graph[j].k_one_mer) == 0)
            {
                is_there_left_node = true;
            }
            if (right.compare(graph[j].k_one_mer) == 0)
            {
                is_there_right_node = true;
            }
        }
        Node dummy;
        dummy.k_one_mer = left;
        graph.push_back(dummy);
        dummy.k_one_mer = right;
        graph.push_back(dummy);
    }

}
int main(int argc, char **argv)
{
    if (argc != 2)
	{
		cout << "Usage: ./Esselman_De_Bruijn k-mer_file \n"; 
		return 1;
	}

	//open files and open the stream
	ifstream kmer_file(argv[1]);

	if (!kmer_file.is_open())
	{
		cout << "File 1 is not open \n" << "Usage: ./Esselman_De_Bruijn k-mer_file \n";
		return 2;
	}

    //Save the kmers in a vector of strings
	vector<string> kmers;

    // Blank sting variable
    string str;

    while (getline(kmer_file,str))
    {
        kmers.push_back(str);
    }

    //Save the k-1mers in a vector of strings
    vector<Node> d_graph;


    construct_graph(d_graph,kmers);
    

    // Now create the linked list with vertices as the k-1mers and edges being if they overlap
    //Directed graph where left is pointing to the right

    for (int i = 0; i < d_graph.size(); i++)
    {

    }

    // cout << "kmers size :  " << kmers.size() << "\n";
    // cout << "kmers-1 size :" << d_graph.size() << "\n";

    // for (int i = 0; i < d_graph.size(); i++)
    // {
    //     cout << d_graph[i] << "\n";
    // }
	
}