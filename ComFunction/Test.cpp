#include <iostream>
#include <stdio.h>
#include "strutil.h"

int main(void)
{
	printf("hello\n");
	std::string str = "1,2,45,sds,34,45,dsf,543,dfgd,df,5434,45";
	std::vector<std::string> arrStr;
	SplitStr(str, arrStr);
	printf("nimei");
	printf("nimei");
	printf("nimei");
	printf("nimei");
	
	double dLarge = 12.456;
	std::string strLarge = DoubleToStr(dLarge, 3);
	system("pause");
	return 0;
}