// Authors:  Yiru Sun
//999235229
 
#ifndef SALES_H
#define	SALES_H

#include <stdio.h>
#include <stdlib.h>
#include <algorithm>
#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include "SaleRunner.h"

using namespace std;


class Pro {
public:
	long long SKU;
	char name[265];
	int price;
	int onHand;
	int minimum;
	int order;
	int totsal;
};


class Sales {
public:
  Sales(const ProductInfo *productInfo, int productCount);
  void sale(long long SKU, int numSold, const char **name, int *price);
  void report(long long SKU, long long SKU2, int *totalSales);
  void belowMinimums(long long belowMin[], int *belowMinCount);

  int pronum;
  int mcount;
  long long m[50000];
  Pro *pro;
};

#endif	/* SALES_H */

