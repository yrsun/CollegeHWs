//Author: Yiru SUn
//ID:999235229
#include <iostream>
#include "LongInt.h"
#include "StackLi.h"

using namespace std;

LongInt::LongInt()
{}

LongInt::~LongInt()
{}

istream &operator>>(istream &input, LongInt &number)
{


	while (isdigit(input.peek()))
	{
		
		number.list.push(input.get()-48);
	}
	while(input.get()!='\n')
	
	
	return input;
}

ostream &operator<< (ostream &output, LongInt &number)
{
	
	while(number.list.isEmpty()== false )
	{
		cout<< number.list.topAndPop();
	}
	return output;
}

 LongInt &LongInt::operator=( LongInt &right)
	{
		
		while(right.list.isEmpty()==0)
		{
			this->list.push(right.list.topAndPop());
		}
		
		return *this;
	}
	
 LongInt &LongInt::operator+( LongInt &right)
	{
		StackLi <int> temp;
		bool carry=0;
		int n1,n2,n3;
		while(this->list.isEmpty()== false || right.list.isEmpty()==false)
		{
			if(this->list.isEmpty()==true)
			{
				n1=0;
				n2=right.list.topAndPop();
			}else if(right.list.isEmpty()==true)
			{
				n1=this->list.topAndPop();
				n2=0;
			}else
			{
				n1=this->list.topAndPop();
				n2=right.list.topAndPop();
			}

			n3=n1+n2+carry;
			if(n3>9)
			{
				n3 = n3 - 10;
				carry = 1;
			}else
			{
				carry = 0;
			}
			temp.push(n3);

		}
		if(carry==1)
		{temp.push(1);}

		while(temp.isEmpty()==0)
		{
			this->list.push(temp.topAndPop());
		}
		return *this;
	}