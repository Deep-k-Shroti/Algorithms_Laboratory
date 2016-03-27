
#Algorithms_Lab

##Algorithms_Lab Autumn 2015.

This repository contains all Algorithms Lab Assignments. The assignments are written in C.

##Directories included <br />
/Assignment1 <br />
/Assignment2 <br />
/Assignment3 <br />
/Assignment4 <br />
/Assignment5 <br />
/Assignment6 <br />
/Assignment7 <br />
/Assignment8 <br />
/Assignment9 <br />

Each directory includes the experiment source code(.c) and a Report(.pdf).

##The list of experiments:

1. Polynomial multiplication <br />
__Assignment statement:__ Using the FFT/IFFT technique, you are required to multiply long integers (of say 1024 digits). Develop a suitable data structure for representing such long integers.
Populate such data structures, as required, to obtain such integers with random digits, the number of digits to generate should be taken as a parameter. That way smaller integers may be generated for testing and larger integers may be generated for experimentation.

2. Divide and Conquer <br />
__Assignment statement:__
	* Tiling Problem: Given a n×n board where n is a power of 2 with minimum value as 2, with one missing cell (of size 1×1) at a known location, fill the board using L shaped tiles. An L shaped tile is a 2×2 square with one cell (of size 1×1) missing
	* Write an efficient program which takes as input the co-ordinates of n points and reports back the pair which is closest to each other.

3. Skyline Problem <br />
__Assignment statement:__
Given the exact location and shape information of n buildings which lie on a fixed horizontal line in a 2-dimensional city, design an algorithm that reports the skyline of these buildings, eliminating hidden lines. You need to solve the problem in two cities A and B. Buildings in each city have a fixed characteristic as explained below.
	* City A remains sunny all year round. Each building is rectangular in shape and has a flat roof. A sample input and output is presented in the following figure. A building B_i is represented by a triple (l_i,r_i,h_i) where l_i and r_i represent the leftmost and rightmost x-coordinates of the building and h_i represents the height. The input is a list of triples - one per building. The output is a list of pairs (x-coordinate and height) arranged in ascending order of x-coordinates representing the skyline. <br />
