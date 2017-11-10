//Author: Yiru SUn
//ID:999235229
#ifndef _LONGINT_H
#define _LONGINT_H
#include <iostream>
#include "StackLi.h"
using namespace std;

class LongInt
{
private:
	StackLi <int> list;
public:
	LongInt();
	~LongInt();
	LongInt &operator=( LongInt &);
	LongInt &operator+( LongInt &);
	
friend ostream &operator <<(ostream &, LongInt &);
friend istream &operator >>(istream &, LongInt &);
};




#endif