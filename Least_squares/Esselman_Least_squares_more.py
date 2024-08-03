# Import necessary libraries
import csv  # for reading CSV files
import numpy as np  # for numerical operations
import matplotlib.pyplot as plt  # for plotting
from sympy import *
from pprint import pprint


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

# Multiply A transpose by A and save in new variable
AtA = np.dot(A.transpose(), A)

# Multiply A transpose by b and save in new variable
Atb = np.dot(A.transpose(), b)

# Print the values of AtA and Atb
print("AtA = ")
pprint(AtA)
print("Atb = ")
pprint(Atb)

# Make augmented matrix and save in new variable
Aug = np.column_stack((AtA, Atb))

# Print the augmented matrix
print("Aug = ")
pprint(Aug)

# Save Aug_rreduced for later use
Aug_rreduced_matrix = Matrix(Aug).rref()
#Save as numpy array

Aug_rreduced = Aug_rreduced_matrix[0]

# Print Aug_rreduced so it looks nice
print("Aug_rreduced = ")
pprint(Aug_rreduced)

# Save the last column of Aug_rreduced in x
x = Aug_rreduced[:, -1]
print("x = ")
pprint(x)

# Change x to ints and pretty print
x = x.as_np().astype(int)
pprint(x)