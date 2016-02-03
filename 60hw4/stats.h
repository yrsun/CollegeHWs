// Authors: Yiru Sun

#ifndef STATS_H
#define	STATS_H

#include <iostream>
#include <cstring>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <algorithm>
#include <cstdlib>
#include "statrunner.h"

using namespace std;

class Players {
public:
	int atbats;
	int hits;
	double ave;
	char tn[4];
	char pname[25];
	bool operator< (const Players& other) const { return ave < other.ave; }
};

class Team {
public:
	Players tplayers[40];
//	int tcheck;
	char tname[25];

	void tupdate(const char name[25], const char team[4], int hit)
	{
		for (int i = 0; i < 40; ++i)
		{
			if(strcmp(tplayers[i].pname, name)==0)
			{
				memcpy(tplayers[i].tn,team, 4);
				tplayers[i].atbats++;
 				tplayers[i].hits+=hit;
 				tplayers[i].ave=( (double) tplayers[i].hits ) / tplayers[i].atbats;
 				break;
			}else if(tplayers[i].pname[0]=='\0')
			{
				memcpy(tplayers[i].pname,name, 25);
				memcpy(tplayers[i].tn,team, 4);
				tplayers[i].atbats++;
 				tplayers[i].hits+=hit;
 				tplayers[i].ave=( (double) tplayers[i].hits ) / tplayers[i].atbats;
 				break;
			}
		}
	}

};



class Stats {
public:
  Stats();
  void update(const char name[25], const char team[4], int hit, int operationNum);
  void query(const char team[4], Player top10[10], int operationNum);

  Players p1[20];
  Players p2[40];

  Team t[30];
};

#endif	/* STATS_H */

