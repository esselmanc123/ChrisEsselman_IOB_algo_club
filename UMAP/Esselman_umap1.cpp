/*
    Chris Esselman First part of UMAP.

    2.3.2024

    Will be writing the first part of UMAP in C++. Much of the pseudo code
    is from the youtube videos on UMAP:



*/

#include <iostream>
#include <fstream>
#include <vector> 
#include <sstream>
#include <cmath>
#include <cstring>
#include <string>

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

//Function to tell if vector has all negative elements
bool all_negative(vector<double> difference)
{
    for (int i = 0; i < difference.size(); i++)
    {
        if (difference[i] > 0)
        {
            return false;
        }
    }
    return true;
}

//Normalizing the data
//Mean center and scale
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

// Distance for categorical or binary data
void jaccard_distance(vector<vector<double> > data, vector<vector<double> >& blank_matrix)
{
    for (int z = 0; z < data.size(); z++)
    {
        blank_matrix.push_back(vector<double>());
        for (int i = 0; i < data.size(); i++)
        {
            double similarity = 0.0;
            double number_in_both = 0;
            for (int j = 0; j < data[0].size(); j++)
            {
                if (data[z][j] == data[i][j])
                {
                    number_in_both++;
                }
            }
            similarity = number_in_both/data[0].size();
            blank_matrix[z].push_back(1-similarity);
        }
    }
}

// Distance for numerical data
void euclidean_distance(vector<vector<double> > data, vector<vector<double> >& blank_matrix)
{
    for (int z = 0; z < data.size(); z++)
    {
        blank_matrix.push_back(vector<double>());
        for (int i = 0; i < data.size(); i++)
        {
            double sum = 0.0;
            for (int j = 0; j < data[0].size(); j++)
            {
                sum += (data[z][j] - data[i][j]) * (data[z][j] - data[i][j]);
            }
            blank_matrix[z].push_back(sqrt(sum));
        }
    }
}



int main(int argc, char **argv) 
{
    //Make sure the correct number of arguments
	if (argc != 6)  
    {
		cout << "Use as:  " << argv[0] << " <Comma-delimited_text_file num_neighbors col_names? rownames? numerical_or_categorical?>\n";
		cout << "Example: " << argv[0] << " Table.txt 3 0 1 num\n" << "or\n" << argv[0] << " Table.txt 3 false true cat\n";
		return 0;
	}

	//Make sure the file can be opened
	ifstream InFile(argv[1]);
	if (!InFile.is_open())  
    {
		cout << "Cannot open file \"" << argv[1] << "\"\n";
		return 1;
	}

    string num_neighbors_string = argv[2];
    //Variable to hold number of neighbors
    if (!is_number(num_neighbors_string))
    {
        cout << "Please enter a number for the number of neighbors\n";
        return 2;
    }

    //Integer to hold number of neighbors
    int num_neighbors = stoi(num_neighbors_string);

    //Read in the headers and the row names
    string col_names_string = argv[3];
    transform(col_names_string.begin(), col_names_string.end(), col_names_string.begin(), ::toupper);
    if (col_names_string != "TRUE" || col_names_string != "FALSE")
    {
        if (!is_number(col_names_string) || stoi(col_names_string) != 1 || stoi(col_names_string) != 0)
        {
            cout << "Please enter true or false or 1 or 0 for col_names\n";
            return 3;
        }
    }
    // set is_there_colnames
    int is_there_colnames;
    if (col_names_string == "TRUE")
    {
        is_there_colnames = 1;
    }
    else if (col_names_string == "FALSE")
    {
        is_there_colnames = 0;
    }
    else
    {
        is_there_colnames = stoi(col_names_string);
    }

    //Read in true or false to see if the data has rownames
    string row_names_string = argv[4];
    transform(row_names_string.begin(), row_names_string.end(), row_names_string.begin(), ::toupper);
    if (row_names_string != "TRUE" || row_names_string != "FALSE")
    {
        if (!is_number(row_names_string) || stoi(row_names_string) != 1 || stoi(row_names_string) != 0)
        {
            cout << "Please enter true or false or 1 or 0 for row_names\n";
            return 4;
        }
    }
    // set is_there_rownames
    int is_there_rownames;
    if (row_names_string == "TRUE")
    {
        is_there_rownames = 1;
    }
    else if (row_names_string == "FALSE")
    {
        is_there_rownames = 0;
    }
    else
    {
        is_there_rownames = stoi(row_names_string);
    }

    string numerical_or_categorical_string =  argv[5];
    transform(numerical_or_categorical_string.begin(), numerical_or_categorical_string.end(), numerical_or_categorical_string.begin(), ::toupper);
    if (numerical_or_categorical_string != "NUM" || numerical_or_categorical_string != "CAT")
    {
        cout << "Please enter num or cat for numerical_or_categorical\n";
        return 5;
    }
    // set numerical_or_categorical
    int numerical_or_categorical;
    if (numerical_or_categorical_string == "NUM")
    {
        numerical_or_categorical = 1;
    }
    else
    {
        numerical_or_categorical = 0;
    }
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

    normalize(the_data);

    vector<vector<double> > dissimilarity_matrix;

    if (numerical_or_categorical == 1)
    {
        euclidean_distance(the_data,dissimilarity_matrix);
    }
    else
    {
        jaccard_distance(the_data,dissimilarity_matrix);
    }
    
}