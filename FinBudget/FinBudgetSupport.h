#pragma once
#include "pch.h"
#include <ctime>
#include <vector>
#include <string>
time_t StringToDateTime(char* str);
CString DateTimeToString(time_t _time);
CString _toCString(double _value);
CString _toCString(int _value);
double _toDouble(CString _str);
char* CStringToCharArray(CString str);
void SplitString(const std::string& s, std::vector<std::string>& v, const std::string& c);
enum Cycle {
	Annually = 2,
	Monthly = 1,
	Daily = 0
};
enum FlowType {
	Invest = 0, //投资取出
	Repay = 1,  //还债
	Expance = 2,  //普通支出
	Gain = 3   //普通收入
};
enum DebtType {
	Finance = 0, //投资
	Debt = 1 
};

