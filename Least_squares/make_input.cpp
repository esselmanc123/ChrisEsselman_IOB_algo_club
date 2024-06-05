
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cmath>
#include <cstdlib>
using namespace std;
using namespace Eigen;
/*
    Make input file for least squares regression. Input the the number of data points (n) to make n x 2 dimension matrix.
    Randomly assign values to that matrix between 0 and 10 and out put it as a csv file.

    Writing this to also learn how to use the eigen library

*/
// define the format you want, you only need one instance of this...
const static IOFormat CSVFormat(StreamPrecision, DontAlignCols, ",", "\n");
void writeToCSVfile(string name, MatrixXd matrix)
{
    ofstream file(name.c_str());
    file << matrix.format(CSVFormat);
 }

void writeToCSVfile2(string name, Matrix2f matrix)
{
    ofstream file(name.c_str());
    file << matrix.format(CSVFormat);
 }

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

    if (argc != 2)
	{
		cout << "Usage: ./make_input number_of_points \n"; 
		return 1;
	}

    int number_of_rows;
    string number_of_rows_string = argv[1];
    if (!is_number(number_of_rows_string))
    {
        cout << "Second argument is not a number! \n";
        cout << "Usage: ./make_input number_of_points \n";
    }
    else
    {
        number_of_rows = stoi(number_of_rows_string);
    }

    MatrixXd matrixA;

    matrixA.resize(number_of_rows,2);
    
    //matrixA.setZero();
    matrixA.setRandom();
    writeToCSVfile("16_points.csv",matrixA);

    Matrix2f test;

    test << 1,2,
            0,0;

    writeToCSVfile2("line.csv",test);
    return 0;
    

}

