
#include <iostream>
#include <fstream>
#include <string>
#include <cstring> 
#include <vector>
#include <cmath>
#include <cstdlib>
#include <time.h>
#include <sstream>

using namespace std;

struct Node {
    string node_name;
    vector<int> indices_pointing;
    vector<bool> edges_graph;
};

void construct_graph(vector<Node> &graph, vector<string> names2)
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


        //Figure out how to do this without having the indexing variables
        //Add Nodes and edges to the graph
    */

   for (int i = 0; i < names2.size(); i++)
   {
        //Put line in sstream to parse
        istringstream ss(names2[i]);

        //Blank string variable to parse with
        string substr;
        //Get label
        getline(ss, substr, '-');
        Node dummy;
        if ((is_there_left_node == false) && (is_there_right_node == false))
        {
            //Add the two nodes to the graph
            dummy.node_name = left;
            graph.push_back(dummy);
            dummy.node_name = right;
            graph.push_back(dummy);
            //Add pointer from the left to the right and add edge flag
            graph[graph.size() - 2].indices_pointing.push_back(graph.size() - 1);
            graph[graph.size() - 2].edges_graph.push_back(false);
        }
        else if ((is_there_left_node == false) && (is_there_right_node == true))
        {
            //Make a new left node
            dummy.node_name = left;
            graph.push_back(dummy);
            //Point the new node to the old right node
            graph[graph.size() - 1].indices_pointing.push_back(right_pos);
            graph[graph.size() - 1].edges_graph.push_back(false);
        }
        else if ((is_there_left_node == true) && (is_there_right_node == false))
        {
            //Make a new right node
            dummy.node_name = right;
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
		cout << "Usage: ./Esselman_DFS node_file \n"; 
		return 1;
	}

	//open files and open the stream
	ifstream node_file(argv[1]);

	if (!node_file.is_open())
	{
		cout << "File 1 is not open \n" << "Usage: ./Esselman_De_Bruijn k-mer_file \n";
		return 2;
	}

    //Save the kmers in a vector of strings
	vector<string> names;

    // Blank sting variable
    string str;

    while (getline(node_file,str))
    {
        names.push_back(str);
    }

    //Construct the graph
    vector<Node> d_graph;

    for (int i = 0; i < names.size(); i++)
    {
        cout << names[i] << "\n";
    }

    //construct_graph(d_graph,names);

    // for (int i = 0; i < d_graph.size(); i++)
    // {
    //     cout << d_graph[i].node_name << "->";
    //     for (int j = 0; j < d_graph[i].indices_pointing.size(); j++)
    //     {
    //         cout << d_graph[d_graph[i].indices_pointing[j]].node_name;
    //         if (j < d_graph[i].indices_pointing.size() - 1)
    //         {
    //             cout << ",";
    //         }
    //     }
    //     cout << "\n";
    // }
    return 0;
}