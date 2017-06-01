#ifndef _STR_UTIL_H_
#define _STR_UTIL_H_
#include <string.h>
#include <iostream>
#include <vector>

char* RTrim(char* str, const char* szBlank = "\t\r\n");

std::string RTrim(const std::string & str, const char* szBlank = "\t\r\n");

char* LTrim(char* str, const char* szBlank = "\t\r\n");

std::string LTrim(const std::string &str, const char * szBlank = "\t\r\n");

char* Trim(char* str, const char* szBlank = "\t\r\n");

std::string Trim(const std::string &str, const char* szBlank = "\t\r\n");

std::string DoubleToStr(double dVal, int nDec = -1, bool bDelZero = false);

//最后一个参数标示是否过滤空格
int SplitStr(const std::string &strInput, std::vector<std::string>& arrStr, char chSep = ',', bool bMark = false);

#endif // inc
