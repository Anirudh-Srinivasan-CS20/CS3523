import matplotlib.pyplot as plt
 
# x axis values
x = [1000,2000,3000,4000,5000]
# corresponding y axis values
y = [5.457, 15.357, 29.273, 47.024, 52.316]
 
# plotting the points
plt.plot(x, y)
 
# naming the x axis
plt.xlabel('No. of Points')
# naming the y axis
plt.ylabel('Time taken to find the nearest point (in milliseconds)')
 
# giving a title to my graph
plt.title('For 16 Threads')
 
# function to show the plot
plt.show()