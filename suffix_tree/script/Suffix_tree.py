import numpy as np

# Using the command line read in a fasta file and put into a numpy array

# Read in the file ignoring the first line

with open('test.txt', 'r') as f:
    lines = f.readlines()

# Make an empty list
holder = []
# Put the lines into the numpy array ignoring the first line
for i in range(1, len(lines)):
    for j in range(len(lines[i])):
        # Remove the newline character
        if lines[i][j] != "\n":
            holder.append(lines[i][j])

holder.append('$')
# Convert the list into a numpy array
seq = np.array(holder)
# Print the numpy array
print(seq)


# Create a node class
class Node:
    def __init__(self, value):
        self.value = value
        self.children = []
        self.edges = []

    def add_child(self, child):
        self.children.append(child)

    def add_edge(self, edge):
        self.edges.append(edge)

    def get_children(self):
        return self.children

    def get_value(self):
        return self.value
    
    def get_edges(self):
        return self.edges

# Create an empty linked list
tree = []
# Big loop for going through each substring    
for i in range(len(seq)):
    # Create current substring
    substring = seq[i:]
    # If the tree is empty create simplest tree
    if len(tree) == 0:
        # Create root node
        tree.append(Node(''))
        # Add first child
        tree.append(Node(0))
        # Add edge
        tree[0].add_child(1)
        # Add edge label
        tree[0].add_edge([0,len(substring)])
    else:
        for j in range(len(tree)):
            


    


