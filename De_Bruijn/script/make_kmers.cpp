//Chris Esselman
//Sequence alignment 9.21.23

#include <iostream>
#include <fstream>
#include <string>
#include <cstring>  

using namespace std;

bool is_number(string& s)
{
    for (int i = 0; i < s.length(); i++)
    {
        if (!isdigit(s[i]))
        {
            return 0;
        }
    }
    return 1; 
}

int main(int argc, char **argv)
{
    if (argc != 3)
	{
		cout << "Usage: ./make_kmers fasta1 k_mer-length \n"; 
		return 1;
	}

	//open files and open the stream
	ifstream fasta1(argv[1]);

	if (!fasta1.is_open())
	{
		cout << "File 1 is not open \n" << "Usage: ./make_kmers fasta1 k_mer-length \n";
		return 2;
	}

	//Make sure files are fasta files
	char Z1;
	fasta1.get(Z1);
	if (Z1!='>')  
	{
		cout << "File 1 does not appear to be in FASTA format\n" << "Usage: ./make_kmers fasta1 k_mer-length  \n";
		return 4;
	}
	//Skip first line
	while (Z1 != '\n')  fasta1.get(Z1);
    //Determine length of sequences
    long fasta1_length = 0;
    while (fasta1.get(Z1))
	{
		if (isalpha(Z1))
		{
			fasta1_length++;

		}
	}
    string holder = argv[2];
    if (is_number(holder) != 1)
    {
        cout << "k_mer-length has to be a number!" << "\n";
        return 10;
    }
    long kmer_length = stoi(argv[2]);
    if (kmer_length < 2 || kmer_length > fasta1_length)
    {
        cout << "This is not a valid number for kmer length" << "\n";
        cout << "Kmer length must be 2 <= kmer_length <= length_of_sequence" << "\n";
        return 11;
    }
    fasta1.clear();
	fasta1.seekg(0, ios::beg);
    fasta1.get(Z1);
    while (Z1 != '\n')  fasta1.get(Z1);
    char sequence1[fasta1_length];
    int i1 = 0;
	while (fasta1.get(Z1))
	{
		if (isalpha(Z1))
		{
			sequence1[i1] = toupper(Z1);
			i1++;
		}
	}
    //Close files
	fasta1.close();

    for (int i = 0; i < fasta1_length - kmer_length; i++)
    {
        for (int j = 0; j < kmer_length; j++)
        {
            cout << sequence1[i+j];
        }
        cout << "\n";
    }
	
}