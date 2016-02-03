//Yiru Sun
#include <iostream>
#include <cstring>
#include <fstream>
#include <cstdlib>
#include <stdio.h>
#include <stdlib.h>
#include <algorithm>
#include "stats.h"
#include "statrunner.h"

using namespace std;


Stats::Stats()
{


	for (int i = 0; i < 30; ++i)
	{
		t[i].tname[0] = '\0';
	//	t[i].tcheck = 0;
		for (int j = 0; j < 40; ++j)
		{
			t[i].tplayers[j].atbats = t[i].tplayers[j].hits = t[i].tplayers[j].ave = 0;

			t[i].tplayers[j].pname[0] = t[i].tplayers[j].tn[0] = '\0';
			
		}
	}
}  // Stats()



 void Stats::update(const char name[25], const char team[4], int hit, 
   int operationNum)
 {
	for (int i = 0; i < 30; ++i)    //update team
 	{
 		if(strcmp(t[i].tname, team)==0)
 		{
 			t[i].tupdate(name, team, hit);
 			break;
 		}else if(t[i].tname[0]=='\0')
 		{
 			//t[i].tcheck++;
 			memcpy(t[i].tname,team, 4);
 			t[i].tupdate(name, team, hit);
 			break;
 		}
 	}
 }  // update()
 
static int cmpfunc (const void * a, const void * b) {
   const Players* _a = reinterpret_cast<const Players*>(a);
   const Players* _b = reinterpret_cast<const Players*>(b);
   return _a->ave > _b->ave ? -1 : _a->ave < _b->ave ? 1 : 0;
}

 
 void Stats::query(const char team[4], Player top10[10], int operationNum)
 {
  	if(strncmp("MLB", team, 3)==0)
   	{
   		int a = 0;

		for (int i = 0; i < 30; ++i)
   		{
				if (i!=0) a=10;
   				for (int k = 0; k < 40; ++k)
   				{

//   					p1[k+a].atbats=t[i].tplayers[k].atbats;
//   					p1[k+a].hits=t[i].tplayers[k].hits;
   					p1[k+a].ave=t[i].tplayers[k].ave;
   					memcpy(p1[k+a].tn,t[i].tplayers[k].tn,4);
   					memcpy(p1[k+a].pname,t[i].tplayers[k].pname,25);
   				}

   				qsort(p1, 50, sizeof(p1[0]), cmpfunc);

   		}

   		for (int i = 0; i < 10; ++i)
   		{
   				memcpy(top10[i].name, p1[i].pname, 25);
   				memcpy(top10[i].team, p1[i].tn, 4);
   		}
   	}else
   	{
   		for (int i = 0; i < 30; ++i)
   		{
   			if(strcmp(t[i].tname, team)==0)
   			{
 //  				cout<<t[i].tname<<"  "<<team<<endl;
   				for (int k = 0; k < 40; ++k)
   				{
//   					p2[k].atbats=t[i].tplayers[k].atbats;
//   					p2[k].hits=t[i].tplayers[k].hits;
   					p2[k].ave=t[i].tplayers[k].ave;
   					memcpy(p2[k].tn,t[i].tplayers[k].tn,4);
   					memcpy(p2[k].pname,t[i].tplayers[k].pname,25);
   				}

   				qsort(p2, 40, sizeof(p2[0]), cmpfunc);

   				for (int j = 0; j < 10; ++j)
   				{
   					memcpy(top10[j].name, p2[j].pname, 25);
   					memcpy(top10[j].team, p2[j].tn, 4);
   				}
   			break;	
   			}
   		}
   	}
//cout<<"run"<<endl;
 }  // query ()
 
 
 
 

