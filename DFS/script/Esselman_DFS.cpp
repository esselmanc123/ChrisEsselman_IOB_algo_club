
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
        string origin_node;
        //Get label
        getline(ss, origin_node, '-');
        // Boolean to tell if origin node exists
        bool is_there_origin = false;
        //Index of origin node
        int origin_node_int;
        //Check to see if origin node is already in the graph
        for (int j = 0; j < graph.size(); j++)
        {
            if (graph[j].node_name == origin_node)
            {
                is_there_origin = true;
                origin_node_int = j;
            }
        }
        //If the origin node does not exist add it to the graph
        Node dummy;
        if (is_there_origin == false)
        {
            dummy.node_name = origin_node;
            graph.push_back(dummy);
            origin_node_int = graph.size() - 1;
        }
        //Save to where the origin node is pointing towards
        vector<string> nodes_towards;
        string towards_dummies;
        while (getline(ss,towards_dummies,','))
        {
            nodes_towards.push_back(towards_dummies);
        }

        //Add to the graph depending on the size of the pointing ndoes
        for (int j = 0; j < nodes_towards.size(); j++)
        {
            //See if the towards node exists and if it does save the index of its location
            bool does_towards_node_exist = false;
            int towards_node_int;
            for (int k = 0; k < graph.size(); k++)
            {
                if (graph[k].node_name == nodes_towards[j])
                {
                    does_towards_node_exist = true;
                    towards_node_int = k;
                }
            }
            // Add it if it does not exist
            if (does_towards_node_exist == false)
            {
                dummy.node_name = nodes_towards[j];
                graph.push_back(dummy);
                towards_node_int = graph.size() - 1;
            }
            // Make things point to the right thing
            graph[origin_node_int].indices_pointing.push_back(towards_node_int);
            graph[origin_node_int].edges_graph.push_back(false);
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
		cout << "File 1 is not open \n" << "Usage: ./Esselman_DFS node_file \n";
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

    construct_graph(d_graph,names);

    for (int i = 0; i < d_graph.size(); i++)
    {
        cout << d_graph[i].node_name << "->";
        for (int j = 0; j < d_graph[i].indices_pointing.size(); j++)
        {
            cout << d_graph[d_graph[i].indices_pointing[j]].node_name;
            if (j < d_graph[i].indices_pointing.size() - 1)
            {
                cout << ",";
            }
        }
        cout << "\n";
    }
    return 0;
}