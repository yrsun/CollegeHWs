//Author: Yiru Sun
//ID: XXXXXXXXXXXXX
#include <iostream>
#include <fstream>
#include <string>
#include "CPUTimer.h"
#include "LinkedList.h"
#include "StackAr.h"
#include "dsexceptions.h"
#include "CursorList.h"
#include "QueueAr.h"
#include "StackLi.h"
#include "SkipList.h"
#include "vector.h"

vector<CursorNode <int> > cursorSpace(250000);

using namespace std;

int getChoice();
void RunList(string);
void RunCursorList(string);
void RunStackAr(string); 
void RunStackLi(string);
void RunQueueAr(string);
void RunSkipList(string);

int main () 
{
	int choice;
	string filename;
	CPUTimer ct;

	cout<< "Filename >> "; 
	cin>>filename;
	do
{
	choice = getChoice();
	ct.reset();
	
	switch (choice)
	{
	case 1: RunList(filename); break;
	case 2: RunCursorList(filename); break;
	case 3: RunStackAr(filename); break;
	case 4: RunStackLi(filename);break;
	case 5: RunQueueAr(filename);break;
	case 6: RunSkipList(filename);break;
	}
	cout<<"CPU time: "<<ct.cur_CPUTime()<<endl;

} while(choice > 0);

	return 0;

}

int getChoice() 
{
	int choice; 
	cout<<"      ADT Menu"<<endl;
	cout<<"0. Quit"<<endl;
	cout<<"1. LinkedList"<<endl;
	cout<<"2. CursorList"<<endl;
	cout<<"3. StackAr"<<endl;
	cout<<"4. StackLi"<<endl;
	cout<<"5. QueueAr"<<endl;
	cout<<"6. SkipList"<<endl;
	cout<<"Your choice >> "; 
	cin >> choice; 
	return choice;  
}

void RunList(string name)
{
	List <int>linklist; 
	ListItr <int> pos = linklist.zeroth();
	char c; 
	int n; 
	ifstream inf(name.c_str());
	inf.ignore(512, '\n'); 

	while (inf>>c>>n)
	{
		if (c == 'i')
		{
			linklist.insert(n , pos); 	
		}
		else if (c == 'd')
		{
			linklist.remove(n);
		}
	}

	inf.close();
}

void RunCursorList(string name)
{
	CursorList <int> cursor(cursorSpace);
	CursorListItr <int> pos = cursor.zeroth();
	char c; 
	int n; 	
	ifstream inf(name.c_str());
	inf.ignore(512, '\n'); 
	while (inf>>c>>n)
	{
		if (c == 'i')
		{
			cursor.insert(n , pos); 	
		}
		else if (c == 'd')
		{
			cursor.remove(n);
		}
	}

	inf.close();
}

void RunStackAr(string name)
{
	StackAr <int>stack(250000);
	stack.makeEmpty();
	char c; 
	int n; 	
	
	ifstream inf(name.c_str());
	inf.ignore(512, '\n'); 
	while (inf>>c>>n)
	{
		if (c == 'i')
		{
			stack.push(n); 	
		}
		else if (c == 'd')
		{
			stack.pop();
		}
	}

	inf.close();
	
}

void RunStackLi(string name)
{ 
	StackLi <int> stackli;
	char c;
	int n;
	ifstream inf(name.c_str());
	inf.ignore(512,'\n');
	while (inf>>c>>n)
	{
		if (c== 'i')
			stackli.push(n);
		else if (c=='d')
			stackli.pop();
	}
	inf.close();
}

void RunQueueAr (string name)
{
	Queue <int> queuear(250000);
	char c;
	int n;
	ifstream inf(name.c_str());
	inf.ignore(512,'\n');
	while (inf>>c>>n)
	{
		if (c=='i')
			queuear.enqueue(n);
		else if (c=='d')
			queuear.dequeue();
	}
	inf.close();
}

void RunSkipList(string name)
{
	SkipList <int> skiplist(0,2500000);
	char c;
	int n;
	ifstream inf(name.c_str());
	inf.ignore(512,'\n');
	while (inf>>c>>n)
	{
		if (c=='i')
			skiplist.insert(n);
		else if (c=='d')
			skiplist.deleteNode(n);
	}
	inf.close();
}
