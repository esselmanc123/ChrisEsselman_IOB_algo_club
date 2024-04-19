
#include <iostream>
#include <fstream>
#include <string>
#include <cstring> 
#include <vector>
#include <cmath>
#include <cstdlib>
#include <time.h>

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

    //Set seed for rand
    srand(time(0));

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
        cout << d_graph[i].k_one_mer << "->";
        for (int j = 0; j < d_graph[i].indices_pointing.size(); j++)
        {
            cout << d_graph[d_graph[i].indices_pointing[j]].k_one_mer;
            if (j < d_graph[i].indices_pointing.size() - 1)
            {
                cout << ",";
            }
        }
        cout << "\n";
    }
    return 0;
}