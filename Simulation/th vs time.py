import matplotlib.pyplot as plt
 
# x axis values
x = [1,2,4,8,16]
# corresponding y axis values
y = [1.331, 5.902, 11.627, 19.226, 51.207]
 
# plotting the points
plt.plot(x, y)
 
# naming the x axis
plt.xlabel('No. of Threads')
# naming the y axis
plt.ylabel('Time taken to find the nearest point (in milliseconds)')
 
# giving a title to my graph
plt.title('For 5,000 points')
 
# function to show the plot
plt.show()