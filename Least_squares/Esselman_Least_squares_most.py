# Import necessary libraries
import csv  # for reading CSV files
import numpy as np  # for numerical operations
import matplotlib.pyplot as plt  # for plotting
from sympy import *
from pprint import pprint

# Write a function that transposes a matrix
def transpose(matrix):
    """
    Transposes a given matrix.

    Parameters:
        matrix (List[List[Any]]): The matrix to be transposed.

    Returns:
        List[List[Any]]: The transposed matrix.

    Example:
        >>> transpose([[1, 2, 3], [4, 5, 6]])
        [[1, 4], [2, 5], [3, 6]]
    """
    return [[matrix[j][i] for j in range(len(matrix))] for i in range(len(matrix[0]))]

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
print("A = ")
pprint(A)
print("b = ")
pprint(b)

# Transpose A using the transpose function
AT = transpose(A)

# Print AT
print("AT = ")
pprint(AT)
