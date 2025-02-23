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

def find_edge_to_take(tree, substring, index_substring, layer):
    for j in range(len(tree[layer])):
        # Find edge that matches first letter of substring
        for k in range(len(tree[i][j].get_edges())):
            if tree[i][j].get_edges()[k][0] == substring[index_substring]:
                # Return node and edge indices for the layer
                return [j,k]
def follow_edge(tree,substring,index_substring,layer,node,edge):
    # Check to see if the substring falls off in the edge
    for j in range(len(tree[layer][node].get_edges()[edge])):
        if tree[layer][node].get_edges()[edge][j] != substring[index_substring]:
            # Return True if it falls off
            return [True,index_substring]
        index_substring += 1
    # Return False if it does not fall off
    return [False,index_substring]
   
# Make function that returns index of substring to make new node, path on tree to make new node, if off edge or not
def find_path(tree, substring):
    # Index on substring where node needs to be made
    index_substring = 0
    # Path on tree to make new node
    path = []
    # Bool to check if fell off edge
    off_edge = False
    # For every layer, first find the edge that matches the first letter of the substring
    # Then check the rest of the edge to see if it falls off in the edge
    # If it do not fall off then check the next layer to find the edge that matches the next letter in the substring
    # If fall off on edge will need to make internal node and leaf node
    # If fall off at start or end of edge just need to make leaf node
    for i in range(len(tree)):
        # Find node and edge that matches first letter of substring
        path.append(find_edge_to_take(tree,substring,index_substring,i))
        # Check to see if it falls off in the edge
        off_edge = follow_edge(tree,substring,index_substring,i,path[i][0],path[i][1])
        # If it does not fall off then check the next layer
        if off_edge[0] == False:
            index_substring = off_edge[1]
        else:
            # Return path
            return path

# Create an empty linked list
tree = []
# Big loop for going through each substring    
for i in range(len(seq)):
    # Create current substring
    substring = seq[i:]
    # If the tree is empty create simplest tree
    if len(tree) == 0:
        # Create root node
        sublist = []
        sublist.append(Node(None))
        # Child will be first index of second layer
        sublist[0].add_child(0)
        # Edge correspons to index in the children list
        sublist[0].add_edge([0,len(substring)])
        # Add root node
        tree.append(sublist)
        # Add first child
        sublist = []
        # Value will be the index of the substring
        sublist.append(Node(0))
        # Add the child into second layer
        tree.append(sublist)
    else:
        
                

        
        

       