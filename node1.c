/*********************************************************************/
/*                                                                   */
/* Courtesy Jim Kurose and Keith Ross, from their text               */
/*                                                                   */
/* Computer Networking: A Top-Down Approach Featuring the Internet,  */
/* 3rd edition                                                       */
/*                                                                   */
/*********************************************************************/

#include <stdio.h>
#define NODE 1

extern struct rtpkt {
  int sourceid;       /* id of sending router sending this pkt */
  int destid;         /* id of router to which pkt being sent 
                         (must be an immediate neighbor) */
  int mincost[4];    /* min cost to node 0 ... 3 */
  };


extern int TRACE;
extern int YES;
extern int NO;

int connectcosts1[4] = { 1,  0,  1, 999 };

struct distance_table 
{
  int costs[4][4];
} dt1;

//create distance table, necessary structs, and the clock
struct distance_table table;
struct rtpkt send_to_0;
struct rtpkt send_to_2;
struct rtpkt send_to_3;
float clocktime;


/* students to write the following two routines, and maybe some others */


rtinit1() 
{
    //timestamp
    printf("rtinit1 called at: %d\n", clocktime);
    
    //initialize the distance table to reflect the direct costs to nodes
    table.costs[NODE][0] = 1;
    table.costs[NODE][1] = 0;
    table.costs[NODE][2] = 1;
    table.costs[NODE][3] = 999;
    
    //set minimum cost paths to all other directly-connected neighbor nodes
    send_to_0.sourceid = NODE;
    send_to_0.destid = 0;
    send_to_0.mincost[0] = 1;
    send_to_0.mincost[1] = 0;
    send_to_0.mincost[2] = 1;
    send_to_0.mincost[3] = 999;
    
    send_to_2.sourceid = NODE;
    send_to_2.destid = 2;
    send_to_2.mincost[0] = 1;
    send_to_2.mincost[1] = 0;
    send_to_2.mincost[2] = 1;
    send_to_2.mincost[3] = 999;
    
    send_to_3.sourceid = NODE;
    send_to_3.destid = 3;
    send_to_3.mincost[0] = 1;
    send_to_3.mincost[1] = 0;
    send_to_3.mincost[2] = 1;
    send_to_3.mincost[3] = 999;
    
    //send using using tolayer2()
    tolayer2(send_to_0);
    tolayer2(send_to_2);
    //tolayer2(send_to_3);

}


rtupdate1(rcvdpkt)
  struct rtpkt *rcvdpkt;
  
{
    //timestamp
    printf("rtupdate1 called at: %d\n", clocktime);
    
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
        
        if (mincost[j] != NULL && table.costs[NODE][sourceid]!=NULL){
            min = table.costs[NODE][sourceid] + mincost[j];
            
            if (min < table.costs[NODE][j]){
                table.costs[NODE][j] = min;
                didChange = 1;
            }
        }
    }
    
    if (didChange){
        
        send_to_0.sourceid = NODE;
        send_to_0.destid = 0;
        send_to_0.mincost[0] = table.costs[NODE][0];
        send_to_0.mincost[1] = table.costs[NODE][1];
        send_to_0.mincost[2] = table.costs[NODE][2];
        send_to_0.mincost[3] = table.costs[NODE][3];
        
        send_to_2.sourceid = NODE;
        send_to_2.destid = 2;
        send_to_2.mincost[0] = table.costs[NODE][0];
        send_to_2.mincost[1] = table.costs[NODE][1];
        send_to_2.mincost[2] = table.costs[NODE][2];
        send_to_2.mincost[3] = table.costs[NODE][3];
        
        send_to_3.sourceid = NODE;
        send_to_3.destid = 3;
        send_to_3.mincost[0] = table.costs[NODE][0];
        send_to_3.mincost[1] = table.costs[NODE][1];
        send_to_3.mincost[2] = table.costs[NODE][2];
        send_to_3.mincost[3] = table.costs[NODE][3];
        
        tolayer2(send_to_0);
        tolayer2(send_to_2);
        //tolayer2(send_to_3);
    }
    
    
    
    
    //Desired Output
    printf("The packet was sent from router #:%d\n", sourceid);
    
    if (didChange)
        printf("The table did change\n");
    else
        printf("The table did NOT change\n");
    
    printdt1(&table);
    didChange = 0; 

}


printdt1(dtptr)
  struct distance_table *dtptr;
  
{
  printf("             via   \n");
  printf("   D1 |    0     2 \n");
  printf("  ----|-----------\n");
  printf("     0|  %3d   %3d\n",dtptr->costs[0][0], dtptr->costs[0][2]);
  printf("dest 2|  %3d   %3d\n",dtptr->costs[2][0], dtptr->costs[2][2]);
  printf("     3|  %3d   %3d\n",dtptr->costs[3][0], dtptr->costs[3][2]);

}



linkhandler1(linkid, newcost)
int linkid, newcost;   
/* called when cost from 1 to linkid changes from current value to newcost*/
/* You can leave this routine empty if you're an undergrad. If you want */
/* to use this routine, you'll need to change the value of the LINKCHANGE */
/* constant definition in prog3.c from 0 to 1 */
	
{
    //timestamp
    printf("rtlinkhandler1 called at: %d\n", clocktime);
    
    //update distance table
    table.costs[NODE][linkid] = newcost;
    
    //send update routing packets to neighbor nodes
    send_to_0.sourceid = NODE;
    send_to_0.destid = 1;
    send_to_0.mincost[linkid] = newcost;
    
    send_to_2.sourceid = NODE;
    send_to_2.destid = 2;
    send_to_2.mincost[linkid] = newcost;
    
    tolayer2(send_to_2);
    tolayer2(send_to_3);
}


