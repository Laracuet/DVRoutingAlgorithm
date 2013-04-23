/*********************************************************************/
/*                                                                   */
/* Courtesy Jim Kurose and Keith Ross, from their text               */
/*                                                                   */
/* Computer Networking: A Top-Down Approach Featuring the Internet,  */
/* 3rd edition                                                       */
/*                                                                   */
/*********************************************************************/

#include <stdio.h>
#define NODE 0 

extern struct rtpkt {
  int sourceid;       /* id of sending router sending this pkt */
  int destid;         /* id of router to which pkt being sent 
                         (must be an immediate neighbor) */
  int mincost[4];    /* min cost to node 0 ... 3 */
  };

extern int TRACE;
extern int YES;
extern int NO;

struct distance_table 
{
  int costs[4][4];
} dt0;

struct distance_table table;

/* students to write the following two routines, and maybe some others */

void rtinit0() 
{
    //initialize distance table and necessary structs    
    struct rtpkt send_to_1;
    struct rtpkt send_to_2;
    struct rtpkt send_to_3;
    
    //initialize the distance table to reflect the direct costs to nodes
    table.costs[0][0] = 0;
    table.costs[0][1] = 1;
    table.costs[0][2] = 7;
    table.costs[0][3] = 3;
    
    //set minimum cost paths to all other directly-connected neighbor nodes 
    send_to_1.sourceid = 0;
    send_to_1.destid = 1;
    send_to_1.mincost[0] = 0;
    send_to_1.mincost[1] = 1;
    send_to_1.mincost[2] = 7;
    send_to_1.mincost[3] = 3;
    
    send_to_2.sourceid = 0;
    send_to_2.destid = 2;
    send_to_2.mincost[0] = 0;
    send_to_2.mincost[1] = 1;
    send_to_2.mincost[2] = 7;
    send_to_2.mincost[3] = 3;
    
    send_to_3.sourceid = 0;
    send_to_3.destid = 3;
    send_to_3.mincost[0] = 0;
    send_to_3.mincost[1] = 1;
    send_to_3.mincost[2] = 7;
    send_to_3.mincost[3] = 3;
    
    
    //send using using tolayer2()
    tolayer2(send_to_1);
    tolayer2(send_to_2);
    tolayer2(send_to_3); 
    
    
}


void rtupdate0(rcvdpkt)
  struct rtpkt *rcvdpkt;
{
    int sourceid = rcvdpkt->sourceid;
    int destid = rcvdpkt->destid;
    int mincost[4];
    mincost[0] = rcvdpkt->mincost[0];
    mincost[1] = rcvdpkt->mincost[1];
    mincost[2] = rcvdpkt->mincost[2];
    mincost[3] = rcvdpkt->mincost[3];
    
    int didChange = 0;
    
    //dNODE(source) = minv [c(NODE,v)+dv(source)] over all v such that v is a neighbor of our NODE

    int j;
    int min = 0;
    for (j=0; j<4; j++) {
        
        if (mincost[j] < 999){
            min = table.costs[NODE][sourceid] + mincost[j];
        
            if (min < table.costs[NODE][j]){
                table.costs[NODE][j] = min;
                didChange = 1;
            }
        }
    }
    printf("The packet was sent from router #:%d\n", sourceid);
    
    if (didChange)
        printf("The table did change\n");
    else
        printf("The table did NOT change\n");
    
    printdt0(&table); 
}

printdt0(dtptr)
  struct distance_table *dtptr;
  
{
  printf("                via     \n");
  printf("   D0 |    1     2    3 \n");
  printf("  ----|-----------------\n");
  printf("     1|  %3d   %3d   %3d\n",dtptr->costs[1][1],
	 dtptr->costs[1][2],dtptr->costs[1][3]);
  printf("dest 2|  %3d   %3d   %3d\n",dtptr->costs[2][1],
	 dtptr->costs[2][2],dtptr->costs[2][3]);
  printf("     3|  %3d   %3d   %3d\n",dtptr->costs[3][1],
	 dtptr->costs[3][2],dtptr->costs[3][3]);
}

linkhandler0(linkid, newcost)   
  int linkid, newcost;

/* called when cost from 0 to linkid changes from current value to newcost*/
/* You can leave this routine empty if you're an undergrad. If you want */
/* to use this routine, you'll need to change the value of the LINKCHANGE */
/* constant definition in prog3.c from 0 to 1 */
	
{
}

