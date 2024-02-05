
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
#include <sstream>

using namespace std;

int main(int argc, char **argv) 
{
    //Make sure the correct number of arguments
	if (argc != 4)  
    {
		cout << "Use as:  " << argv[0] << " <Comma-delimited_text_file col_names? rownames?>\n";
		cout << "Example: " << argv[0] << " Table.txt 0 1 \n";
		return 0;
	}

	//Make sure the file can be opened
	ifstream InFile(argv[1]);
	if (!InFile.is_open())  
    {
		cout << "Cannot open file \"" << argv[1] << "\"\n";
		return 1;
	}

    //Read in true or false to see if the data has variable names
    int is_there_colnames = stoi(argv[2]);
    //transform(skip_col_names.begin(),skip_col_names.end(),skip_col_names.begin(),::toupper);

    //Read in true or false to see if the data has rownames
    int is_there_rownames = stoi(argv[3]);
    //transform(skip_rownames.begin(),skip_rownames.end(),skip_rownames.begin(),::toupper);

    //Vectors to hold the headers, rownames, and variables
    vector<string> col_names;
    vector<string> row_names;
    vector<vector<string> > the_data;

    //Read in the headers and the row names
	string Str;

    //Counters for rows and the columns
    int counterX = 0;
    int counterY = 0;

	//Read each line of txt file
	while (!InFile.eof())  
    {
        if (is_there_colnames == 1 && is_there_rownames == 1)
        {
            int skip = 0;
            if (counterX == 0)
            {
                //get the line
                getline(InFile,Str);
                //Put header line into sstram to parse
                istringstream ss(Str);
                //Blank string variable to parse with
                string substr;
                //Read the column names in
                while (getline(ss,substr,','))
                {
                    if (skip != 0)
                    {
                        col_names.push_back(substr);
                    }
                    skip++;
                }
                counterX++;
            }
            else
            {
                //get the line
                getline(InFile,Str);
                //Put header line into sstram to parse
                istringstream ss(Str);
                //Blank string variable to parse with
                string substr;
                //make the vector longer
                the_data.push_back(vector<string>());
                //Read the column names in
                while (getline(ss,substr,','))
                {
                    if (skip == 0)
                    {
                        row_names.push_back(substr);
                    }
                    else
                    {
                        the_data[counterX - 1].push_back(substr);
                    }
                    skip++;
                }
                row_names.push_back(col_names[0]);
                counterX++;
            }
            
        }
        else if (is_there_colnames == 0 && is_there_rownames == 1)
        {

        }
        /*
        if (strcmp(skip_headers.c_str(),"YES"))
        {
            //Put header line into sstram to parse
            istringstream ss(Str);

            //Blank string variable to parse with
            string substr;

            while (getline(ss, substr,','))
            {
                headers.push_back(substr);
                cout << t;
                t++;
            }
        }
        counterX++;
        */
        for (int i = 0; i < col_names.size(); i++)
        {
            cout << col_names[i] << "\n";
            cout << row_names[i] << "\n";
        }
    }
}
    /*

        //Put line in sstream to parse
        istringstream ss(Str);

        //Blank string variable to parse with
        string substr;

        //Get label
        getline(ss, substr, ',');
        Label.push_back(substr);
        aa_numbers.push_back(vector<double>());

        //Get numbers till end of line
        while (getline(ss,substr,'\t'))
        {
            aa_numbers[counterX].push_back(stof(substr));
            if (counterX == 0)
            {
                counterY++;
            }
        }
        counterX++;

	}
	
    return 0;

}
*/