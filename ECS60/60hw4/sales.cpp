//Yiru Sun
//999235229
#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <stdio.h>
#include <stdlib.h>
#include <algorithm>
#include <math.h>
#include "SaleRunner.h"
#include "sales.h"

 static int cmpfunc (const void * a, const void * b) {
  if ( *(long long*)a <  *(long long*)b ) 
  	return -1;
  if ( *(long long*)a == *(long long*)b ) 
  	return 0;
  if ( *(long long*)a >  *(long long*)b ) 
  	return 1;
}

static int cmp (const void * a, const void * b) {
   const Pro* _a = reinterpret_cast<const Pro*>(a);
   const Pro* _b = reinterpret_cast<const Pro*>(b);
   return _a->SKU < _b->SKU ? -1 : _a->SKU > _b->SKU ? 1 : 0;
}


Sales::Sales(const ProductInfo *productInfo, int productCount) 
{
	mcount = 0;
	pronum = productCount;
	pro = new Pro[productCount];
	for(int i = 0; i< productCount; i++)
	{
		pro[i].SKU = productInfo[i].SKU;
		pro[i].onHand = productInfo[i].onHand;
		pro[i].minimum = productInfo[i].minimum;
		pro[i].price = productInfo[i].price;	
		pro[i].order = 0;
		pro[i].totsal = 0;
		memcpy(pro[i].name, productInfo[i].name, 265);
		if (pro[i].onHand<pro[i].minimum)
			{
				pro[i].order++;
				m[mcount]=pro[i].SKU;
				mcount++;
			}
	}
	qsort(pro, pronum, sizeof(pro[0]), cmp);

}  // Sales())


template <typename T>
int fbsearch( const T *sorted_list, size_t list_size, long long x )
{

    unsigned i = 0;
    unsigned b = 1 << int( log(list_size-1) / M_LN2 );
 
    for( ; b ; b >>= 1 )
    {
        unsigned j = i | b;
        if( j < list_size && sorted_list[j].SKU <= x ) i = j;
    }
 
    return i;
}


void Sales::sale(long long SKU, int numSold, const char **name, int *price)
{

	int i = fbsearch(pro, pronum, SKU);

	*name = pro[i].name;
	*price = pro[i].price;
	if(numSold<=pro[i].onHand )
	{
		pro[i].onHand-=numSold;
		pro[i].totsal+=(numSold*pro[i].price);
		if(pro[i].onHand<pro[i].minimum && pro[i].order==0)
		{
			pro[i].order++;
			m[mcount]=pro[i].SKU;
			mcount++;

		}
	}

} // sale())


 void Sales::report(long long SKU, long long SKU2, int *totalSales)
 {
 	*totalSales = 0;
 	if (SKU==SKU2)
 	{
		int i = fbsearch(pro, pronum, SKU);
 		*totalSales = pro[i].totsal;
 	}else
 	{
 		int i = fbsearch(pro, pronum, SKU);
 		int j = fbsearch(pro, pronum, SKU2);
		if (i<j)
		{
			for (int a = i; a<=j; ++a)
			{
 				*totalSales += pro[a].totsal;
			}
		}else
		{
			for (int a = j; a<=i; ++a)
			{
 				*totalSales += pro[a].totsal;
			}
		}
 	}
 }  // report())
 
 
 void Sales::belowMinimums(long long belowMin[], int *belowMinCount)
 {
 	*belowMinCount = mcount;
 	qsort(m, mcount, sizeof(long long), cmpfunc);
 	for (int i = 0; i < mcount; ++i)
 	{
 		belowMin[i]=m[i];
 	}
 }  // belowMinimums())

