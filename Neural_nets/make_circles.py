# Write a script where the user inputs the number of points and the noise level
# and then generates a dataset of points in the shape of a circle

import numpy as np
import matplotlib.pyplot as plt

# Define the number of points and the noise level
n_points = 5
noise_level = 0.1

# Generate the dataset
x = np.random.uniform(-1, 1, n_points)
y = np.random.uniform(-1, 1, n_points)
x += np.random.normal(0, noise_level, n_points)
y += np.random.normal(0, noise_level, n_points)

# Plot the dataset
plt.scatter(x, y)
plt.show()

  




