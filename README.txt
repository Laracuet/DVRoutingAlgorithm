/*******************************************************/
/*                                                     */
/*                  	README                         */
/*   												   */
/*													   */
/*  Tyler Laracuente 				4/23/2013		   */
/*													   */	
/*******************************************************/


My implementation of the subroutines rtinit0, rtinit1, rtinit2, rtinit3, and rtupdate0, 
rtupdate1, rtupdate2, rtupdate3 was fairly straightforward. Take node0.c for example:


- rtinit0 -
I initialized the distance table as a 4x4 array of ints, populating all known distances
to node 0 by hand. I then set structs to hold packet data to be sent to each router 
respectively in order to inform them of the vector states. Upon sending the packets,
the function finishes

- rtupdate0 - 
Here, I took the packet data passed as a struct argument and created variables from its
attributes. I then modeled the mathematical formula Dx(y) = minv [c(x,y) + Dv(y)] by 
looping through all possible values for v and comparing their results to the smallest
found thus far, or the min. Whenever a new min was established, I would save it to the 
tables and when the loop ended I would send the changes out to node0's neighbor nodes. 

These functions were both theoretically repeated for each node. 

There are no notes on use, the program will run and produce reports on the states of the 
distance vectors. 