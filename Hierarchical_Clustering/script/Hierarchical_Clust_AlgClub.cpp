
/*
    Chris Esselman Hierarchical Clustering for Algorithms Club for IOB

    2.3.2024

    Going to be writing the divisive hierarchical algorithm that I found from the book:
    Finding Groups in Data: An Introduction to Cluster Analysis (Kaufman 1990)

    Still need to read in the data. Some of the arguments will be to tell if to skip headers
    or the skip the row names. That will be my first task. 


*/

#include <iostream>
#include <fstream>
#include <vector> 

using namespace std;

int main(int argc, char **argv) 
{
    //Checking if the amount of input arguments  is correct
	if (argc==1)  
    {
		cout << "Use as:  " << argv[0] << " <Comma-delimited text file>\n";
		cout << "Example: " << argv[0] << " Table.txt\n";
		return 0;
	}
	
    // Opening the file:
	ifstream InFile(argv[1]);
	if (!InFile.is_open())  
    {
		cout << "Cannot open file \"" << argv[1] << "\"\n";
		return 1;
	}

    vector<double> X,Y;

    // Now I can read the actual numbers:
	string Str;
//	for (int i=0;i<rows;++i)  {
// The line above cannot be used now because we do not know the number of rows. 
// Instead, we'll keep reading as long as there is another line in the file
	while (getline(InFile,Str,','))  
    {
// The getline above will fail (return false) if are at the end of the file
        if (strcmp(Str.c_str(),"NA") == 0)
        {
            X.push_back(0.0);
        }
        else
        {
            X.push_back(stof(Str));
        }
		  // convert Str to a double and add the value as the new last element to the vector X
// Now read the rest of the line:
		if (getline(InFile,Str))  
        {
            if (strcmp(Str.c_str(),"NA") == 0)
            {
                Y.push_back(0.0);
            }
            else
            {
                Y.push_back(stof(Str));
            }
		}
		else  
        {
// This will happen if there was no tab in the line being read because the getline(InFile,Str) above would have failed
			cout << "The input file is corrupted or has incorrect format. Quitting ...\n";
			exit (1);
		}
	}
    // Print the data I read:
	cout << "Data read from the file:\nX\tY\n";
	for (int i=0;i<X.size();++i)  cout << X[i] << "\t" << Y[i] << "\n";
	
    return 0;

}