![alt tag](https://cloud.githubusercontent.com/assets/12825395/13701240/92da64d0-e7ac-11e5-96ce-1eef292812e3.png)

	* City B remains cold all year round and suffers from snowfall. Each building now has a slant roof in order to prevent snow from accumulating. A sample input and output is presented in the following figure. A building B_i is represented by a quadruple (l_i,h_l,r_i,h_r) where l_i and r_i represent the leftmost and rightmost x-coordinates of the building and h_l and h_r represents the corresponding heights. The input is now a list of quadruples - one per building. The output is again a list of pairs (x-coordinate and height) arranged in ascending order of x-coordinates representing the skyline. <br />
![alt tag](https://cloud.githubusercontent.com/assets/12825395/13701241/92e15a56-e7ac-11e5-92bd-c9e6e30634e7.png)

4. Josephus problem <br />
We start with n people numbered 1 to n around a circle. We eliminate every second remaining person until only one survives
Task is to compute the position of the survivor as V(n). <br />
	Example, n=10 <br />
	Let 10 people stand in a circle. <br />
	The elimination order is: 2, 4, 6, 8, 10, 3, 7, 1, 9. <br />
	So, we have V(10) = 5. <br />
__Assignment statement:__ Write a program to generate the elimination order according to the given scheme, but preferably without using an array (or linked list), and thereby determine the survivor.
Check both programmatically and analytically whether the survivor position can be obtained as: V(2^m + l) = 2l + 1, for m ≥ 0 and 0 ≤ l < 2m.

5. Binary Tree <br />
__Assignment statement:__
	* Generate a binary tree of 100 nodes containing distinct integer (both +ve and -ve) keys at random.
	* Be careful that the tree does not become degenerate. To generate a binary tree of n nodes, first create a root node and then you could recursively generate a left sub-tree of m=[pn] nodes, where p is a random number between 0.4 and 0.6 and then the right sub-tree should be recursively created to have n-m-1 nodes. Note that p should be randomly generated for each sub-tree.
	* Given a binary tree, carry out an in-order traversal of the tree and output the keys separated by a blank and terminated by double LF.
	* Given a binary tree, carry out an pre-order traversal of the tree and output the keys separated by a blank and terminated by double LF.
	* Given a binary tree, carry out an post-order traversal of the tree and output the keys separated by a blank and terminated by double LF.
	* Given a binary tree storing integer keys, find the path from the root to a leaf node that has the maximum sum, output the keys separated by a blank and terminated by double LF.
	* Given a binary tree storing integer keys, find the path (between any pair of nodes) in it that has the maximum sum, output the keys separated by a blank and terminated by double LF.
The above should be coded as separate functions and called from the main() function The tree generated in the first step should be used for the subsequent steps.


6. Interval Tree <br />
We consider an Interval Tree as a binary tree where, <br />
Each node is labelled with an integer interval range [a,b] where a ≤ b. <br />
For a node a labelled with [la,ua] in the tree, any node b occurring in the left sub-tree of a with label [lb,ub] shall imply that ub ≤ la. <br />
For a node a labelled with [la,ua] in the tree, any node b occurring in the right sub-tree of a with label [lb,ub] shall imply that ua ≤ lb. < br />
Consider the example interval tree given here with the special property that all intervals are mutually exclusive and exhaustive for the entire range [0,30].
a node a labeled with [la,ua] points to a linked list containing elements i,j,...,k in sorted order (where la ≤ i,j,...,k ≤ ua).
Let us call this special structure as disjoint interval list. <br />
__Assignment Statement:__
	1. Write a function CREATE_INTERVAL_TREE(l,u,n) which creates n number of mutually exclusive and exhaustive equal sized intervals within the interval range [l,u].Surely, it is not always possible to maintain such equal sized intervals when we are dealing with integers. In such cases, let the boundary intervals be (a bit) smaller or larger w.r.t. other intervals that are of equal size. Generate a disjoint interval list given this upper and lower bounds and number of intervals. To make the interval tree height balanced, first create a root by finding out the median of the lower bounds of the intervals and select the corresponding interval as root node. Recursively generate a left sub-tree from the intervals lesser than the root interval and a right sub-tree from list of intervals greater than the root interval.
	2. Write a function INSERT(Tree, i), which inserts an integer ii to the disjoint interval list Tree. This means, after insertion, we have a valid disjoint interval list.
	3. Write a function MERGE(T, l, u) that takes as input a disjoint interval list TT and two integers l ≤ u. The function will do the following create a node NN with label [l,u]. Identify the unique sub-tree T' in T with intervals inside or overlapping with [l,u]. traverse T′, create a linked list pointed to by N and populate it with elements from T′. Modify pointers to de-link T′ from T and add N.
	4. Write a function PRETTY_PRINT(Tree), which given an interval tree, carries out an in-order traversal of the tree and outputs the data values contained in the linked lists of each node in the format where the nodal lists are printed at every line and the node at level h has h horizontal tabs before it.
	5. Write a main() which does the following using the helper functions as discussed above.
		* Ask user to provide l,u,n and call CREATE_INTERVAL_TREE(l,u,n).
		* Ask user to provide integer ii, generate ii random integers inside [l,u] and insert them to the created disjoint interval list.
		* Ask user to provide integer m < n. Write a suitable routine which modifies the existing disjoint interval list to another disjoint interval list which should have m number of mutually exclusive and exhaustive equal sized intervals within the interval range [l,u]. This job should be entirely performed by suitable calls to MERGE.
		* Print the data structure using PRETTY_PRINT after each step.

7. Red Black Tree <br />
In a multi-tasking operating system, a scheduler is a piece of code that decides which process/task shall be given access to the CPU and for how much time. The scheduler maintains a set of pending processes stored in some data structure S. Every-time the scheduler wakes up, it finds the process with least pending execution and gives it the CPU (this is just one example of a simple scheduling policy). Red Black tree is the structure of choice in implementing scheduler for the linux kernel (2.6.23). <br />
__Assignment statements__
Implement suitable routines for Insertion, Search and Deletion in RB trees. Write a scheduler and process creator which works as follows.
	1. In every iteration of an outer loop L, if the total number of live processes is less than some N, the process creator creates a process with execution time between [1,1000] and priority between [1,4].
	2. Live processes are stored in a Red Black tree keyed by their pending execution time.
	3. In every iteration of an outer loop L, the scheduler
		* checks if there is any newly created process and inserts it to the tree,
		* searches the process with least pending execution time and gives it to the CPU, a process with priority ii executes for i×50 seconds once scheduled.
		* Once the process finishes its quota of execution, the scheduler inserts it back to the tree if the process has not completed its entire execution.
	4. For insertion of elements in the RB tree whose key value is same as the key of some existing element, put both elements at the same node in a list structure.

 Main function :
 Write a main function from which the value of N can be set and the system can be simulated for execution and completion      of M number of processes. The value of M is also set in main(). The output is expected to be a text file containing a table with column headings: <br />
	* process number,
	* creation time,
	* priority,
	* time stamps when a process got scheduled,
	* time stamps when a process got preempted from CPU,
	* time stamp when a process completed execution.
8. Simulation Using Heaps <br />
__Assignment Statement__
You are required to write a program to simulate the collision of some balls on a 2D planar region bounded by straight walls. The simulation is to be done efficiently using the application of the priority queue data structure, which is the objective of this experiment. <br />
Input and Output Specification <br />
	* Initialize your simulation with a pre-defined area (length and breadth specification), a set of five particles with initial velocities (as per your convenience) and radius.
	* The user may provide a time horizon (100 sec say).Your output should be a plot exhibiting the trajectories of the five particles (in different colors) up to 100 sec.
	* In a seperate text file, you should log the velocity and position vectors of each particle at the moment of each collision.
9. Fibonacci Heaps <br />
Some common Fibonacci Heap functions have been implemented
	* Implemented makeHeap()
	* Implemented insertHeap(H, x)
	* Implemented extractMinHeap(H)
	* Implemented unionHeap(H1, H2)
	* Implemented decreaseKeyHeap(H, x, k)
	* Reported of amortised costs in the report

Reference: Introduction to Algorithms book by Thomas H. Cormen, Charles E. Leiserson, Ronald L. Rivest, and Clifford Stein


###Known Bugs
* In Assignment 6 Interval Tree, the function MERGE(T,l,u) is not implemented correctly.
##Setup

1. For C codes
	* Download the directory
	* Open the terminal.
	* Go to the directory containing the C code .
	* Run C code
