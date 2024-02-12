
/*
    Chris Esselman Hierarchical Clustering for Algorithms Club for IOB

    2.3.2024

    Going to be writing the divisive hierarchical algorithm that I found from the book:
    Finding Groups in Data: An Introduction to Cluster Analysis (Kaufman 1990)

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

//Diana algorithm
void diana(vector<vector<double> > dissimmat, vector<int> &clusters, int level)
{
    /*
    First find which cluster we need to split at this round. Will do this 
    by finding the cluster that has the largest distance between any two points. 
    Already have dissim mat, so need to find indicies of that point.
    */
   double highest_dissimilarity = 0.0;
   int index_group;
   for (int i = 0; i < clusters.size(); i++)
   {
        for (int j = 0; j < clusters.size(); j++)
        {
            if ((dissimmat[i][j] > highest_dissimilarity) && (clusters[i] == clusters[j]))
            {
                highest_dissimilarity = dissimmat[i][j];
                index_group = i;
            }
        }
   }
    //Find the size of the cluster to split and the location of the indices
    vector<int> clust_indices;
    for (int i = 0; i < clusters.size(); i++)
    {
        if (clusters[i] == clusters[index_group])
        {
            clust_indices.push_back(i);
        }
    }
    /*
        Next will need to do the splitting of the largest cluster
        Find point with highest average dissimilarity of each data point to every other data point in the cluster.
        Will be using the variables highest_dissimilarity and index group to keep a track of this
    */
    // Initialize differences vector
    vector<double> differences;
    for (int i = 0; i < clust_indices.size() - 1; i++)
    {
        differences.push_back(1.0);
    }

    // Initialize splinter indices
    vector<int> splinter_indices;

    //While loop that does the splitting
    while (all_negative(differences) == false)
    {
        index_group = 0;
        highest_dissimilarity = 0.0;
        //This finds the initial splinter group
        if (splinter_indices.size() == 0)
        {
            for (int i = 0; i < clust_indices.size(); i++)
            {
                double sum_dist = 0.0;
                for (int j = 0; j < clust_indices.size(); j++)
                {
                    sum_dist += dissimmat[clust_indices[i]][clust_indices[j]];
                }
                if ((sum_dist/clust_indices.size() >= highest_dissimilarity))
                {
                    highest_dissimilarity = sum_dist/clust_indices.size();
                    index_group = i;
                }
            }
            //Add index to splinter group
            splinter_indices.push_back(clust_indices[index_group]);
            //Remove index to clust group
            clust_indices.erase (clust_indices.begin()+index_group);
        }
        //Find who else should join the splinter group
        else
        {
            for (int i = 0; i < clust_indices.size(); i++)
            {
                double sum_dist_clust = 0.0;
                double sum_dist_splint = 0.0;
                for (int j = 0; j < clust_indices.size(); j++)
                {
                    sum_dist_clust += dissimmat[clust_indices[i]][clust_indices[j]];
                }
                for (int j = 0; j < splinter_indices.size(); j++)
                {
                    sum_dist_splint += dissimmat[clust_indices[i]][splinter_indices[j]];
                }
                differences[i] = (sum_dist_clust/clust_indices.size()) - (sum_dist_splint/splinter_indices.size());
                if (differences[i] >= highest_dissimilarity)
                {
                    highest_dissimilarity = differences[i];
                    index_group = i;
                }
            }
            if (differences[index_group] >= 0)
            {
                splinter_indices.push_back(clust_indices[index_group]);
                clust_indices.erase (clust_indices.begin()+index_group);
                differences.erase (differences.begin()+index_group);
            }
        }
    }
    for (int i = 0; i < splinter_indices.size(); i++)
    {
        clusters[splinter_indices[i]] = level;
    }
}

int main(int argc, char **argv) 
{
    //Make sure the correct number of arguments
	if (argc != 5)  
    {
		cout << "Use as:  " << argv[0] << " <Comma-delimited_text_file col_names? rownames? numerical_or_categorical?>\n";
		cout << "Example: " << argv[0] << " Table.txt 0 1 1\n";
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

    int numerical_or_categorical = stoi(argv[4]);
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
    vector<int> clusts;
    for (int i = 0; i < the_data.size(); i++)
    {
        clusts.push_back(0);
    }

    if (is_there_rownames == true)
    {
        for (int q = 1; q < row_names.size() + 1; q++)
        {
            diana(dissimilarity_matrix,clusts,q);
            for (int i = 0; i < row_names.size(); i++)
            {
                cout << row_names[i] << "\t" << clusts[i] << "\n";
            }
            cout << "************************" << "\n";
            cout << "************************" << "\n";
        }
    }
    else
    {
        for (int q = 1; q < the_data.size() + 1; q++)
        {
            diana(dissimilarity_matrix,clusts,q);
            for (int i = 0; i < the_data.size(); i++)
            {
                cout << i+1 << "\t" << clusts[i] << "\n";
            }
            cout << "************************" << "\n";
            cout << "************************" << "\n";

        }
    }
}

    
