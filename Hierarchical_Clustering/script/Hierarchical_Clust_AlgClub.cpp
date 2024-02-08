
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
#include <cmath>

using namespace std;

//Function to tell if a string can be converted to a number
//Using this function to convert input csv into data matrix
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

//Normalizing the data
void normalize(vector<vector<double> >& matrix)
{
    double means, sd;
    int row_size = matrix.size();
    int column_size = matrix[0].size();

    for (int j = 0; j < column_size; j++)
    {
        double adder = 0.0;
        for (int i = 0; i < row_size; i++)
        {
            adder = adder + matrix[i][j];
        }
        means = adder/row_size;
        adder = 0.0;
        for (int i = 0; i < row_size; i++)
        {
            adder += (matrix[i][j] - means) * (matrix[i][j] - means);
        }

        sd = sqrt(adder/row_size);

        for (int i = 0; i < row_size; i++)
        {
            matrix[i][j] = (matrix[i][j] - means)/sd;
        }
    }
}

void compute_distance_matrix(vector<vector<double> > data, vector<vector<double> >& blank_matrix)
{

}



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
    vector<vector<double> > the_data;

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
                the_data.push_back(vector<double>());
                //Read the column names in
                while (getline(ss,substr,','))
                {
                    if (skip == 0)
                    {
                        row_names.push_back(substr);
                    }
                    else
                    {
                        if (is_number(substr))
                        {
                            the_data[counterX - 1].push_back(stof(substr));
                        }
                        else
                        {
                            the_data[counterX - 1].push_back(0.0);
                        }
                        
                    }
                    skip++;
                }
                counterX++;
            }
            
        }
        else if (is_there_colnames == 0 && is_there_rownames == 1)
        {
            int skip = 0;
            //get the line
            getline(InFile,Str);
            //Put header line into sstram to parse
            istringstream ss(Str);
            //Blank string variable to parse with
            string substr;
            //make the vector longer
            the_data.push_back(vector<double>());
            //Read the column names in
            while (getline(ss,substr,','))
            {
                if (skip == 0)
                {
                    row_names.push_back(substr);
                }
                else
                {
                    if (is_number(substr))
                    {
                        the_data[counterX].push_back(stof(substr));
                    }
                    else
                    {
                        the_data[counterX].push_back(0.0);
                    }
                        
                }
                skip++;
            }
            counterX++;
        }
        else if (is_there_colnames == 1 && is_there_rownames == 0)
        {
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
                    col_names.push_back(substr);
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
                the_data.push_back(vector<double>());
                //Read the column names in
                while (getline(ss,substr,','))
                {
                    if (is_number(substr))
                    {
                        the_data[counterX - 1].push_back(stof(substr));
                    }
                    else
                    {
                        the_data[counterX - 1].push_back(0.0);
                    }    
                }
                counterX++;
            }
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
            the_data.push_back(vector<double>());
            //Read the column names in
            while (getline(ss,substr,','))
            {
                if (is_number(substr))
                {
                    the_data[counterX].push_back(stof(substr));
                }
                else
                {
                    the_data[counterX].push_back(0.0);
                }    
            }
            counterX++;
            cout << the_data.size() << "\n";
        }
    }
    the_data.pop_back();

    for (int i = 0; i < col_names.size(); i++)
    {
        cout << col_names[i] << "\n";
    }

    for (int i = 0; i < row_names.size(); i++)
    {
        cout << "Rownames" << row_names[i] << "\n";
    }

    for (int i = 0; i < the_data.size(); i++)
    {
        for (int j = 0; j < the_data[1].size();j++)
        {
            cout << the_data[i][j] << '\t';
        }
        cout << '\n';
    }
    
    cout << "*****************************" << "\n";

    normalize(the_data);

    for (int i = 0; i < the_data.size(); i++)
    {
        for (int j = 0; j < the_data[1].size();j++)
        {
            cout << the_data[i][j] << '\t';
        }
        cout << '\n';
    }

    vector<vector<double> > dissimilarity_matrix;


}
