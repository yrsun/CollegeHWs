#include <iostream>
#include <fstream>
#include <iomanip>
#include "BinaryTree.h"

using namespace std;

class Huffman
{
public:
	char c;
	int times;
    int check;

	bool operator< (const Huffman &com)const
	{
		return this->times<com.times;
	}

	friend ostream &operator<<(ostream &output, const Huffman &h)
    {
    	output << h.c << setw(5) << h.times;
    	return output;
	}

};

int findminh(Huffman *hm, int count)
{
	int min=150000;
	int minposition;

	for (int i = 0; i < count; ++i)
	{
		if (hm[i].times<=min&&hm[i].check==0)
		{
			min=hm[i].times;
			minposition=i;
			
		}
	}

	hm[minposition].check++;
	//cout<<count<<"!!!"<<minposition<<endl;

	return minposition;
}



int main(int argc, char const *argv[])
{
	int list[3000];

	for (int i = 0; i < 3000; ++i)
	{
		list[i]=0;
	}

	ifstream inf(argv[1]);

    char temp;

	while(inf>>std::noskipws >>temp)
	{
		int a=temp;
		list[a]++;
	}

	/*for (int i = 0; i < 200; ++i)
	{
		cout<<list[i]<<"  "<<i<<endl;
	}*/

	int count=0;
	Huffman hm[3000];
	BinaryTree <Huffman>  bt[3000];

	for (int i = 0; i < 3000; ++i)
	{
		if (list[i]>0)
		{
			hm[count].c=i;
			hm[count].times=list[i];
			hm[count].check=0;
			bt[count].object=hm[count];
			bt[count].left=NULL;
			bt[count].right=NULL;
			count++;
		}
	}

	//cout<<count<<endl;

	int count1=count;
	int countBT = 0;

	for (int i = 0; i < count-1; ++i)
	{
		int temp1 = findminh(hm,count1);
		int temp2 = findminh(hm,count1);
		//cout<<temp1<<"  "<<temp2<<endl;
		hm[count1].c=count1;
		hm[count1].times=hm[temp1].times+hm[temp2].times;
		hm[count1].check=0;
		if(hm[temp1].times==hm[temp2].times){
					bt[count1].object=hm[count1];
		bt[count1].left=&bt[temp2];
		bt[count1].right=&bt[temp1];
		}else{
		bt[count1].object=hm[count1];
		bt[count1].left=&bt[temp1];
	 	bt[count1].right=&bt[temp2];
	    }
        count1++;
	}

	//cout<<count<<"  "<<count1<<endl;

    char arr[3000];
    int countpt=0;
	bt[count1-1].printTree(arr, countpt);

	return 0;
}