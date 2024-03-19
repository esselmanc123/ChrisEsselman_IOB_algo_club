/*
Psuedocode

1. Save the k-1 mers of the set of kmers
2. Draw a multi-graph (try doing this using a linked list)
https://www.bitdegree.org/learn/linked-list-c-plus-plus

a. vertices - k-1mers
b. edge - both nodes make up original sequence

***** Want to Visit Every Edge Once *******

3. Guarunteed to have a Eulerian trail (visit every edge once). Follow it to construct the final sequence
Hierholzer's algorithm below
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

using namespace std;

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

	//Check Kmer length
	char Z1;
	//Skip first line
	while (Z1 != '\n')  kmer_file.get(Z1);
    //Determine length of sequences
    long kmer_file_length = 0;
    while (kmer_file.get(Z1))
	{
		if (isalpha(Z1))
		{
			kmer_file_length++;

		}
	}
    string holder = argv[2];
    }
    long kmer_length = stoi(argv[2]);
    if (kmer_length < 2 || kmer_length > kmer_file_length)
    {
        cout << "This is not a valid number for kmer length" << "\n";
        cout << "Kmer length must be 2 <= kmer_length <= length_of_sequence" << "\n";
        return 11;
    }
    kmer_file.clear();
	kmer_file.seekg(0, ios::beg);
    kmer_file.get(Z1);
    while (Z1 != '\n')  kmer_file.get(Z1);
    char sequence1[kmer_file_length];
    int i1 = 0;
	while (kmer_file.get(Z1))
	{
		if (isalpha(Z1))
		{
			sequence1[i1] = toupper(Z1);
			i1++;
		}
	}
    //Close files
	kmer_file.close();

    for (int i = 0; i < kmer_file_length - kmer_length; i++)
    {
        for (int j = 0; j < kmer_length; j++)
        {
            cout << sequence1[i+j];
        }
        cout << "\n";
    }
	
}