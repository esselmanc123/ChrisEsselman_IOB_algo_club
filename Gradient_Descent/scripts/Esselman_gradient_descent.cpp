/*
    Chris Esselman Gradient Descent for Algorithms Club for IOB

    10/2024

    Will be writing gradient desceent for fitting a linear model to data.


    Notes:

    Loss function- Mean Squared Error
    
    Have the user input 1.)csv of line 2.)max number of iterations 3.)learning rate


    Got some ideas from Geeks for Geeks and here https://towardsdatascience.com/linear-regression-using-gradient-descent-97a6c8700931
    Pseudo code:
    1. Read in csv
    2. Convert csv to matrix
    3. Initialize slope and intercept to 0,0
    4. Find mean squared error for every value in matrix
    5. Calulate partial derivatives of loss function with respect to slope and intercept
        a. D(slope) = -2/n*sum(xi(yi - yi_hat))
        b. D(intercept) = -2/n*sum(yi - yi_hat)
    6. Update slope and intercept
        a. slope = slope - learning_rate*D(slope)
        b. intercept = intercept - learning_rate*D(intercept)
    7. Repeat until loss function is really low or hit number of iterations


*/

#include <iostream>
#include <fstream>
#include <vector> 
#include <sstream>
#include <cmath>

using namespace std;


int main(int argc, char **argv) 
{
    //Make sure the correct number of arguments
	if (argc != 4)  
    {
		cout << "Use as:  " << argv[0] << " <X_Y_Points_CSV max_number_of_iterations learning_rate>\n";
		cout << "Example: " << argv[0] << " points.csv 1000 0.001\n";
		return 0;
	}

	//Make sure the file can be opened
	ifstream InFile(argv[1]);
	if (!InFile.is_open())  
    {
		cout << "Cannot open file \"" << argv[1] << "\"\n";
		return 1;
	}

    //Save max number of iterations
    int max_iterations = stoi(argv[2]);
    //Save learning rate
    double learning_rate = stod(argv[3]);

    //Create vectors to hold X and Y values
    vector<double> X;
    vector<double> Y;

    //Read in X and Y values
    //Read in X and Y values
    string line;
    while (getline(InFile, line))
    {
        stringstream ss(line);
        string X_temp, Y_temp;
        //Get the X value
        getline(ss, X_temp, ',');
        X.push_back(stod(X_temp));
        //Get the Y value
        getline(ss, Y_temp, ',');
        Y.push_back(stod(Y_temp));
    }

    //Close the file
    InFile.close();

    //Initialize slope and intercept to 0,0
    double slope = 0;
    double intercept = 0;

    //Find mean squared error for every value in matrix
    double loss = 0;
    double loss_prev = 1;
    double D_slope = 0;
    double D_intercept = 0;
    long count = 0;
    //Repeat until loss function is really low or hit number of iterations
    while (abs(loss - loss_prev) != 0.0 && count < max_iterations)
    {
        loss_prev = loss;
        loss = 0;
        for (int i = 0; i < X.size(); i++)
        {
            loss += (Y[i] - (slope*X[i] + intercept))*(Y[i] - (slope*X[i] + intercept));
        }
        loss = loss/(2*X.size());
        count++;

        //Calulate partial derivatives of loss function with respect to slope and intercept
        //a. D(slope) = -2/n*sum(xi(yi - yi_hat))
        //b. D(intercept) = -2/n*sum(yi - yi_hat)
        D_slope = 0;
        D_intercept = 0;
        for (int i = 0; i < X.size(); i++)
        {
            D_slope += -2*X[i]*(Y[i] - (slope*X[i] + intercept));
            D_intercept += -2*(Y[i] - (slope*X[i] + intercept));
        }
        D_slope = D_slope/(2*X.size());
        D_intercept = D_intercept/(2*X.size());

        //Update slope and intercept
        //slope = slope - learning_rate*D(slope)
        //intercept = intercept - learning_rate*D(intercept)
        slope = slope - (learning_rate*D_slope);
        intercept = intercept - (learning_rate*D_intercept);
        
    }

    //Finished
    cout << "Finished in " << count << " iterations \n";
    cout << "slope = " << slope << "\n";
    cout << "intercept = " << intercept << "\n";

    return 0;
}