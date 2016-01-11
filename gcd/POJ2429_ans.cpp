/*
https://github.com/neofung/acm_backup/blob/master/src/POJ/POJ2429%20GCD%20LCM%20Inverse.cpp
*/

#include <fstream>
#include <stdio.h>
#include <iostream>
#include <string.h>
#include <string>
#include <memory.h>

#include <math.h>
#include <algorithm>
#include <numeric>
#include <functional>
#include <limits>
#include <assert.h>
#include <ctype.h>

#include <vector>
#include <stack>
#include <queue>
#include <deque>

#define MAX 1000000

using namespace std;



int gcd(const int &lhs,const int &rhs)
{
	return rhs == 0 ? lhs : gcd(rhs,lhs % rhs);
}

int main(void)
{
	int x , y, temp;

	while(scanf("%d %d",&x,&y)!=EOF)
	{
		temp = y / x;
		int result;
		int upper = (int)sqrt((double)temp);

		for (int i= upper; i >= 1; --i)
		{
			if(temp % i == 0 && gcd(temp / i, i ) == 1)
			{
				result = i;
				break;
			}
		}
		printf("%d %d\n",result*x,y/result);
	}


	return 0;
}
