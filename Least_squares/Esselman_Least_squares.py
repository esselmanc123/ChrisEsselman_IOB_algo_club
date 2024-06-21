# Import necessary libraries
import csv  # for reading CSV files
import numpy as np  # for numerical operations
import matplotlib.pyplot as plt  # for plotting

# Prompt the user for the CSV file name
filename = input("Enter CSV file name: ")

# Open the CSV file and read its contents
with open(filename, 'r') as csvfile:
    # Create a CSV reader object
    reader = csv.reader(csvfile)
    # Read the contents of the CSV file into a list of lists (data)
    data = list(reader)

# Make a matrix where the first column is all ones and the second column is the first column of data
A = np.column_stack((np.ones(len(data)), np.array(data)[:, 0]))

# Make a one column matrix from the second column of data
b = np.array(data)[:, 1]

# Make the values of A and b floats
A = A.astype(float)
b = b.astype(float)

# Print A and b
print("A = ", A)
print("b = ", b)

# Solve the least squares problem
x = np.linalg.lstsq(A, b, rcond=None)[0]

# Print the solution
print("x = ", x)
    
