#include "stdafx.h"

//进制转化函数
/*
	使用
	char s1[] = "E";
	int a = toTen(s1, 16);
	cout << a << endl;
	char temp[200];
	int b= 15;
	_itoa(a, temp, 16);
	cout << temp;
*/
void TenToAny(int TenNum, int HexOrBina) 
{
	int i = 0;
	char array[64] = "";
	while (TenNum != 0)
	{
		array[i] = TenNum%HexOrBina;
		if (array[i] >= 10)
			array[i] = array[i] - 10 + 'A';
		else
			array[i] += 48;
		TenNum /= HexOrBina;
		i++;
	}
	i--;
	while (i >= 0)
	{
		printf("%c", array[i]);
		i--;
	}
	printf("\n");
	return;
}

long  toTen(char a[], int bit)
{
	int length = strlen(a);
	int i, b = 1, sum = 0; //i要做数组a的下标，注意其起止范围 
	for (i = length - 1; i >= 0; i--)
	{
		if (a[i] >= 'A')
		{
			sum += (a[i] - 'A' + 10) *b;
			b *= bit;
		}
		else
		{
			sum += (a[i] - '0') *b;
			b *= bit;
		}
	}
	return sum;
}


/*
		Unicode符号范围        |   UTF-8编码方式
		(十六进制)                 |   （二进制）
		------------------------------+--------------------------------------------------------------
		0000 0000-0000 007F | 0xxxxxxx
		0000 0080-0000 07FF | 110xxxxx 10xxxxxx
		0000 0800-0000 FFFF | 1110xxxx 10xxxxx 10xxxxxx
		0001 0000-0010 FFFF | 11110xxx 10xxxxxx 10xxxxxx 10xxxxxx

		1字节 0xxxxxxx   有几个字节前面就有几个一
		2字节 110xxxxx 10xxxxxx
		3字节 1110xxxx 10xxxxxx 10xxxxxx
		4字节 11110xxx 10xxxxxx 10xxxxxx 10xxxxxx
		5字节 111110xx 10xxxxxx 10xxxxxx 10xxxxxx 10xxxxxx
		6字节 1111110x 10xxxxxx 10xxxxxx 10xxxxxx 10xxxxxx 10xxxxxx
		---------------------------------------------------------------------------------------------
*/

