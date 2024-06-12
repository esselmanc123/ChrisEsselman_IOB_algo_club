
#include <iostream>
#include <fstream>
#include <string>
#include <cstring> 
#include <vector>
#include <cmath>
#include <cstdlib>
#include <time.h>
#include "/Users/christopheresselman/vscode_header_files/eigen-3.4.0/Eigen/Dense"
#include <sstream>

using namespace std;
using namespace Eigen;

// Codeium auto completion for C++

//Function to read in CSV and put into an Eigen matrix I got from here:
// https://www.youtube.com/watch?v=K9QB1LbemnY

/*
 * Reads data from a CSV file and returns it as an Eigen Matrix.
 *
 * @param fileToOpen The path to the CSV file to be opened.
 *
 * @return A MatrixXd object containing the data from the CSV file.
 *
 * @throws None.
 */
MatrixXd openData(string fileToOpen)
{
	//Vector to map to eigenmatrix
	vector<double> matrixEntries;

	//Store the data
	ifstream matrixDataFile(fileToOpen);

	if (!matrixDataFile.is_open())
	{
		cerr << "File 1 is not open \n" << "Usage: ./Esselman_Least_squares points.csv \n";
		exit(1);
	}

	//store the row
	string matrixRowString;

	//store matrix entry;
	string matrixEntry;

	//Track number of rows
	int matrixRowNumber = 0;

	//Read in all of the lines into a vector
	while(getline(matrixDataFile,matrixRowString))
	{
		stringstream matrixRowStringStream(matrixRowString);

		while (getline(matrixRowStringStream,matrixEntry,','))
		{
			matrixEntries.push_back(stod(matrixEntry));
		}
		matrixRowNumber++;
	}

	// Number of columns is matrixEntris.size()/matrixRowNumber
	return Map<Matrix<double,Dynamic,Dynamic,RowMajor> >(matrixEntries.data(),matrixRowNumber,matrixEntries.size()/matrixRowNumber);
}

int main(int argc, char **argv)
{
    if (argc != 2)
	{
		cout << "Usage: ./Esselman_Least_squares points.csv \n"; 
		return 1;
	}

	//Save the name of the csv as a string
	string csv_file_name = argv[1];

	//Use the function to read in the csv file
    MatrixXd points = openData(csv_file_name);

	//Make column matrix that is the second column of points
	MatrixXd b = points.col(1);

	//Make a 2 column matrix where the first column is all ones and the second column is the first column of points
	MatrixXd A = MatrixXd::Ones(points.rows(),2);
	A.col(1) = points.col(0);

	//Print to the terminal b and A
	cout << "b = \n" << b << "\n";
	cout  << "A = \n" << A << "\n";

	cout << "points = \n"  << points << "\n";

	//Solve the least squares problem
	MatrixXd x = (A.transpose()*A).inverse()*A.transpose()*b;
	cout << "x = \n" << x << "\n";
    return 0;
}