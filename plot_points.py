# create plot of convex hull points 
import numpy as np
import matplotlib.pyplot as plt
# from mpl_toolkits.mplot3d import Axes3Q


# open convex_hull.txt
with open("convex_hull.txt", "r") as f:
	# read points into array 
	points = []
	# get first line with x values
	# get second line with y values 
	# append to Q[0] and Q[1] respectively 
	i = 0
	for line in f:
	
		# get line of ints
		if i == 0:
			int_list1 = [int(i) for i in line.split()]
		elif i == 1:
			int_list2 = [int(i) for i in line.split()]
		elif i == 2:
			int_list3 = [int(i) for i in line.split()]
		elif i == 3:
			int_list4 = [int(i) for i in line.split()]
		else:
			quit() 
		i += 1

	# append line to Q
	Q = np.array(int_list1)
	Q = np.vstack([Q, int_list2]) 
	C = np.array(int_list3) 
	C = np.vstack([C, int_list4]) 
	print("\nQ = \n", Q)
	print("\n")
	print("\nC_hull = \n", C)
	print("\n")
	
	# Create figure for Q
	fig2d = plt.figure(1)
	ax2d = fig2d.add_subplot()
	ax2d.set_xlim([0, 150])
	ax2d.set_ylim([0, 150])
	ax2d.set_xlabel('X')
	ax2d.set_ylabel('Y')
	
	# plot points
	ax2d.scatter(Q[0, :], Q[1, :], c='r')

	# display point coordinates
	#for i_x, i_y in zip(Q[0, :], Q[1, :]):
	#	plt.text(i_x, i_y, '({}, {})'.format(i_x, i_y))

	# Create figure for Convex Hull
	chull_fig = plt.figure(2)
	chull_plot = chull_fig.add_subplot()
	chull_plot.set_xlim([0, 150])
	chull_plot.set_ylim([0, 150])
	chull_plot.set_xlabel('X')
	chull_plot.set_ylabel('Y')
	
	# plot points
	chull_plot.scatter(C[0, :], C[1, :], c='r')

	# display point coordinates
	#for i_x, i_y in zip(Q[0, :], Q[1, :]):
	#	plt.text(i_x, i_y, '({}, {})'.format(i_x, i_y))
	
	# display points 
	plt.show() 
