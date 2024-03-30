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
#include <cmath>

using namespace std;

struct Node {
    string k_one_mer;
    vector<int> indices_pointing;
    vector<bool> edges_graph;
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
    cout << "Kmerssize: " << Kmers.size() << "\n";
    for (int i = 0; i < Kmers.size(); i++)
    {
        //Split into left and right k-1mers
        string left = "";
        string right = "";
        for (int j = 0; j < Kmers[1].size() - 1; j++)
        {
            left = left + Kmers[i][j];
            right = right + Kmers[i][j+1];
        }
        //Check if the k-1mer has been created yet and if it has find the index to that node
        bool is_there_left_node = false;
        bool is_there_right_node = false;
        int left_pos;
        int right_pos;
        for (int j = 0; j < graph.size(); j++)
        {
            if (left == graph[j].k_one_mer)
            {
                is_there_left_node = true;
                left_pos = j;
                
            }
            if (right == graph[j].k_one_mer)
            {
                is_there_right_node = true;
                right_pos = j;
            }
        }
        //Figure out how to do this without having the indexing variables
        //Add Nodes and edges to the graph
        Node dummy;
        if ((is_there_left_node == false) && (is_there_right_node == false))
        {
            //Add the two nodes to the graph
            dummy.k_one_mer = left;
            graph.push_back(dummy);
            dummy.k_one_mer = right;
            graph.push_back(dummy);
            //Add pointer from the left to the right and add edge flag
            graph[graph.size() - 2].indices_pointing.push_back(graph.size() - 1);
            graph[graph.size() - 2].edges_graph.push_back(false);
        }
        else if ((is_there_left_node == false) && (is_there_right_node == true))
        {
            //Make a new left node
            dummy.k_one_mer = left;
            graph.push_back(dummy);
            //Point the new node to the old right node
            graph[graph.size() - 1].indices_pointing.push_back(right_pos);
            graph[graph.size() - 1].edges_graph.push_back(false);
        }
        else if ((is_there_left_node == true) && (is_there_right_node == false))
        {
            //Make a new right node
            dummy.k_one_mer = right;
            graph.push_back(dummy);
            //Make old node point to new node
            graph[left_pos].indices_pointing.push_back(graph.size() - 1);
            graph[left_pos].edges_graph.push_back(false);
        }
        else
        {
            //Make old node point to old node
            graph[left_pos].indices_pointing.push_back(right_pos);
            graph[left_pos].edges_graph.push_back(false);
        }
    }
}

bool check_eulerian(vector<Node> graph, vector<int> &locs)
{
    /*
    A directed connected graph is Eulerian if and only if it has at most 2 semi-balanced nodes
    https://www.cs.jhu.edu/~langmea/resources/lecture_notes/assembly_dbg.pdf

    semi-balanced node - indegree differes from outdegree by 1
    */

   int semi_balanced = 0;
   int out_semi_idx;
   int in_semi_idx;
   for (int i = 0; i < graph.size(); i++)
   {
        int in_degree = 0;
        int out_degree = graph[i].edges_graph.size();
        //Find the indegrees
        for (int j = 0; j < graph.size(); j++)
        {
            if (i!=j)
            {
                for (int k = 0; k < graph[j].indices_pointing.size(); k++)
                {
                    if (graph[j].indices_pointing[k] == i)
                    {
                        in_degree++;
                    }
                }
            }
        }
        if (abs(in_degree - out_degree) >= 2)
        {
            return false;
        }
        else if (in_degree - out_degree == 1)
        {
            semi_balanced++;
            in_semi_idx = i;
        }
        else if (in_degree - out_degree == -1)
        {
            semi_balanced++;
            out_semi_idx = i;
        }
   }
   if (semi_balanced > 2 || semi_balanced == 1)
   {
        return false;
   }
   if (semi_balanced == 2)
   {
        locs.push_back(out_semi_idx);
        locs.push_back(in_semi_idx);
        return true;
   }
   else 
   {
        return true;
   }

}

int subtour(vector<Node> &graph, int start_node, bool is_semi_eulerian)
{
    //Do the subtours
    int current = start_node;
    //Subtour if the graph is eulerian
    if (is_semi_eulerian == false)
    {
        //variable just to get into the starting node
        int w = 1;
        //Keep lopping until reach a cycle
        while (current != start_node || w == 1)
        {
            w++;
            //Pick a next unvisited edge from the current node
            bool check_if_visited = true;
            int next_edge;
            while (check_if_visited == true)
            {
                next_edge = rand()%graph[current].edges_graph.size();
                if (graph[current].edges_graph[next_edge] == false)
                {
                    check_if_visited = false;
                }
            }
            current = graph[current].indices_pointing[next_edge];
            graph[current].edges_graph[next_edge] = true;
            cout << graph[current].k_one_mer[graph[current].k_one_mer.size() - 1];
        }
        // Save the locations of nodes from the previous subtour. Find a node that does not have a visited edge. If no unvisited edges, just return current.
        return current;
    }
    else 
    {

    }
    return current;
}

void eulerian_walk(vector<Node> graph, int start_node, bool is_semi_eulerian)
{
    // Loop through subtours until every edge of the graph is visited
    bool all_edges_visited = false;
    int start_node_new = start_node;
    while (all_edges_visited == false)
    {
        // Keep checking if a node is unvisited
        bool single_edge_unvisited = false;
        start_node_new = subtour(graph,start_node_new, is_semi_eulerian);
        for (int i = 0; i < graph.size(); i++)
        {
            for (int j = 0; j < graph[i].edges_graph.size();j++)
            {
                if (graph[i].edges_graph[j] == false)
                {
                    single_edge_unvisited = true;
                }
            }
        }
        if (!single_edge_unvisited)
        {
            all_edges_visited = true;
        }
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

    //Construct the graph
    vector<Node> d_graph;

    construct_graph(d_graph,kmers);

    for (int i = 0; i < d_graph.size(); i++)
    {
        cout << "original node: " << d_graph[i].k_one_mer << "\n";

        cout << "nextsize: " << d_graph[i].indices_pointing.size() << "\n";
        cout << "edgessize: " << d_graph[i].edges_graph.size() << "\n";
        for (int j = 0; j < d_graph[i].indices_pointing.size(); j++)
        {
            cout << d_graph[d_graph[i].indices_pointing[j]].k_one_mer << "\n";
        }

        cout << "************************\n";
        cout << "************************\n";
    }
    
    //Check to see if a Eulerian walk is possible

    vector<int> location_semieulerians;
    if (!check_eulerian(d_graph, location_semieulerians))
    {
        cout << "An Eulerian walk is not possible with this dataset" << "\n";
        return 3;
    }
    bool semi_eulerian = false;

    cout << "Sequence after the walk" << "\n";
    cout << "**********************" << "\n";
    cout << "Is Semi_eulerian: " << location_semieulerians.size() << "\n";
    if (!location_semieulerians.empty())
    {
        // Case for when the graph is semieulerian
        for (int i = 0; i < d_graph[location_semieulerians[0]].k_one_mer.size() - 1; i++)
        {
            cout << d_graph[location_semieulerians[0]].k_one_mer[i];
        }
        semi_eulerian = true;
        eulerian_walk(d_graph,location_semieulerians[0],semi_eulerian);
        
    }
    else
    {
        // Case for when the graph is eulerian
        int seed = rand() % d_graph.size(); //Not truly random. Unsure how to fix this
        eulerian_walk(d_graph,seed,semi_eulerian);
    }
    return 0;
}